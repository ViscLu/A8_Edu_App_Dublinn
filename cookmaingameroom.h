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
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CookMainGameRoom; }
QT_END_NAMESPACE

class CookMainGameRoom : public QMainWindow
{
    Q_OBJECT

public:
    CookMainGameRoom(Model& model, QWidget *parent = nullptr);
    ~CookMainGameRoom();

private slots:
    void enterRecipeLevel();
    void enterMainGameLevel();
    void checkCollision();
    void addNewCard(QPoint pos, QString foodName, QString path);
    void OpenFile();

signals:
    void sendCollisionItems(QList<QString>);
    void readFileForOpen(QString filename);


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
    QList<QString> collisionItems;
};
#endif // COOKMAINGAMEROOM_H
