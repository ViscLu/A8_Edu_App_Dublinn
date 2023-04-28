/*
 *  @author: Jiahua Zhao, Chnegyu Yang and Yitong Lu
 *  @course: CS3505
 *  @Assignment: A8-An-Educational-App
 *  @Description: This is the class for represent a food card.
*/
#include "foodcard.h"

FoodCard::FoodCard(QObject *parent)
{
}

// Define a food card.
FoodCard::FoodCard(QPoint pos, QString foodName, QString pathName){
    cardPos = pos;
    foodCardName = foodName;
    this->setPos(pos);
    this->setPixmap(QPixmap(pathName));
    checkRelease = false;
}

// This method calculates and represents how the food card moves when the mouse clicks on the food card and tries to move it.
void FoodCard::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF mouseMovePos = event->pos() - mousePressPos;
    this->setPos(this->pos().x() + mouseMovePos.x(), this->pos().y() + mouseMovePos.y());
}

// This method calculates and represents how the food card moves when the mouse clicks on the food card and tries to move it.
void FoodCard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mousePressPos = event->pos();
    qDebug() <<"get mouse press pos" <<mousePressPos;
    checkRelease = false;
}

// This method will calculate the ingredient card's destination when the mouse is released.
void FoodCard::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    checkRelease = true;
}

// Reset the position of the ingredients card.
void FoodCard::resetCardPos(){
    this->setPos(cardPos);
}

// Set the position of the ingredients card.
void FoodCard::setCardPos(QPoint pos){
    this->setPos(pos);
    cardPos = pos;
}

// Returns the name of the ingredient.
QString FoodCard::GetFoodCardName(){
    return foodCardName;
}
