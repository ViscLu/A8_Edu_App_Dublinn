/*
 *  @author: Jiahua Zhao, Chnegyu Yang and Yitong Lu
 *  @course: CS3505
 *  @Assignment: A8-An-Educational-App
 *  @Description: This is the main window of our project, it will generate the music play and the connect the signal and handler.
*/
#include "cookmaingameroom.h"
#include "ui_cookmaingameroom.h"
#include <QAudioOutput>

CookMainGameRoom::CookMainGameRoom(Model& model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CookMainGameRoom)
{
    ui->setupUi(this);

    // play music when game start, set the metrix
    mediaPlayer = new QMediaPlayer(this);
    outPut = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(outPut);
    mediaPlayer->setSource(QUrl("qrc:/ArtAssert/GameBackgroundMusic.wav"));
    outPut->setVolume(100);
    connect(mediaPlayer, &QMediaPlayer::playbackStateChanged, this, &CookMainGameRoom::onStateChanged);
    mediaPlayer->play();

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

    auto tomatoAndEggStirFryLogo = new QToolButton();
    tomatoAndEggStirFryLogo->resize(379, 114);
    tomatoAndEggStirFryLogo->setIcon(QIcon(":/ArtAssert/Recipe_TomatoAndEggStirFry.png"));
    tomatoAndEggStirFryLogo->setIconSize(QSize(379, 114));
    tomatoAndEggStirFryLogo->move(555, 230);
    tomatoAndEggStirFryLogo->setStyleSheet("background-color: transparent;");

    auto beefStewWithPotatoesLogo = new QToolButton();
    beefStewWithPotatoesLogo->resize(379, 114);
    beefStewWithPotatoesLogo->setIcon(QIcon(":/ArtAssert/Recipe_BeefStewWithPotatoes.png"));
    beefStewWithPotatoesLogo->setIconSize(QSize(379, 114));
    beefStewWithPotatoesLogo->move(1005, 230);
    beefStewWithPotatoesLogo->setStyleSheet("background-color: transparent;");

    auto foodDropGameLogo = new QToolButton();
    foodDropGameLogo->setText("kungBaoChicken");
    foodDropGameLogo->resize(379, 114);
    foodDropGameLogo->setIcon(QIcon(":/ArtAssert/Recipe_FoodDropGame.png"));
    foodDropGameLogo->setIconSize(QSize(379, 114));
    foodDropGameLogo->move(1455, 230);
    foodDropGameLogo->setStyleSheet("background-color: transparent;");

    mRecipeScene.addItem(&mBackGround2);
    mRecipeScene.addWidget(kungBaoChickenLogo);
    mRecipeScene.addWidget(tomatoAndEggStirFryLogo);
    mRecipeScene.addWidget(beefStewWithPotatoesLogo);
    mRecipeScene.addWidget(foodDropGameLogo);

    // main game screen
    mMainGameScene.setSceneRect(QRect(0,0,1920,1080));
    mBackGround3.setPixmap(QPixmap(":/ArtAssert/EduApp_GameMainRoomBackground.png"));
    CookArea* prepSink = new CookArea(QPoint(352,409), QString("prepSink"), QPixmap(":/ArtAssert/MainGameScreen_PrepSinkArea.png"));
    CookArea* cuttingBoard = new CookArea(QPoint(1265, 448), QString("cuttingBoard"), QPixmap(":/ArtAssert/MainGameScreen_CuttingBoardArea.png"));
    CookArea* stove = new CookArea(QPoint(809,350), QString("stove"), QPixmap(":/ArtAssert/MainGameScreen_StoveArea.png"));
    CookAreasList.push_back(prepSink);
    CookAreasList.push_back(cuttingBoard);
    CookAreasList.push_back(stove);

    auto cardBox = new QLabel();
    cardBox->resize(1696, 290);
    cardBox->setPixmap(QPixmap(":/ArtAssert/MainGameScreen_CardBox.png"));
    cardBox->move(174, 780);
    cardBox->setStyleSheet("background-color: transparent;");

    auto openMenuLogo = new QPushButton();
    openMenuLogo->resize(231, 76);
    openMenuLogo->setIcon(QIcon(":/ArtAssert/openMenuButton.png"));
    openMenuLogo->setIconSize(QSize(231, 76));
    openMenuLogo->move(40, 39);
    openMenuLogo->setStyleSheet("background-color: transparent;");

    mMainGameScene.addItem(&mBackGround3);
    mMainGameScene.addItem(prepSink);
    mMainGameScene.addItem(cuttingBoard);
    mMainGameScene.addItem(stove);
    mMainGameScene.addWidget(cardBox);
    mMainGameScene.addWidget(openMenuLogo);


    connect(openMenuLogo, &QPushButton::clicked, this, &CookMainGameRoom::openGameMenu);
    connect(&gameMenuWindow, &GameMenu::restartMainGameRoom, this, &CookMainGameRoom::restartGameRoom);
    connect(&gameMenuWindow, &GameMenu::backToRecipeLevel, this, &CookMainGameRoom::backToRecipeLevelAndClearGameLevel);

    connect(startButton, &QPushButton::clicked, this, &CookMainGameRoom::enterRecipeLevel);
    connect(startButton, &QPushButton::clicked, this, &CookMainGameRoom::OpenFile);
    connect(this, &CookMainGameRoom::readFileForOpen, &model, &Model::openGameData);

    connect(kungBaoChickenLogo, &QToolButton::clicked, this, &CookMainGameRoom::enterMainGameLevelKungBaoChicken);
    connect(tomatoAndEggStirFryLogo, &QPushButton::clicked, this, &CookMainGameRoom::enterMainGameLevelTomatoAndEggStirFry);
    connect(beefStewWithPotatoesLogo, &QPushButton::clicked, this, &CookMainGameRoom::enterMainGameLevelBeefStewWithPotatoes);
    connect(foodDropGameLogo, &QPushButton::clicked, this, &CookMainGameRoom::enterFoodDropGameRoom);

    connect(this, &CookMainGameRoom::setupMainGameLevel, &model, &Model::initMainGameRoomBaseOnSelectedRecipe);

    connect(this, &CookMainGameRoom::sendCollisionItems, &model, &Model::checkCardCollision);
    connect(this, &CookMainGameRoom::restartGameRoomRequest, &model, &Model::restartGameRoomHandler);
    connect(&model, &Model::dealNewCard, this, &CookMainGameRoom::addNewCard);
    connect(&model, &Model::initRecipeStepBoard, this, &CookMainGameRoom::addNewRecipeStep);
    connect(&model, &Model::finishCurrLevel, this, &CookMainGameRoom::showDishCard);
    connect(this, &CookMainGameRoom::resetMainGameLevel, &model, &Model::resetMainGameLevelHandler);

    // start card game timer
    gameLoopTimer = new QTimer(this);
    gameLoopTimer->start(10);
    connect(gameLoopTimer, &QTimer::timeout, this, &CookMainGameRoom::checkCollision);

    mStartScene.addItem(&mBackGround1);
    ui->mGameView->setScene(&mStartScene);
    ui->mGameView->setParent(this);
}

