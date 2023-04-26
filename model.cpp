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
    qDebug()<< "order size" << RecipeCookOrder.size();
    if(cardName == "eggCard_whisked"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("eggCard_scrambled"), ":/ArtAssert/eggCard_scrambled.png");
        cardsCount++;
        return;
    }

    if(cardName == "raw_beef_cubesCard"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("beef_cubesCard_boiled"), ":/ArtAssert/beef_cubesCard_boiled.png");
        cardsCount++;
        return;
    }

    if(cardName == "potato_dicedCard"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("potato_dicedCard_fried"), ":/ArtAssert/potato_dicedCard_fried.png");
        cardsCount++;
        return;
    }

    if(cardName == RecipeCookOrder[stoveStepCount]){
        stoveStepCount++;
    }else if(sameTypefoodCheck(cardName)){
        stoveStepCount++;
    }else{
        stoveStepCount++;
        stoveErrorProcessCheck = true;
    }

    qDebug()<< "stove check: " << stoveErrorProcessCheck;
    qDebug()<< "stove count check: " << stoveStepCount;

    if(stoveStepCount >= RecipeCookOrder.size()){
        if(stoveErrorProcessCheck == true){
            qDebug()<< "finish!";
            emit finishCurrLevel(":/ArtAssert/charredFoodCard.png");
        }else{
            emit finishCurrLevel(currDishPixmapPath);
        }
    }
}

bool Model::sameTypefoodCheck(QString cardName){
    if((cardName == "green_onionCard" || cardName == "gingerCard" || cardName == "chiliCard" || cardName == "garlicCard" || cardName == "star_aniseCard")
            && (RecipeCookOrder[stoveStepCount] == "green_onionCard" || RecipeCookOrder[stoveStepCount] == "gingerCard"
            || RecipeCookOrder[stoveStepCount] == "chiliCard" || RecipeCookOrder[stoveStepCount] == "garlicCard" || RecipeCookOrder[stoveStepCount] == "star_aniseCard")){
        return true;
    }

    if((cardName == "soy_sauceCard" || cardName == "SoyBean_sauceCard" || cardName == "saltCard" || cardName == "sugarCard")
            && (RecipeCookOrder[stoveStepCount] == "soy_sauceCard" || RecipeCookOrder[stoveStepCount] == "SoyBean_sauceCard"
            || RecipeCookOrder[stoveStepCount] == "saltCard" || RecipeCookOrder[stoveStepCount] == "sugarCard")){
        return true;
    }
    return false;
}

void Model::sinkProcessing(QString cardName){
    if(cardName == "raw_chickenCard"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("raw_chickenCard_water"), ":/ArtAssert/raw_chickenCard_water.png");
    }else if(cardName == "green_onionCard"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("green_onionCard_water"), ":/ArtAssert/green_onionCard_water.png");
    }else if(cardName == "tomatoCard"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("tomatoCard_water"), ":/ArtAssert/tomatoCard_water.png");
    }else if(cardName == "eggCard"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("eggCard_water"), ":/ArtAssert/eggCard_water.png");
    }else if(cardName == "raw_beefCard"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("raw_beefCard_water"), ":/ArtAssert/raw_beefCard_water.png");
    }else if(cardName == "potatoCard"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("potatoCard_water"), ":/ArtAssert/potatoCard_water.png");
    }else{
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("washCard"), ":/ArtAssert/washCard.png");
    }
}

void Model::cuttingBoardProcessing(QString cardName){
    if(cardName == "raw_chickenCard" || cardName == "raw_chickenCard_water"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("raw_chicken_brisketsCard"), ":/ArtAssert/raw_chicken_brisketsCard.png");
    }else if(cardName == "green_onionCard" || cardName == "green_onionCard_water"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("green_onion_piecesCard"), ":/ArtAssert/green_onion_piecesCard.png");
    }else if(cardName == "tomatoCard" || cardName == "tomatoCard_water"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("tomatoCard_diced"), ":/ArtAssert/tomatoCard_diced.png");
    }else if(cardName == "eggCard" || cardName == "eggCard_water"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("eggCard_whisked"), ":/ArtAssert/eggCard_whisked.png");
    }else if(cardName == "raw_beefCard" || cardName == "raw_beefCard_water"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("raw_beef_cubesCard"), ":/ArtAssert/raw_beef_cubesCard.png");
    }else if(cardName == "potatoCard" || cardName == "potatoCard_water"){
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("potato_dicedCard"), ":/ArtAssert/potato_dicedCard.png");
    }else{
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), QString("cutCard"), ":/ArtAssert/cutCard.png");
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

