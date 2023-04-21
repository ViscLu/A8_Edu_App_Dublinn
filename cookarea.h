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
