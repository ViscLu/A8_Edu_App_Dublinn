#ifndef RECIPEDATA_H
#define RECIPEDATA_H
#include <QString>
#include <QPixmap>

class RecipeData
{
public:
    RecipeData(QList<QList<QString>> foodCardsData, QList<QString>recipeCookOrde, int cardCount, QString recipePixmapPath, QString dishCardPixmapPath, bool paassedlevel);
    void setPassedLevelTrue();
    QList<QList<QString>> getFoodCardsData();
    QList<QString> getRecipeCookOrder();
    int getCardCount();
    QString getRecipePixmapPath();
    bool checkLevelState();
    QString getDishCardPixmapPath();

private:
    QList<QList<QString>> foodCardsData;
    QList<QString> recipeCookOrder;
    int cardCount;
    QString recipePixmapPath;
    bool passedLevel;
    QString dishCardPixmapPath;
};

#endif // RECIPEDATA_H
