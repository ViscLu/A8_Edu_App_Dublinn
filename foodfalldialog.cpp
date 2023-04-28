/*
 *  @author: Jiahua Zhao, Chnegyu Yang and Yitong Lu
 *  @course: CS3505
 *  @Assignment: A8-An-Educational-App
 *  @Description: This is the class for setting and adjusting the built-in Box2D mini-game. This class is responsible for providing Objects that can be instantiated and used for dropping ingredients.
*/
#include "foodfalldialog.h"
#include <QVBoxLayout>
#include <QTransform>
#include <QGraphicsScene>
#include <QMouseEvent>\

const float timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

// define a FoodFallDialog
FoodFallDialog::FoodFallDialog(QWidget *parent) : QDialog(parent)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    timer = new QTimer(this);
    b2Vec2 gravity(0.0f, -9.8f);
    world = new b2World(gravity);
    scaleFactor = 50.0f;
    currMode = 0;
    int fixedWidth = 1920;
    int fixedHeight = 1080;
    moveDirection  = 0;

    foodCardPaths.push_back(":/ArtAssert/sugarCard.png");
    foodCardPaths.push_back(":/ArtAssert/eggCard_whisked.png");
    foodCardPaths.push_back(":/ArtAssert/cookWineCard.png");
    foodCardPaths.push_back(":/ArtAssert/raw_beefCard.png");
    foodCardPaths.push_back(":/ArtAssert/green_onionCard_water.png");
    foodCardPaths.push_back(":/ArtAssert/peanutsCard.png");
    foodCardPaths.push_back(":/ArtAssert/tomatoCard.png");
    foodCardPaths.push_back(":/ArtAssert/garlicCard.png");
    foodCardPaths.push_back(":/ArtAssert/oilCard.png");
    foodCardPaths.push_back(":/ArtAssert/raw_chicken_brisketsCard.png");
    foodCardPaths.push_back(":/ArtAssert/washCard.png");
    foodCardPaths.push_back(":/ArtAssert/cutCard.png");


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
    scene->addPixmap(QPixmap(":/ArtAssert/FoodDropGameBackground.png"));

    auto foodCardSelectButton = new QToolButton();
    foodCardSelectButton->resize(246, 96);
    foodCardSelectButton->setIcon(QIcon(":/ArtAssert/FoodDropGame_foodCardButton.png"));
    foodCardSelectButton->setIconSize(QSize(246, 96));
    foodCardSelectButton->move(47, 496);
    foodCardSelectButton->setStyleSheet("background-color: transparent;");

    auto recipeCardSelectButton = new QToolButton();
    recipeCardSelectButton->resize(246, 96);
    recipeCardSelectButton->setIcon(QIcon(":/ArtAssert/FoodDropGame_RecipeLogoButton.png"));
    recipeCardSelectButton->setIconSize(QSize(246, 96));
    recipeCardSelectButton->move(47, 626);
    recipeCardSelectButton->setStyleSheet("background-color: transparent;");

    auto dishCardSelectButton = new QToolButton();
    dishCardSelectButton->resize(246, 96);
    dishCardSelectButton->setIcon(QIcon(":/ArtAssert/FoodDropGame_dishCardButton.png"));
    dishCardSelectButton->setIconSize(QSize(246, 96));
    dishCardSelectButton->move(47, 756);
    dishCardSelectButton->setStyleSheet("background-color: transparent;");

    scene->addWidget(foodCardSelectButton);
    scene->addWidget(recipeCardSelectButton);
    scene->addWidget(dishCardSelectButton);

    connect(foodCardSelectButton, &QToolButton::clicked, this, &FoodFallDialog::foodCardMode);
    connect(recipeCardSelectButton, &QToolButton::clicked, this, &FoodFallDialog::recipeMode);
    connect(dishCardSelectButton, &QToolButton::clicked, this, &FoodFallDialog::dishCardMode);

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

// Dconstructor of the FoodFallDialog
FoodFallDialog::~FoodFallDialog()
{
    delete world;
    delete timer;
    delete view;
    delete scene;
}

// This method is used to detect collisions and keep updating the page content.
void FoodFallDialog::updateWorld()
{
    world->Step(timeStep, velocityIterations, positionIterations);

    QRectF characterRect = characterItem->sceneBoundingRect();
    for (QGraphicsPixmapItem *item : foodItems)
    {
        b2Body *body = static_cast<b2Body *>(item->data(0).value<void *>());
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        QTransform transform;
        transform.translate(position.x * scaleFactor, (1080 - position.y * scaleFactor)); // Negate the Y position to flip the coordinate
        transform.rotateRadians(angle);
        item->setTransform(transform);

        QRectF foodRect = item->sceneBoundingRect();
                if (rectsIntersect(characterRect, foodRect))
                {
                    // collision happened
                    b2Body *body = static_cast<b2Body *>(item->data(0).value<void *>());
                    b2Vec2 velocity = body->GetLinearVelocity();
                    body->SetLinearVelocity(b2Vec2(velocity.x, -velocity.y)); // Invert the y velocity to make the food bounce
                }
    }

    if (moveDirection != 0)
    {
        float newX = characterItem->x() + moveDirection * 5;
        // Check if the new x position is within the screen bounds, if so, update the character position
        if (newX >= 0 && newX + characterItem->pixmap().width() <= view->sceneRect().width())
        {
            characterItem->setX(newX);
        }
    }
}

