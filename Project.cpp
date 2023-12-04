#include <iostream>
#include <chrono>
#include <thread>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"






using namespace std;

#define DELAY_CONST 100

GameMechs* myGM;
Player* myPlayer;



void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void) {
    Initialize();

    while(myGM->getExitFlagStatus() == false) {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void) 
{
    MacUILib_init();
    MacUILib_clearScreen();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));


    myGM = new GameMechs(26,13);
    myPlayer = new Player(myGM);

    // Generate the initial food after player has been instantiated
    objPosArrayList* playerPositionsList = myPlayer->getPlayerPos();
    objPos playerPosition;
    if (playerPositionsList->getSize() > 0) {
        playerPositionsList->getHeadElement(playerPosition); // Assuming the player's current position is at the head
    }

    // Create a new objPosArrayList for generateFood
    objPosArrayList blockOffPositions;
    blockOffPositions.insertHead(playerPosition); // Add player's position to the list

    // Generate the initial food, avoiding the player's current position
    myGM->generateFood(blockOffPositions);
}

void GetInput(void) 
{
    myGM->getInput();
    char currInput;
    currInput = myGM->getInput();
    if(currInput == 27){
        myGM->setExitTrue();
    }
}

void RunLogic(void) 
{   
    
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    
    myGM->clearInput();

}

void DrawScreen(void) {
    MacUILib_clearScreen();

    bool drawn;

    // objPos tempPos;
    // myPlayer->getPlayerPos(tempPos);
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;
    // Retrieve food position to draw
    objPos foodPosition;
    myGM->getFoodPos(foodPosition);

    for(int y = 0; y < myGM->getBoardSizeY(); ++y)
    {
        for(int x = 0; x < myGM->getBoardSizeX(); ++x)
        {
            drawn = false;
            for(int i = 0; i < playerBody->getSize(); i++)
            {
                playerBody->getElement(tempBody,i);
                if(tempBody.x == x && tempBody.y == y){
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }
            if(drawn) continue;
            if(x == 0 || x == myGM->getBoardSizeX() - 1 || y == 0 || y == myGM->getBoardSizeY() - 1)
            {
                MacUILib_printf("%c", '#');
            }
            // Draw the food
            else if(foodPosition.x != -1 && foodPosition.y != -1 && x == foodPosition.x && y == foodPosition.y) {
                MacUILib_printf("%c", foodPosition.symbol);
            }
            else{
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("%c", '\n');
    }
    MacUILib_printf("%c", '\n');

    // MacUILib_printf("score: %d\n", myGM->getScore());

    

    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void) {
    MacUILib_clearScreen();
    MacUILib_uninit();

    delete myGM;
    delete myPlayer;

    
}