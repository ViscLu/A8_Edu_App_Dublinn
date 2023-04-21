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
    FoodCard(QPoint pos, QString foodName, QPixmap pixmap);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void resetCardPos();

    bool checkRelease;

    //void keyPressEvent(QKeyEvent *event);

signals:
    //void mouseReleased(bool check);

public slots:

private:
    QPointF mousePressPos;
    int mSpeed;
    QPoint cardPos;
    QString foodCardName;
};

#endif // FOODCARD_H