// Listen and calculate the collision state, which behaves differently depending on the rigidity or flexibility of the object the falling object collides with.
void CustomContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();
    int bodyAUserData = (intptr_t)bodyA->GetUserData();
    int bodyBUserData = (intptr_t)bodyB->GetUserData();
    // Determine if a character collides with a food
    if ((bodyAUserData == 1 && bodyBUserData == 2) || (bodyAUserData == 2 && bodyBUserData == 1))
    {
        // Handle the collision between the character and the food here
        // You can check the fixture's userData or the rigidbody's userData as needed to determine which is the character and which is the food
        // Then adjust the collision properties as needed, such as the bounce coefficient
        // Example: Set bounce coefficient for collision
        contact->SetRestitution(1.0f);
    }
}

// Spawns food cards that fly around when the mouse is clicked on the screen.
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
    fixtureDef.friction = 0.3f;// Set the friction system of the food
    fixtureDef.restitution = 0.3f; // Set the rebound coefficient of the food
    body->CreateFixture(&fixtureDef);
    body->SetUserData((void*)2);
    QString currPixmap = ":/ArtAssert/Recipe_KungPaoChicken.png";
    if(currMode == 0){
        currPixmap = randomSelectFoodCardLogo();
    }else if(currMode == 1){
        currPixmap = randomSelectRecipeLogo();
    }else if(currMode == 2){
        currPixmap = randomSelectDishCardLogo();
    }
    QPixmap pixmap(currPixmap);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    item->setOffset(-pixmap.width() / 2, -pixmap.height() / 2);
    item->setData(0, QVariant::fromValue(static_cast<void *>(body)));
    scene->addItem(item);
    foodItems.append(item);
}

// Select ingredient cards to drop from the sky.
void FoodFallDialog::foodCardMode()
{
    currMode = 0;
}

// Select tabs falling from the sky.
void FoodFallDialog::recipeMode()
{
    currMode = 1;
}

// Choose food finished cards to drop from the sky.
void FoodFallDialog::dishCardMode()
{
    currMode = 2;
}

// Adjust whether the bar at the bottom of the menu moves to the left or to the right according to the keys.
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

// When the key is released, stop the movement of the bar.
void FoodFallDialog::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_D)
    {
        moveDirection = 0;
    }
}

// Checks if two card rectangles collide.
bool FoodFallDialog::rectsIntersect(const QRectF &rect1, const QRectF &rect2) const
{
    return (rect1.left() < rect2.right() &&
            rect1.right() > rect2.left() &&
            rect1.top() < rect2.bottom() &&
            rect1.bottom() > rect2.top());
}

// Randomly choose the ingredient card that should drop.
QString FoodFallDialog::randomSelectFoodCardLogo(){
    int randomInt = QRandomGenerator::global()->bounded(0, foodCardPaths.size());
    return foodCardPaths[randomInt];
}

// Randomly selects the option card that should drop.
QString FoodFallDialog::randomSelectRecipeLogo(){
    int randomInt = QRandomGenerator::global()->bounded(1, 5);
    if(randomInt % 4 == 0){
        return ":/ArtAssert/Recipe_FoodDropGame.png";
    }else if(randomInt % 3 == 0){
        return ":/ArtAssert/Recipe_TomatoAndEggStirFry.png";
    }else if(randomInt % 2 == 0){
        return ":/ArtAssert/Recipe_KungPaoChicken.png";
    }else{
        return ":/ArtAssert/Recipe_BeefStewWithPotatoes.png";
    }
}

// Randomly choose the finished food card that should drop.
QString FoodFallDialog::randomSelectDishCardLogo(){
    int randomInt = QRandomGenerator::global()->bounded(1, 5);
    if(randomInt % 4 == 0){
        return ":/ArtAssert/BeefStewWithPotatoesCard.png";
    }else if(randomInt % 3 == 0){
        return ":/ArtAssert/TomatoAndEggStirFryCard.png";
    }else if(randomInt % 2 == 0){
        return ":/ArtAssert/KungPaoChickenCard.png";
    }else{
        return ":/ArtAssert/charredFoodCard.png";
    }
}

