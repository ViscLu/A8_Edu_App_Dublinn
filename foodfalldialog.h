/*
 *  @author: Jiahua Zhao, Chnegyu Yang and Yitong Lu
 *  @course: CS3505
 *  @Assignment: A8-An-Educational-App
 *  @Description: This is the class for setting and adjusting the built-in Box2D mini-game. This class is responsible for providing Objects that can be instantiated and used for dropping ingredients.
*/
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

class FoodFallDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FoodFallDialog(QWidget *parent = nullptr);
    ~FoodFallDialog();
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QTimer *timer;
    b2World *world;
    float scaleFactor;
    QList<QGraphicsPixmapItem *> foodItems;
    QGraphicsPixmapItem *characterItem;
    int moveDirection;
    int currMode;
    QList<QString> foodCardPaths;
    QString randomSelectFoodCardLogo();
    QString randomSelectRecipeLogo();
    QString randomSelectDishCardLogo();
    bool rectsIntersect(const QRectF &rect1, const QRectF &rect2) const;

private slots:
    void updateWorld();
    void mousePressEvent(QMouseEvent *event);
    void foodCardMode();
    void recipeMode();
    void dishCardMode();
};
class CustomContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact *contact) override;
};

#endif // FOODFALLDIALOG_H
