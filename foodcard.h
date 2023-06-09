/*
 *  @author: Jiahua Zhao, Chnegyu Yang and Yitong Lu
 *  @course: CS3505
 *  @Assignment: A8-An-Educational-App
 *  @Description: This is the class for represent a food card.
*/
#ifndef FOODCARD_H
#define FOODCARD_H

#include <QWidget>
#include <QToolButton>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class FoodCard : public QGraphicsPixmapItem
{

public:
    explicit FoodCard(QObject *parent = nullptr);
    FoodCard(QPoint pos, QString foodName, QString pathName);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void resetCardPos();
    QString GetFoodCardName();
    void setCardPos(QPoint pos);

    bool checkRelease;

signals:

public slots:

private:
    QPointF mousePressPos;
    int mSpeed;
    QPoint cardPos;
    QString foodCardName;
};

#endif // FOODCARD_H
