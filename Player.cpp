#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2,'@');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() 
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic   
    char input = mainGameMechsRef->getInput();
        switch(input)
        {       
            case 'a': 
                if(myDir != LEFT && myDir != RIGHT){
                    myDir = LEFT;
                    break;    
                }
            case 'w':
                if(myDir != UP && myDir != DOWN){
                    myDir = UP;
                    break;    
                }
            case 's':
                if(myDir != UP && myDir != DOWN){
                    myDir = DOWN;
                    break;    
                }
            case 'd':
                if(myDir != LEFT && myDir != RIGHT){
                    myDir = RIGHT;
                    break;    
                }
        
        }

}

void Player::movePlayer() {
    objPos currHead;
    playerPosList->getHeadElement(currHead); // Get current head position of the snake
    objPos nextHead = currHead; // Copy the current head to calculate next position

    // Determine the next position of the snake's head based on the direction
    switch(myDir) {
        case UP:
            nextHead.y--;
            break;
        case DOWN:
            nextHead.y++;
            break;
        case LEFT:
            nextHead.x--;
            break;
        case RIGHT:
            nextHead.x++;
            break;
        case STOP:
            // If the direction is STOP, don't move the player
            return;
    }

    // Wrap around if the next head position is outside the board limits
    if (nextHead.x <= 0) {
        nextHead.x = mainGameMechsRef->getBoardSizeX() - 2;
    }
    if (nextHead.x >= mainGameMechsRef->getBoardSizeX()) {
        nextHead.x = 1;
    }
    if (nextHead.y <= 0) {
        nextHead.y = mainGameMechsRef->getBoardSizeY() - 2;
    }
    if (nextHead.y >= mainGameMechsRef->getBoardSizeY()) {
        nextHead.y = 1;
    }

    // Check for food consumption
    objPos foodPosition;
    mainGameMechsRef->getFoodPos(foodPosition);
    if (nextHead.isPosEqual(&foodPosition)) {
        // Food consumed, increment score and length
        mainGameMechsRef->incrementScore();
        playerPosList->insertHead(nextHead); // Increase snake length by adding a new head position

        // Generate new food, ensuring it doesn't appear on the snake's body
        mainGameMechsRef->generateFood(*playerPosList);
    } else {
        // No food consumed, just move the snake forward
        playerPosList->insertHead(nextHead); // Add new head position
        playerPosList->removeTail(); // Remove tail position to keep the snake the same length
    }
}

