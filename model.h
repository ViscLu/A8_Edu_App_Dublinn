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
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QFileDialog>
#include <QPainter>
#include<QResource>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

signals:
    void dealNewCard(QPoint pos, QString foodName, QString path);

public slots:
    void checkCardCollision(QList<QString> collisionList);
    void openGameData(QString filename);

private:
    QList<QList<QString>> cardsData;
    QList<QString> RecipeCookOrde;
    QList<RecipeData> recipeDataList;
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
