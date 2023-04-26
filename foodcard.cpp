#include "foodcard.h"
//#include "cookmaingameroom.h"

FoodCard::FoodCard(QObject *parent)
{
}

FoodCard::FoodCard(QPoint pos, QString foodName, QString pathName){
    cardPos = pos;
    foodCardName = foodName;
    this->setPos(pos);
    this->setPixmap(QPixmap(pathName));
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

void FoodCard::setCardPos(QPoint pos){
    this->setPos(pos);
    cardPos = pos;
}

QString FoodCard::GetFoodCardName(){
    return foodCardName;
}
