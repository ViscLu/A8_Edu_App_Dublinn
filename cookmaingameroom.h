#ifndef COOKMAINGAMEROOM_H
#define COOKMAINGAMEROOM_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QWidget>
#include <QTimer>
#include "foodcard.h"
#include "cookarea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CookMainGameRoom; }
QT_END_NAMESPACE

class CookMainGameRoom : public QMainWindow
{
    Q_OBJECT

public:
    CookMainGameRoom(QWidget *parent = nullptr);
    ~CookMainGameRoom();

private slots:


signals:
    void enterRecipeLevel();
    void enterMainGameLevel();
    void checkCollision();


private:
    Ui::CookMainGameRoom *ui;

    QGraphicsScene mRecipeScene;
    QGraphicsScene mStartScene;
    QGraphicsScene mMainGameScene;

    QGraphicsPixmapItem mBackGround1;
    QGraphicsPixmapItem mBackGround2;
    QGraphicsPixmapItem mBackGround3;

    QTimer* gameLoopTimer;

    void collision();

    QList<FoodCard*> foodCardsList;
    QList<CookArea*> CookAreasList;

};
#endif // COOKMAINGAMEROOM_H
