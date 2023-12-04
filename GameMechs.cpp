#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
  input = '\0';
  exitFlag = false;
  boardSizeX = 20;
  boardSizeY = 10;

}

GameMechs::GameMechs(int boardX, int boardY)
{
  input = '\0';
  exitFlag = false;
  boardSizeX = boardX;
  boardSizeY = boardY;

}

// do you need a destructor?


bool GameMechs::getExitFlagStatus()
{
  return exitFlag;

}

char GameMechs::getInput() {
    if (MacUILib_hasChar()) 
    {
        input = MacUILib_getChar();
    }
    return input;
}

int GameMechs::getBoardSizeX()
{
  return boardSizeX;
}

void GameMechs::getFoodPos(objPos &returnPos) {
    returnPos = foodPos; // Assuming you have an operator= or similar method in objPos
}

int GameMechs::getBoardSizeY()
{
  return boardSizeY;
}


// GameMechs.cpp - Implement the setter methods and input handling
void GameMechs::setExitTrue() {
    exitFlag = true;
}

void GameMechs::setInput(char this_input) {
    input = this_input;
}

void GameMechs::clearInput() {
    input = '\0'; // Or '\0' if you prefer to clear to null character
}

void GameMechs::generateFood(objPosArrayList& blockOffPositions) {
    int x, y;
    bool positionOK;
    
    // Generate a random position for the food, and check if it's not overlapping with the snake's body.
    do {
        // Randomly select a position for the food that is inside the boundaries of the game board.
        x = std::rand() % (boardSizeX - 2) + 1;
        y = std::rand() % (boardSizeY - 2) + 1;
        foodPos.setObjPos(x, y, 'F');  // 'F' is the symbol for food.

        // Check if the randomly chosen position is not on the snake's body.
        positionOK = true;
        for (int i = 0; i < blockOffPositions.getSize(); i++) {
            objPos tempPos;
            blockOffPositions.getElement(tempPos, i);
            if (foodPos.isPosEqual(&tempPos)) {
                positionOK = false;
                break;  // If the position is occupied, break the loop and generate a new position.
            }
        }
    } while (!positionOK); // Continue looping until a valid, unoccupied position is found.

    // Once a valid position is found, set the food position in the game mechanics.
    this->foodPos = foodPos;
}

int GameMechs::getScore() {
    return score;
}

void GameMechs::incrementScore() {
    score++;
}