// Deconstructor the ui
CookMainGameRoom::~CookMainGameRoom()
{
    delete ui;
}

// check whether the card is collision with the sink, pot and bord etc while the time is out
void CookMainGameRoom::checkCollision(){
    collision();
}

// When the user clicks to start the game, he enters the menu selection page
void CookMainGameRoom::enterRecipeLevel(){
    ui->mGameView->setScene(&mRecipeScene);
}

// When the user clicks Kung Pao Chicken, they enter the level of Kung Pao Chicken.
void CookMainGameRoom::enterMainGameLevelKungBaoChicken(){
    currRecipe = "KungBaoChicken";
    ui->mGameView->setScene(&mMainGameScene);
    emit setupMainGameLevel("currRecipe");
}

// When the user clicks Tomato And Egg Stir Fry, they enter the level of Tomato And Egg Stir Fry.
void CookMainGameRoom::enterMainGameLevelTomatoAndEggStirFry(){
    currRecipe = "TomatoAndEggStirFry";
    ui->mGameView->setScene(&mMainGameScene);
    emit setupMainGameLevel("TomatoAndEggStirFry");
}

// When the user clicks Beef Stew With Potatoes, they enter the level of Beef Stew With Potatoes.
void CookMainGameRoom::enterMainGameLevelBeefStewWithPotatoes()
{
    currRecipe = "BeefStewWithPotatoes";
    ui->mGameView->setScene(&mMainGameScene);
    emit setupMainGameLevel("BeefStewWithPotatoes");
}

// When the user deals with a card, they get a brand new card based on how the user dealt with it.
void CookMainGameRoom::addNewCard(QPoint pos, QString foodName, QString path){
    if(pos.x()> 1666){
        int initX = 266;
        for(int i = 0; i <foodCardsList.size(); i++){
            foodCardsList[i]->setCardPos(QPoint(initX+100*i, 819));
        }
        FoodCard *newCard = new FoodCard(QPoint(initX+100*foodCardsList.size(),819), QString(foodName), QString(path));
        foodCardsList.push_back(newCard);
        mMainGameScene.addItem(newCard);
    }else{
        FoodCard *newCard = new FoodCard(QPoint(pos), QString(foodName), QString(path));
        foodCardsList.push_back(newCard);
        mMainGameScene.addItem(newCard);
    }
}

