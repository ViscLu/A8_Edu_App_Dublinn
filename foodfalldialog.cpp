#include "foodfalldialog.h"
#include <QVBoxLayout>
#include <QTransform>
#include <QGraphicsScene>
#include <QMouseEvent>

const float timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

FoodFallDialog::FoodFallDialog(QWidget *parent) : QDialog(parent)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    timer = new QTimer(this);
    b2Vec2 gravity(0.0f, -9.8f);
    world = new b2World(gravity);
    scaleFactor = 50.0f;

    int fixedWidth = 1920;
    int fixedHeight = 1080;
    setFixedSize(fixedWidth, fixedHeight);

    CustomContactListener *contactListener = new CustomContactListener();
    world->SetContactListener(contactListener);

    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setSceneRect(0, 0, 1920, 1080);
    view->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setTransform(QTransform::fromScale(1, 1));

    //    b2BodyDef groundBodyDef;
    //    float groundYPosition = (1080 - 10) / scaleFactor;
    //    groundBodyDef.position.Set(0.0f, -groundYPosition);

    //    //float groundYPosition = 10 / scaleFactor;
    //    //groundBodyDef.position.Set(0.0f, groundYPosition);
    //    //float groundYPosition = 10 / scaleFactor;
    //    //groundBodyDef.position.Set(0.0f, (fixedHeight - 10) / scaleFactor);
    //    b2Body *groundBody = world->CreateBody(&groundBodyDef);

    //    // 定义地面形状
    //    b2PolygonShape groundBox;
    //    float groundWidth = 1920 / scaleFactor; // 设置地面宽度为视图宽度
    //    float groundHeight = 10.0f / scaleFactor; // 地面高度
    //    groundBox.SetAsBox(groundWidth / 2.0f, groundHeight / 2.0f);

    //    // 为地面添加夹具
    //    b2FixtureDef groundFixtureDef;
    //    groundFixtureDef.shape = &groundBox;
    //    groundFixtureDef.restitution = 0.5f; // 设置反弹系数，可以根据需要调整
    //    groundFixtureDef.friction = 0.5f; // 设置地面摩擦系数
    //    groundBody->CreateFixture(&groundFixtureDef);

    // 添加一个边界矩形用于表示地面
    //    QGraphicsRectItem *groundRect = new QGraphicsRectItem(0, 0, 1920, 10);
    //    groundRect->setPos(0, 1080-10);
    //    groundRect->setBrush(QBrush(Qt::blue));
    //    scene->addItem(groundRect);

    moveDirection  = 0;
    QPixmap characterPixmap(":/ArtAssert/Recipe_KungPaoChicken.png");

    characterItem = new QGraphicsPixmapItem(characterPixmap);
    characterItem->setPos(0, 1080 - characterPixmap.height() - 10);
    scene->addItem(characterItem);

    b2BodyDef characterBodyDef;
    characterBodyDef.type = b2_staticBody;
    float characterX = characterItem->x() / scaleFactor;
    float characterY = (1080 - characterItem->y() - characterPixmap.height()) / scaleFactor;
    characterBodyDef.position.Set(characterX, characterY);

    b2Body *characterBody = world->CreateBody(&characterBodyDef);

    b2PolygonShape characterBox;
    float characterWidth = characterPixmap.width() / scaleFactor;
    float characterHeight = characterPixmap.height() / scaleFactor;
    characterBox.SetAsBox(characterWidth / 2.0f, characterHeight / 2.0f);

    b2FixtureDef characterFixtureDef;
    characterFixtureDef.shape = &characterBox;
    characterFixtureDef.restitution = 0.5f;
    characterFixtureDef.friction = 0.5f;
    characterBody->CreateFixture(&characterFixtureDef);

    characterBody->SetUserData((void*)1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    timer->setInterval(1000 / 60);
    connect(timer, &QTimer::timeout, this, &FoodFallDialog::updateWorld);
    timer->start();

    setMouseTracking(true);
}

FoodFallDialog::~FoodFallDialog()
{
    delete world;
    delete timer;
    delete view;
    delete scene;
}

void FoodFallDialog::updateWorld()
{
    world->Step(timeStep, velocityIterations, positionIterations);

    for (QGraphicsPixmapItem *item : foodItems)
    {
        b2Body *body = static_cast<b2Body *>(item->data(0).value<void *>());
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();

        QTransform transform;
        transform.translate(position.x * scaleFactor, (1080 - position.y * scaleFactor)); // Negate the Y position to flip the coordinate
        transform.rotateRadians(angle);
        item->setTransform(transform);
    }

    if (moveDirection != 0)
    {
        float newX = characterItem->x() + moveDirection * 5;

        // 检查新的x位置是否在屏幕范围内，如果是，则更新角色位置
        if (newX >= 0 && newX + characterItem->pixmap().width() <= view->sceneRect().width())
        {
            characterItem->setX(newX);
        }
    }
}

void CustomContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();


    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    int bodyAUserData = (intptr_t)bodyA->GetUserData();
    int bodyBUserData = (intptr_t)bodyB->GetUserData();

    // 判断是否有一个角色和一个食物发生碰撞
    if ((bodyAUserData == 1 && bodyBUserData == 2) || (bodyAUserData == 2 && bodyBUserData == 1))
    {
        // 在这里处理角色和食物之间的碰撞
        // 您可以根据需要检查夹具的 userData 或刚体的 userData 以确定哪个是角色，哪个是食物
        // 然后根据需要调整碰撞属性，例如反弹系数

        // 示例: 设置碰撞的反弹系数
        contact->SetRestitution(1.0f);
    }
}

void FoodFallDialog::mousePressEvent(QMouseEvent *event)
{
    QPointF pos = view->mapToScene(event->pos());
    b2BodyDef bodyDef;
    bodyDef.linearVelocity.Set(0.0f, 0.0f);
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x() / scaleFactor, (1080 - pos.y()) / scaleFactor);
    //bodyDef.position.Set(pos.x() / scaleFactor, pos.y() / scaleFactor);

    b2Body *body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = 10.0f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f; // 设置食物的摩擦系数
    fixtureDef.restitution = 0.3f; // 设置食物的反弹系数
    body->CreateFixture(&fixtureDef);

    body->SetUserData((void*)2);

    QPixmap pixmap(":/ArtAssert/Recipe_KungPaoChicken.png");
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    item->setOffset(-pixmap.width() / 2, -pixmap.height() / 2);
    item->setData(0, QVariant::fromValue(static_cast<void *>(body)));
    scene->addItem(item);
    foodItems.append(item);
}

void FoodFallDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A)
    {
        moveDirection = -1;
    }
    else if (event->key() == Qt::Key_D)
    {
        moveDirection = 1;
    }
}

void FoodFallDialog::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_D)
    {
        moveDirection = 0;
    }
}
