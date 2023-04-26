#ifndef FOODFALLDIALOG_H
#define FOODFALLDIALOG_H


#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>
#include <Box2D/Box2D.h>

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

private slots:
    void updateWorld();
    void mousePressEvent(QMouseEvent *event);
};

class CustomContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact *contact) override;
};
#endif // FOODFALLDIALOG_H
