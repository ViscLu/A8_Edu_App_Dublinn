/*
 *  @author: Jiahua Zhao, Chnegyu Yang and Yitong Lu
 *  @course: CS3505
 *  @Assignment: A8-An-Educational-App
 *  @Description: This is a C++ class implementation of CookArea, which is a derived class of QGraphicsPixmapItem.
    The CookArea class represents a specific area in a cooking game, and it has a position, an area type name, and an image.
    The constructor initializes the position and image using the passed parameters, and sets the area type.
    The getAreaType method simply returns the area type of the CookArea.
*/
#ifndef COOKAREA_H
#define COOKAREA_H

#include <QWidget>
#include <QToolButton>
//#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class CookArea : public QGraphicsPixmapItem
{

public:
    CookArea();
    CookArea(QPoint pos, QString areaTypeName, QPixmap pixmap);
    QString getAreaType();

private:
    QString areaType;

};

#endif // COOKAREA_H
