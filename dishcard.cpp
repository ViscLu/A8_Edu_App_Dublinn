#include "dishcard.h"

DishCard::DishCard(QObject *parent)
{

}

DishCard::DishCard(QString dishName, QString pathName){
    //cardPos = QPoint(845,222);
    dishCardName = dishName;
    this->setPos(QPoint(845,222));
    this->setPixmap(QPixmap(pathName));
}