// Check whether the card collides with the special tool. If there is a collision, different tools will be used for different processing. If there is no collision, the card position will return to the original position.
void CookMainGameRoom::collision(){
    bool checkRemoveCard = false;
    for(int j = 0; j < foodCardsList.size(); j++){
        if(foodCardsList[j]->checkRelease){
            int cardIndex = j;
            for(int i = 0; i < CookAreasList.size(); i++){
                if(foodCardsList[cardIndex]->collidesWithItem(CookAreasList[i])){
                    qDebug() <<"collision happen: " << j << i;
                    QList<QString> collisionItems {CookAreasList[i]->getAreaType(), foodCardsList[cardIndex]->GetFoodCardName()};
                    emit sendCollisionItems(collisionItems);
                    mMainGameScene.removeItem(foodCardsList[j]);
                    foodCardsList.removeOne(foodCardsList[j]);
                    checkRemoveCard = true;
                    break;
                }
            }
            if(checkRemoveCard == false){
                foodCardsList[cardIndex]->resetCardPos();
            }
        }
    }
}

// Open the level design data of different levels and perform different initializations.
void CookMainGameRoom::OpenFile(){
    QList<QString> filenames;

    QString filename1 = ":/ArtAssert/recipeKungBaoChicken.txt";
    QString filename2 = ":/ArtAssert/recipeTomatoAndEggStirFry.txt";
    QString filename3 = ":/ArtAssert/recipeBeefStewWithPotatoes.txt";

    if(filename1.isEmpty() || filename2.isEmpty())
        return;

    filenames.push_back(filename1);
    filenames.push_back(filename2);
    filenames.push_back(filename3);
    emit readFileForOpen(filenames);
}

// Add a menu that prompts the user to operate in the game interface.
void CookMainGameRoom::addNewRecipeStep(QString recipeStepPixmap)
{
    auto recipeBox = new QToolButton();
    recipeBox->resize(434, 438);

    recipeBox->setIcon(QIcon(recipeStepPixmap));
    recipeBox->setIconSize(QSize(434, 438));
    recipeBox->move(1465, 20);
    recipeBox->setStyleSheet("background-color: transparent;");
    mMainGameScene.addWidget(recipeBox);
}

// Display ingredient cards in an orderly manner to the user.
void CookMainGameRoom::showDishCard(QString dishPixmapPath){
    auto newDishCard = new QPushButton();
    newDishCard->resize(349, 492);
    qDebug() << dishPixmapPath;
    newDishCard->setIcon(QIcon(dishPixmapPath));
    newDishCard->setIconSize(QSize(349, 492));
    newDishCard->move(845,222);
    newDishCard->setStyleSheet("background-color: transparent;");

    mMainGameScene.addWidget(newDishCard);
    connect(newDishCard, &QPushButton::clicked, this, &CookMainGameRoom::backToRecipeLevelAndClearGameLevel);
    connect(newDishCard, &QPushButton::clicked, newDishCard, &QPushButton::close);
}

// Opening the game menu provides options for restarting, continuing and returning to the original screen.
void CookMainGameRoom::openGameMenu()
{
    gameMenuWindow.show();
}

// Restart the level being played and initialize all game level data.
void CookMainGameRoom::restartGameRoom()
{
    qDebug() << "check foodcardList size: " << foodCardsList.size();
    int foodCardsListNumber = foodCardsList.size() - 1;
    for(int index = foodCardsListNumber; index >= 0; index--){
        qDebug() << "check remove" << foodCardsList[index]->GetFoodCardName();
        mMainGameScene.removeItem(foodCardsList[index]);
        foodCardsList.pop_back();
    }
    qDebug() << "check foodcardList size: " << foodCardsList.size();

    emit restartGameRoomRequest(currRecipe);
}

// Go back to the selection interface of the recipe level and discard the data of the ongoing game.
void CookMainGameRoom::backToRecipeLevelAndClearGameLevel(){
    int foodCardsListNumber = foodCardsList.size() - 1;
    for(int index = foodCardsListNumber; index >= 0; index--){
        qDebug() << "check remove" << foodCardsList[index]->GetFoodCardName();
        mMainGameScene.removeItem(foodCardsList[index]);
        foodCardsList.pop_back();
    }
    ui->mGameView->setScene(&mRecipeScene);
    emit resetMainGameLevel();
}

// Get into how to showcase Box2D's built-in card drop minigame.
void CookMainGameRoom::enterFoodDropGameRoom()
{
    foodFallDialogWindow.show();
}

// If the music playback ends, then the background music is played again.
void CookMainGameRoom::onStateChanged(QMediaPlayer::PlaybackState state)
{
    if (state == QMediaPlayer::StoppedState)
        {
            mediaPlayer->setPosition(0);
            mediaPlayer->play();
       }
}

