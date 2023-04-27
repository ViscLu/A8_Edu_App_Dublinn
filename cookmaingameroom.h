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
#include <QDialog>
#include "gamemenu.h"
#include "foodfalldialog.h"
#include <QtMultimedia/QMediaPlayer>

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
    void enterMainGameLevelKungBaoChicken();
    void enterMainGameLevelTomatoAndEggStirFry();
    void enterMainGameLevelBeefStewWithPotatoes();
    void checkCollision();
    void addNewCard(QPoint pos, QString foodName, QString path);
    void OpenFile();
    void backToRecipeLevelAndClearGameLevel();
    void addNewRecipeStep(QString recipeStepPixmap);
    void showDishCard(QString dishPixmapPath);
    void openGameMenu();
    void restartGameRoom();
    void enterFoodDropGameRoom();
    void onStateChanged(QMediaPlayer::PlaybackState state);

signals:
    void sendCollisionItems(QList<QString>);
    void readFileForOpen(QList<QString> filenames);
    void resetMainGameLevel();
    void setupMainGameLevel(QString recipeName);
    void restartGameRoomRequest(QString recipeName);

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
    QString currRecipe;
    QList<FoodCard*> foodCardsList;
    QList<CookArea*> CookAreasList;
    QList<QString> collisionItems;

    GameMenu gameMenuWindow;
    FoodFallDialog foodFallDialogWindow;

    // To implement the music play
    QMediaPlayer* mediaPlayer;
    QAudioOutput* outPut;
};
#endif // COOKMAINGAMEROOM_H
