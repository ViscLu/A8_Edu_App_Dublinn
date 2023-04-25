#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent}
{
    cardsCount = 0;
    cardYInitPos = 819;
    cardXInitPos = 266;

    stoveStepCount = 0;
    stoveErrorProcessCheck = false;
}

void Model::initializeFoodCard(QList<QList<QString>> foodCards, int foodCardsCount){
    for(int i = 0; i < foodCardsCount; i++){
        QList<QString> foodCardInfo = foodCards[i];
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), foodCardInfo[0], foodCardInfo[1]);
        cardsCount++;
    }
}

void Model::stoveProcessing(QString cardName)
{
    if(stoveStepCount >= RecipeCookOrde.size()){
        return;
    }

    if(cardName == RecipeCookOrde[stoveStepCount]){
        stoveStepCount++;
    }else if(sameTypefoodCheck(cardName)){
        stoveStepCount++;
    }else{
        stoveStepCount++;
        stoveErrorProcessCheck = true;
    }
}

bool Model::sameTypefoodCheck(QString cardName){
    if((cardName == "green_onionCard" || cardName == "gingerCard" || cardName == "chiliCard" || cardName == "garlicCard")
            && (RecipeCookOrde[cardsCount] == "green_onionCard" || RecipeCookOrde[cardsCount] == "gingerCard"
            || RecipeCookOrde[cardsCount] == "chiliCard" || RecipeCookOrde[cardsCount] == "garlicCard")){
        return true;
    }
    return false;
}

void Model::sinkProcessing(QString cardName){
    if(cardName == "raw_chickenCard"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("raw_chickenCard_water"), ":/ArtAssert/raw_chickenCard_water.png");
    }else if(cardName == "green_onionCard"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("green_onionCard_water"), ":/ArtAssert/green_onionCard_water.png");
    }else{

    }

}

void Model::cuttingBoardProcessing(QString cardName){
    if(cardName == "raw_chickenCard" || cardName == "raw_chickenCard_water"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("raw_chicken_brisketsCard"), ":/ArtAssert/raw_chicken_brisketsCard.png");
    }else if(cardName == "green_onionCard" || cardName == "green_onionCard_water"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("green_onion_piecesCard"), ":/ArtAssert/green_onion_piecesCard.png");
    }else{

    }
}

void Model::checkCardCollision(QList<QString> collisionList){
    QString areaType = collisionList[0];
    QString cardName = collisionList[1];
    if(areaType == "prepSink"){
        sinkProcessing(cardName);
        cardsCount++;
    }else if(areaType == "stove"){
        stoveProcessing(cardName);
    }else if(areaType == "cuttingBoard"){
        cuttingBoardProcessing(cardName);
        cardsCount++;
    }
}

void Model::openGameData(QString filename){
    qDebug() <<"start check1";
    QString fileContent;
    QFile file(filename);
    if(!file.exists()){
        qDebug() <<"fall exists";
        return;
    }

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        qDebug() <<"fall";
        return;
    }

    QTextStream in(&file);

    fileContent= in.readAll();

    qDebug() <<"start check2";

    QJsonDocument doc= QJsonDocument::fromJson(fileContent.toUtf8());
    QJsonObject dataobject =doc.object();

    //QList<QList<QString>> recpieCardsData;

    // need change later
    int tempCardCount = dataobject["cardCount"].toString().toInt();
    bool tempRecipeState = dataobject["passedLevel"].toBool();
    QString tempRecipePixmapPath = dataobject["recipePixmapPath"].toString();

    qDebug() <<"tempCardCount: " <<tempCardCount;
    qDebug() <<"tempRecipeState: " <<tempRecipeState;
    qDebug() <<"tempRecipePixmapPath: " <<tempRecipePixmapPath;

    QJsonArray foodCardsDataJson = dataobject["foodCardsData"].toArray();
    QJsonArray recipeCookOrderDataJson = dataobject["recipeCookOrder"].toArray();

    QList<QString> recipeCookOrder;

    qDebug() <<"check 3"<<recipeCookOrder.size();

    for (const auto& cookOrder: recipeCookOrderDataJson){
        recipeCookOrder.push_back(cookOrder.toString());
    }

    qDebug() <<"check 3";

    for(int i = 0; i < recipeCookOrder.size();i++){
        qDebug() <<"recipe Cook order: " <<recipeCookOrder[i];
    }

    QList<QList<QString>> foodCardsData;

    qDebug() <<"check food cards: "<<foodCardsData.size();
    for (const auto& foodCardDataList: foodCardsDataJson){
        QJsonArray foodCardData = foodCardDataList.toArray();
        QList<QString> onefoodCardData;

        for(const auto& fcData: foodCardData){
            onefoodCardData.push_back(fcData.toString());
        }

        foodCardsData.push_back(onefoodCardData);
    }

    qDebug() <<"check 4";

    for(int i = 0; i < foodCardsData.size();i++){
        qDebug() <<"food cards Data: " <<foodCardsData[i][0] << "and" << foodCardsData[i][1];
    }

    initializeFoodCard(foodCardsData,tempCardCount);

    RecipeData KongBaoChichen(foodCardsData, recipeCookOrder, tempCardCount, tempRecipePixmapPath, tempRecipeState);
    recipeDataList.push_back(KongBaoChichen);
}
