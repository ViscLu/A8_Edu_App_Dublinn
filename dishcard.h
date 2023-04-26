#ifndef DISHCARD_H
#define DISHCARD_H


#include <QWidget>
#include <QToolButton>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>
#include <QObject>

class DishCard : public QGraphicsPixmapItem
{
public:
    explicit DishCard(QObject *parent = nullptr);
    DishCard(QString dishName, QString pathName);

    void mouseClickedEvent();
    QString GetFoodCardName();

signals:

public slots:

private:
    int mSpeed;
    QString dishCardName;
};

#endif // DISHCARD_H
