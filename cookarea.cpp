#include "cookarea.h"

CookArea::CookArea(QPoint pos, QString areaTypeName, QPixmap pixmap){
    this->setPos(pos);
    this->setPixmap(pixmap);
    areaType = areaTypeName;
}

QString CookArea::getAreaType(){
    return areaType;
}
