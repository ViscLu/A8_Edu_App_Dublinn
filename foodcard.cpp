#include "foodcard.h"
//#include "cookmaingameroom.h"

FoodCard::FoodCard(QObject *parent)
{
}

FoodCard::FoodCard(QPoint pos, QString foodName, QPixmap pixmap){
    cardPos = pos;
    foodCardName = foodName;
    this->setPos(pos);
    this->setPixmap(pixmap);
    checkRelease = false;
}

void FoodCard::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF mouseMovePos = event->pos() - mousePressPos;
    this->setPos(this->pos().x() + mouseMovePos.x(), this->pos().y() + mouseMovePos.y());
}

void FoodCard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mousePressPos = event->pos();
    qDebug() <<"get mouse press pos" <<mousePressPos;
    checkRelease = false;
}

void FoodCard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    checkRelease = true;
}

void FoodCard::resetCardPos(){
    this->setPos(cardPos);
}

//void FoodCard::keyPressEvent(QKeyEvent *event)
//{

//}
