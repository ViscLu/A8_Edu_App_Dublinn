#ifndef FOODFALLDIALOG_H
#define FOODFALLDIALOG_H


#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>
#include <Box2D/Box2D.h>
#include <QToolButton>
#include <QRandomGenerator>
const float PIXELS_PER_METER = 100.0;

class FoodFallDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FoodFallDialog(QWidget *parent = nullptr);
    ~FoodFallDialog();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;


private:

    void createCharacter();
    void createFood(const QPointF &position);

    b2World *world;
    QPixmap characterPixmap;
    QPixmap foodPixmap;
    b2Body *characterBody;
    b2Body *groundBody;
    QList<b2Body *> foodBodies;
    bool leftPressed;
    bool rightPressed;

//    QGraphicsScene *scene;
//    QGraphicsView *view;
//    float scaleFactor;
//    QList<QGraphicsPixmapItem *> foodItems;
//    QGraphicsPixmapItem *characterItem;
//    int moveDirection;

    int currMode;
    QList<QString> foodCardPaths;
    QString randomSelectFoodCardLogo();
    QString randomSelectRecipeLogo();
    QString randomSelectDishCardLogo();
    bool rectsIntersect(const QRectF &rect1, const QRectF &rect2) const;

private slots:
    void updateScene();
    void foodCardMode();
    void recipeMode();
    void dishCardMode();
};

#endif // FOODFALLDIALOG_H
