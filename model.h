#ifndef MODEL_H
#define MODEL_H

#include "recipedata.h"
#include <QObject>
#include <QList>
#include <foodcard.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QFileDialog>
#include <QMap>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

signals:
    void dealNewCard(QPoint pos, QString foodName, QString path);
    void initRecipeStepBoard(QString recipeStepPath);
    void finishCurrLevel(QString dishPixmapPath);

public slots:
    void checkCardCollision(QList<QString> collisionList);
    void openGameData(QList<QString> filenames);
    void resetMainGameLevelHandler();
    void initMainGameRoomBaseOnSelectedRecipe(QString recipeName);
    void restartGameRoomHandler();

private:
    QList<QList<QString>> foodCardsData;
    QList<QString> RecipeCookOrder;
    QList<RecipeData> recipeDataList;
    QList<QString> condimentList;
    QList<QString> sauceList;
    QMap<QString, RecipeData> recipeDataMap;
    QString currDishName;
    QString currDishPixmapPath;
    QString currRecipeStepBoard;

    int cardsCount;
    int cardYInitPos;
    int cardXInitPos;

    int stoveStepCount;
    bool stoveErrorProcessCheck;
    bool sameTypefoodCheck(QString cardName);
    void initializeFoodCard(QList<QList<QString>> foodCardsList, int foodCardsCount);
    void stoveProcessing(QString cardName);
    void sinkProcessing(QString cardName);
    void cuttingBoardProcessing(QString cardName);
};
#endif // MODEL_H
