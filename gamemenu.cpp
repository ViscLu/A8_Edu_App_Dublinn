#include "gamemenu.h"
#include "ui_gamemenu.h"

GameMenu::GameMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameMenu)
{
    ui->setupUi(this);
    // 470, 678
    ui->backButton->resize(317, 98);
    ui->backButton->setIcon(QIcon(":/ArtAssert/GameMenu_BackButton.png"));
    ui->backButton->setIconSize(QSize(317, 98));
    ui->backButton->move(470/2-317/2, 530);
    ui->backButton ->setStyleSheet("background-color: transparent;");

    ui->recipeButton->resize(317, 98);
    ui->recipeButton->setIcon(QIcon(":/ArtAssert/recipeMenuButton.png"));
    ui->recipeButton->setIconSize(QSize(317, 98));
    ui->recipeButton->move(470/2-317/2, 390);
    ui->recipeButton->setStyleSheet("background-color: transparent;");

    ui->restartButton->resize(317, 98);
    ui->restartButton->setIcon(QIcon(":/ArtAssert/GameMenu_RestartButton.png"));
    ui->restartButton->setIconSize(QSize(317, 98));
    ui->restartButton->move(470/2-317/2, 250);
    ui->restartButton->setStyleSheet("background-color: transparent;");

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QPixmap(":/ArtAssert/GameMainRoom_GameMenu_Background.png")));
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    //this->setWindowIcon(QIcon(":/ArtAssert/GameMainRoom_GameMenu_Background.png"));
    connect(ui->restartButton, &QPushButton::clicked, this, &GameMenu::restartButtonHandler);
    connect(ui->backButton, &QPushButton::clicked, this, &GameMenu::backButtonHandler);
    connect(ui->recipeButton, &QPushButton::clicked, this, &GameMenu::recipeButtonHandler);
}

GameMenu::~GameMenu()
{
    delete ui;
}

void GameMenu::restartButtonHandler(){
    this->hide();
    emit restartMainGameRoom();
}

void GameMenu::backButtonHandler(){
    this->hide();
}

void GameMenu::recipeButtonHandler()
{
    this->hide();
    emit backToRecipeLevel();
}