void Model::openGameData(QList<QString> filenames){
    for(int i = 0; i < filenames.size(); i++){
    qDebug() <<"start check1";
    QString fileContent;
    QFile file(filenames[i]);

    if(!file.exists()){
        qDebug() <<"fall exists";
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() <<"fall";
        return;
    }

    QTextStream in(&file);

    fileContent= in.readAll();

    qDebug() <<"start check2";

    QJsonDocument doc= QJsonDocument::fromJson(fileContent.toUtf8());
    QJsonObject dataobject =doc.object();

    //QString tempRecipeName = dataobject["recipeName"].toString();
    int tempCardCount = dataobject["cardCount"].toString().toInt();
    bool tempRecipeState = dataobject["passedLevel"].toBool();
    QString tempRecipePixmapPath = dataobject["recipePixmapPath"].toString();
    QString tempDishCardPixmapPath = dataobject["dishCardPixmapPath"].toString();

    qDebug() <<"tempCardCount: " <<tempCardCount;
    qDebug() <<"tempRecipeState: " <<tempRecipeState;
    qDebug() <<"tempRecipePixmapPath: " <<tempRecipePixmapPath;
    qDebug() <<"tempDishCardPixmapPath: " <<tempDishCardPixmapPath;

    QJsonArray foodCardsDataJson = dataobject["foodCardsData"].toArray();
    QJsonArray recipeCookOrderDataJson = dataobject["recipeCookOrder"].toArray();

    QList<QString> tempRecipeCookOrder;

    qDebug() <<"check 3"<<tempRecipeCookOrder.size();

    for (const auto& cookOrder: recipeCookOrderDataJson){
        tempRecipeCookOrder.push_back(cookOrder.toString());
    }

    qDebug() <<"check 3";

    for(int i = 0; i < tempRecipeCookOrder.size();i++){
        qDebug() <<"recipe Cook order: " <<tempRecipeCookOrder[i];
    }

    RecipeCookOrder = tempRecipeCookOrder;

    QList<QList<QString>> tempFoodCardsData;

    qDebug() <<"check food cards: "<<tempFoodCardsData.size();

    for (const auto& foodCardDataList: foodCardsDataJson){
        QJsonArray foodCardData = foodCardDataList.toArray();
        QList<QString> onefoodCardData;

        for(const auto& fcData: foodCardData){
            onefoodCardData.push_back(fcData.toString());
        }

        tempFoodCardsData.push_back(onefoodCardData);
    }

    qDebug() <<"check 4";

    for(int i = 0; i < tempFoodCardsData.size();i++){
        qDebug() <<"food cards Data: " <<tempFoodCardsData[i][0] << "and" << tempFoodCardsData[i][1];
    }

    RecipeData KongBaoChichen(tempFoodCardsData, tempRecipeCookOrder, tempCardCount, tempRecipePixmapPath, tempDishCardPixmapPath, tempRecipeState);
    recipeDataList.push_back(KongBaoChichen);

    file.close();
    }
}

void Model::initMainGameRoomBaseOnSelectedRecipe(QString recipeName){
    int index = 0;
    if(recipeName == "KungBaoChicken"){
        index = 0;
    }else if(recipeName == "TomatoAndEggStirFry"){
        index = 1;
    }else if(recipeName == "BeefStewWithPotatoes"){
        index = 2;
    }

    RecipeData currentRecipe = recipeDataList[index];
    RecipeCookOrder = currentRecipe.getRecipeCookOrder();
    foodCardsData = currentRecipe.getFoodCardsData();
    int cardCount = currentRecipe.getCardCount();
    currRecipeStepBoard = currentRecipe.getRecipePixmapPath();
    currDishPixmapPath = currentRecipe.getDishCardPixmapPath();
    qDebug() <<"currDishPixmapPath: " <<currDishPixmapPath;

    for(int i = 0; i < RecipeCookOrder.size();i++){
        qDebug() <<"recipe Cook order: " <<RecipeCookOrder[i];
    }

    for(int i = 0; i < foodCardsData.size();i++){
        qDebug() <<"food cards Data: " << foodCardsData[i][0] << "and" << foodCardsData[i][1];
    }

    initializeFoodCard(foodCardsData,cardCount);
    emit initRecipeStepBoard(currRecipeStepBoard);
}

void Model::restartGameRoomHandler()
{
    cardsCount = 0;
    stoveStepCount = 0;
    stoveErrorProcessCheck = false;
    int cardCount = foodCardsData.size();
    initializeFoodCard(foodCardsData,cardCount);
    qDebug() << "check recipeCookOrder size: " << RecipeCookOrder.size();
    qDebug() << "check foodCardsData size: " << foodCardsData.size();
}

void Model::resetMainGameLevelHandler()
{
    cardsCount = 0;
    stoveStepCount = 0;
    stoveErrorProcessCheck = false;

    foodCardsData.clear();
    RecipeCookOrder.clear();
}
