#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QWidget>
#include <QPixmap>
#include <QPalette>

namespace Ui {
class GameMenu;
}

class GameMenu : public QWidget
{
    Q_OBJECT

public:
    explicit GameMenu(QWidget *parent = nullptr);
    ~GameMenu();

private slots:
    void restartButtonHandler();
    void backButtonHandler();
    void recipeButtonHandler();

signals:
    void restartMainGameRoom();
    void backToRecipeLevel();

private:
    Ui::GameMenu *ui;
};

#endif // GAMEMENU_H
