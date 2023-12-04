#include "objPosArrayList.h"
#include <stdexcept>
#include <string>
using namespace std;
// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList() : sizeList(0), sizeArray(ARRAY_MAX_CAP) 
{
    aList = new objPos[ARRAY_MAX_CAP];
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (sizeList < sizeArray) {
        for (int i = sizeList; i > 0; --i) {
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos;
        ++sizeList;
    }
    else if(sizeList >= sizeArray){
        throw std::out_of_range("Full Elements.");
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (sizeList < sizeArray) {
        aList[sizeList] = thisPos;
        ++sizeList;
    }
    else if(sizeList == sizeArray){
        throw std::out_of_range("Full Elements.");
    }
}

void objPosArrayList::removeHead()
{
    if (sizeList > 0) {
        for (int i = 0; i < sizeList - 1; ++i) {
            aList[i] = aList[i + 1];
        }
        --sizeList;
    }
    else if(sizeList == 0){
        throw std::out_of_range("No Elements.");
    }
}

void objPosArrayList::removeTail()
{
    if (sizeList > 0) {
        --sizeList;
    }
    else if(sizeList == 0){
        throw std::out_of_range("No Elements.");
    }

}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if (sizeList > 0) {
        returnPos = aList[0];
    }
    else if(sizeList == 0){
        throw std::out_of_range("No Elements.");
    }
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if (sizeList > 0) {
        returnPos = aList[sizeList - 1];
    }
    else if(sizeList == 0){
        throw std::out_of_range("No Elements.");
    }
    
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index >= 0 && index < sizeArray) {
        returnPos = aList[index];
    }
    else if(index < 0 || index >= sizeArray){
        throw std::out_of_range("Invalid indexes.");
    }
}