#include "cookmaingameroom.h"
#include "ui_cookmaingameroom.h"

CookMainGameRoom::CookMainGameRoom(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CookMainGameRoom)
{
    ui->setupUi(this);
    //mGameView.setSceneRect(QRect(0,0,1920, 1080));
    //mRecipeScene.setSceneRect(QRect(0,0,1920, 1080));

    // game start screen
    mStartScene.setSceneRect(QRect(0,0,1920, 1080));  // set QGraphicsScene size
    QPixmap pixmap = QPixmap::fromImage(QImage(":/ArtAssert/EduApp_GameStartScreen.png"));
    mBackGround1.setPixmap(pixmap);
    mStartScene.addItem(&mBackGround1);

    auto startButton = new QPushButton();
    startButton->resize(450, 136);
    startButton->setIcon(QIcon(":/ArtAssert/StartScreen_StartLogo.png"));
    startButton->setIconSize(QSize(450, 136));
    startButton->move(960-450/2, 650);
    startButton->setStyleSheet("background-color: transparent;");

    auto quitButton = new QPushButton();
    quitButton->resize(450, 136);
    quitButton->setIcon(QIcon(":/ArtAssert/StartScreen_QuitLogo.png"));
    quitButton->setIconSize(QSize(450, 136));
    quitButton->move(960-450/2, 850);
    quitButton->setStyleSheet("background-color: transparent;");

    auto startLogo = new QPushButton();
    startLogo->resize(1499, 292);
    startLogo->setIcon(QIcon(":/ArtAssert/StartScreen_CookLogo.png"));
    startLogo->setIconSize(QSize(1499, 292));
    startLogo->move(960-1499/2, 130);
    startLogo->setStyleSheet("background-color: transparent;");

    mStartScene.addWidget(startButton);
    mStartScene.addWidget(quitButton);
    mStartScene.addWidget(startLogo);
    mStartScene.addItem(&mBackGround1);

    // game recipe screen
    mRecipeScene.setSceneRect(QRect(0,0,1920, 1080));
    mBackGround2.setPixmap(QPixmap(":/ArtAssert/EduApp_GameRecipeScreen.png"));

    auto kungBaoChickenLogo = new QToolButton();
    kungBaoChickenLogo->resize(379, 114);
    kungBaoChickenLogo->setIcon(QIcon(":/ArtAssert/Recipe_KungPaoChicken.png"));
    kungBaoChickenLogo->setIconSize(QSize(379, 114));
    kungBaoChickenLogo->move(105, 230);
    kungBaoChickenLogo->setStyleSheet("background-color: transparent;");

    mRecipeScene.addItem(&mBackGround2);
    mRecipeScene.addWidget(kungBaoChickenLogo);

    // main game screen
    mMainGameScene.setSceneRect(QRect(0,0,1920,1080));
    mBackGround3.setPixmap(QPixmap(":/ArtAssert/EduApp_GameMainRoomBackground.png"));
    CookArea* prepSink = new CookArea(QPoint(352,429), QString("prepSink"), QPixmap(":/ArtAssert/MainGameScreen_PrepSinkArea.png"));
    CookArea* cuttingBoard = new CookArea(QPoint(1265, 468), QString("cuttingBoard"), QPixmap(":/ArtAssert/MainGameScreen_CuttingBoardArea.png"));
    CookArea* stove = new CookArea(QPoint(809,370), QString("stove"), QPixmap(":/ArtAssert/MainGameScreen_StoveArea.png"));
    CookAreasList.push_back(prepSink);
    CookAreasList.push_back(cuttingBoard);
    CookAreasList.push_back(stove);


//    auto prepSinkArea = new QToolButton();
//    prepSinkArea->resize(420, 384);
//    prepSinkArea->setIcon(QIcon(":/ArtAssert/MainGameScreen_PrepSinkArea.png"));
//    prepSinkArea->setIconSize(QSize(420, 384));
//    prepSinkArea->move(330, 473);
//    prepSinkArea->setStyleSheet("background-color: transparent;");

    auto cardBox = new QLabel();
    cardBox->resize(1696, 290);
    cardBox->setPixmap(QPixmap(":/ArtAssert/MainGameScreen_CardBox.png"));
    cardBox->move(174, 780);
    cardBox->setStyleSheet("background-color: transparent;");

    FoodCard* potatoCard = new FoodCard(QPoint(266,819),QString("potato"), QPixmap(":/ArtAssert/potato_card.png"));
    foodCardsList.push_back(potatoCard);

    mMainGameScene.addItem(&mBackGround3);
    mMainGameScene.addItem(prepSink);
    mMainGameScene.addItem(cuttingBoard);
    mMainGameScene.addItem(stove);
    mMainGameScene.addWidget(cardBox);
    mMainGameScene.addItem(potatoCard);

//    mMainGameScene.addWidget(prepSinkArea);

    connect(startButton, &QPushButton::clicked, this, &CookMainGameRoom::enterRecipeLevel);
    connect(kungBaoChickenLogo, &QToolButton::clicked, this, &CookMainGameRoom::enterMainGameLevel);
    //connect(this, QMouseEvent::MouseButtonRelease, this, &CookMainGameRoom::checkCollision);

    // start card game timer
    gameLoopTimer = new QTimer(this);
    gameLoopTimer->start(10);
    connect(gameLoopTimer, &QTimer::timeout, this, &CookMainGameRoom::checkCollision);


    mStartScene.addItem(&mBackGround1);
    ui->mGameView->setScene(&mStartScene);
    ui->mGameView->setParent(this);
}

CookMainGameRoom::~CookMainGameRoom()
{
    delete ui;
}

void CookMainGameRoom::checkCollision(){
    collision();
}

void CookMainGameRoom::enterRecipeLevel(){
    ui->mGameView->setScene(&mRecipeScene);
}

void CookMainGameRoom::enterMainGameLevel(){
    ui->mGameView->setScene(&mMainGameScene);
}

void CookMainGameRoom::collision(){
    bool checkRemoveCard = false;
    for(int j = 0; j < foodCardsList.size(); j++){
        if(foodCardsList[j]->checkRelease){
            int cardIndex = j;
            for(int i = 0; i < CookAreasList.size(); i++){
                if(foodCardsList[cardIndex]->collidesWithItem(CookAreasList[i])){
                    qDebug() <<"collision happen";
                    mMainGameScene.removeItem(foodCardsList[cardIndex]);
                    foodCardsList.removeOne(foodCardsList[cardIndex]);
                    checkRemoveCard = true;
                }
            }
            if(checkRemoveCard == false){
                foodCardsList[cardIndex]->resetCardPos();
            }
        }
    }
}


