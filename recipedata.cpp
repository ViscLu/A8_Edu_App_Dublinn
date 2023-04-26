#include "recipedata.h"

RecipeData::RecipeData(QList<QList<QString>> cardsData, QList<QString>recipeCookOrde, int cardCount, QString recipePixmapPath, QString dishCardPixmapPath, bool passedLevel){
    this->foodCardsData = cardsData;
    this->recipeCookOrder = recipeCookOrde;
    this->cardCount = cardCount;
    this->recipePixmapPath = recipePixmapPath;
    this->passedLevel = passedLevel;
    this->dishCardPixmapPath = dishCardPixmapPath;
}

void RecipeData::setPassedLevelTrue(){
    this->passedLevel = true;
}

QList<QList<QString>> RecipeData:: getFoodCardsData(){
    return foodCardsData;
}


QList<QString> RecipeData::getRecipeCookOrder(){
    return recipeCookOrder;
}


int RecipeData::getCardCount(){
    return cardCount;
}


QString RecipeData::getRecipePixmapPath(){
    return recipePixmapPath;
}


bool RecipeData::checkLevelState(){
    return passedLevel;
}


QString RecipeData::getDishCardPixmapPath(){
    return dishCardPixmapPath;
}
