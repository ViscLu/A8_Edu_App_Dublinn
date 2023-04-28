/*
 *  @author: Jiahua Zhao, Chnegyu Yang and Yitong Lu
 *  @course: CS3505
 *  @Assignment: A8-An-Educational-App
 *  @Description: This is a C++ class implementation of CookArea, which is a derived class of QGraphicsPixmapItem.
    The CookArea class represents a specific area in a cooking game, and it has a position, an area type name, and an image.
    The constructor initializes the position and image using the passed parameters, and sets the area type.
    The getAreaType method simply returns the area type of the CookArea.
*/
#include "cookarea.h"

//  This is the constructor of the CookArea class in C++. It takes three parameters: a QPoint object representing the position of the CookArea, a QString object representing the type of the area, and a QPixmap object representing the image to be displayed.
CookArea::CookArea(QPoint pos, QString areaTypeName, QPixmap pixmap){
    this->setPos(pos);
    this->setPixmap(pixmap);
    areaType = areaTypeName;
}

// This is a member function of the CookArea class in C++. It returns the area type of the CookArea as a QString. The areaType variable is a private member variable of the CookArea class and is set during the object's construction.
QString CookArea::getAreaType(){
    return areaType;
}
