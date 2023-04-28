/*
 *  @author: Jiahua Zhao, Chnegyu Yang and Yitong Lu
 *  @course: CS3505
 *  @Assignment: A8-An-Educational-App
 *  @Description: This class is used to store the data of the recipe
*/
#include "recipedata.h"

// Creates an instance of the recipe database from the provided data.
RecipeData::RecipeData(QList<QList<QString>> cardsData, QList<QString>recipeCookOrde, int cardCount, QString recipePixmapPath, QString dishCardPixmapPath, bool passedLevel){
    this->foodCardsData = cardsData;
    this->recipeCookOrder = recipeCookOrde;
    this->cardCount = cardCount;
    this->recipePixmapPath = recipePixmapPath;
    this->passedLevel = passedLevel;
    this->dishCardPixmapPath = dishCardPixmapPath;
}

// Set player pass to true.
void RecipeData::setPassedLevelTrue(){
    this->passedLevel = true;
}

// Returns the card name and data to be used.
QList<QList<QString>> RecipeData:: getFoodCardsData(){
    return foodCardsData;
}

// Returns the type and order of cooking ingredients.
QList<QString> RecipeData::getRecipeCookOrder(){
    return recipeCookOrder;
}

// Returns the number of cards to use.
int RecipeData::getCardCount(){
    return cardCount;
}

// Return to the recipe prompt box.
QString RecipeData::getRecipePixmapPath(){
    return recipePixmapPath;
}

// check if the player is passed the level.
bool RecipeData::checkLevelState(){
    return passedLevel;
}

// Returns the drawing path of the ingredients card.
QString RecipeData::getDishCardPixmapPath(){
    return dishCardPixmapPath;
}
