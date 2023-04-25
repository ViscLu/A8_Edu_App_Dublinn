#ifndef RECIPEDATA_H
#define RECIPEDATA_H
#include <QString>
#include <QPixmap>

class RecipeData
{
public:
    RecipeData(QList<QList<QString>> foodCardsData, QList<QString>recipeCookOrde, int cardCount, QString recipePixmapPath, bool paassedlevel);
    void setPassedLevelTrue();
    QList<QList<QString>> getFoodCardsData();
    QList<QString> getRecipeCookOrder();
    int getCardCount();
    QString getRecipePixmapPath();
    bool checkLevelState();

private:
    QList<QList<QString>> foodCardsData;
    QList<QString> recipeCookOrder;
    int cardCount;
    QString recipePixmapPath;
    bool passedLevel;
    //QList<QString> recpieCardsData;

};

#endif // RECIPEDATA_H
