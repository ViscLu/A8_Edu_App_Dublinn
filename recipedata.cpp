#include "recipedata.h"

RecipeData::RecipeData(QList<QList<QString>> cardsData, QList<QString>recipeCookOrde, int cardCount, QString recipePixmapPath, bool passedLevel){
    this->foodCardsData = cardsData;
    this->recipeCookOrder = recipeCookOrde;
    this->cardCount = cardCount;
    this->recipePixmapPath = recipePixmapPath;
    this->passedLevel = passedLevel;
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
