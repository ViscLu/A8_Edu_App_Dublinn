/*
 *  @author: Jiahua Zhao, Chnegyu Yang and Yitong Lu
 *  @course: CS3505
 *  @Assignment: A8-An-Educational-App
 *  @Description: This class provides low-level logic for initializing game data and cards.
*/
#include "model.h"

// Build a model that stores game data.
Model::Model(QObject *parent)
    : QObject{parent}
{
    cardsCount = 0;
    cardYInitPos = 819;
    cardXInitPos = 266;

    stoveStepCount = 0;
    stoveErrorProcessCheck = false;

    condimentList.push_back("green_onion_piecesCard");
    condimentList.push_back("chiliCard");
    condimentList.push_back("garlicCard");
    condimentList.push_back("star_aniseCard");
    condimentList.push_back("gingerCard");

    sauceList.push_back("soy_sauceCard");
    sauceList.push_back("SoyBean_sauceCard");
    sauceList.push_back("saltCard");
    sauceList.push_back("sugarCard");
    sauceList.push_back("waterCard");
}

// This method initializes a food card and sets the properties of the food card.
void Model::initializeFoodCard(QList<QList<QString>> foodCards, int foodCardsCount){
    for(int i = 0; i < foodCardsCount; i++){
        QList<QString> foodCardInfo = foodCards[i];
        emit dealNewCard(QPoint(cardXInitPos+100*cardsCount, cardYInitPos), foodCardInfo[0], foodCardInfo[1]);
        cardsCount++;
    }
}

// This is a function in the "void" (return type) of a class named "Model" which takes a QString argument named "cardName". The purpose of this function seems to be the processing of a stove in a cooking game.
void Model::stoveProcessing(QString cardName)
{
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

    if(stoveStepCount >= RecipeCookOrder.size()){
        if(stoveErrorProcessCheck == true){
            qDebug()<< "finish!";
            emit finishCurrLevel(":/ArtAssert/charredFoodCard.png");
        }else{
            emit finishCurrLevel(currDishPixmapPath);
        }
    }
}

// This function checks whether the given card name matches the type of food required by the recipe at the current step in the stove process. It returns a boolean value indicating whether the given card belongs to the same category of food as the required recipe item.
bool Model::sameTypefoodCheck(QString cardName){
    qDebug()<< "card name check: " << cardName;
    qDebug()<< "recipe order name check: " << RecipeCookOrder[stoveStepCount];
    if(condimentList.contains(cardName) && condimentList.contains(RecipeCookOrder[stoveStepCount])){
        return true;
    }

    if(sauceList.contains(cardName) && sauceList.contains(RecipeCookOrder[stoveStepCount])){
        return true;
    }

    return false;
}

// This method represents how a sink handles an ingredient card.
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

// This method represents how a cutting Board handles an ingredient card.
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

// This function checks for card collisions with different areas, such as the prep sink, stove, or cutting board, and performs the corresponding action based on the type of area and the card that collided with it.
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

// This function opens and reads game data files in JSON format, and updates the recipeDataList with the game data. It takes in a list of file names as input.
void Model::openGameData(QList<QString> filenames){
    for(int i = 0; i < filenames.size(); i++){
        QString fileContent;
        QFile file(filenames[i]);

        if(!file.exists()){
            qDebug() <<"exist fall";
            return;
        }

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() <<"read fall";
            return;
        }

        QTextStream in(&file);

        fileContent= in.readAll();

        QJsonDocument doc= QJsonDocument::fromJson(fileContent.toUtf8());
        QJsonObject dataobject =doc.object();

        int tempCardCount = dataobject["cardCount"].toString().toInt();
        bool tempRecipeState = dataobject["passedLevel"].toBool();
        QString tempRecipePixmapPath = dataobject["recipePixmapPath"].toString();
        QString tempDishCardPixmapPath = dataobject["dishCardPixmapPath"].toString();

        QJsonArray foodCardsDataJson = dataobject["foodCardsData"].toArray();
        QJsonArray recipeCookOrderDataJson = dataobject["recipeCookOrder"].toArray();

        QList<QString> tempRecipeCookOrder;


        for (const auto& cookOrder: recipeCookOrderDataJson){
            tempRecipeCookOrder.push_back(cookOrder.toString());
        }

        RecipeCookOrder = tempRecipeCookOrder;

        QList<QList<QString>> tempFoodCardsData;

        for (const auto& foodCardDataList: foodCardsDataJson){
            QJsonArray foodCardData = foodCardDataList.toArray();
            QList<QString> onefoodCardData;

            for(const auto& fcData: foodCardData){
                onefoodCardData.push_back(fcData.toString());
            }

            tempFoodCardsData.push_back(onefoodCardData);
        }

        RecipeData KongBaoChichen(tempFoodCardsData, tempRecipeCookOrder, tempCardCount, tempRecipePixmapPath, tempDishCardPixmapPath, tempRecipeState);
        recipeDataList.push_back(KongBaoChichen);

        file.close();
    }
}

// This function initializes the main game room based on the selected recipe. The input parameter is the name of the selected recipe. It then maps the recipe name to an index in the recipeDataList and retrieves the corresponding RecipeData object.
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

    initializeFoodCard(foodCardsData,cardCount);
    emit initRecipeStepBoard(currRecipeStepBoard);
}

// This function is a handler for restarting the game room. It resets the values of cardsCount, stoveStepCount, and stoveErrorProcessCheck to their initial values. It then calls the initializeFoodCard function to reset the food cards on the game board to their initial positions.
void Model::restartGameRoomHandler()
{
    cardsCount = 0;
    stoveStepCount = 0;
    stoveErrorProcessCheck = false;
    int cardCount = foodCardsData.size();
    initializeFoodCard(foodCardsData,cardCount);
}

// This function is responsible for resetting the main game level. It sets the cardsCount, stoveStepCount, and stoveErrorProcessCheck variables to their initial values. It also clears the foodCardsData and RecipeCookOrder variables.
void Model::resetMainGameLevelHandler()
{
    cardsCount = 0;
    stoveStepCount = 0;
    stoveErrorProcessCheck = false;

    foodCardsData.clear();
    RecipeCookOrder.clear();
}
