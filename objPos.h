#ifndef OBJPOS_H
#define OBJPOS_H
// do not change anything in this class, central class
class objPos // not very well designed... but serves the purpose 
{
    public:
        int x;
        int y;
        char symbol;

        objPos();
        objPos(objPos &o); // copy constructor
        objPos(int xPos, int yPos, char sym);

        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  
        void getObjPos(objPos &returnPos); // pass by ref i.e. provide an empty objpos into this function, then the objects instance will write its own x,y, sym into the return and return it back
        char getSymbol();

        bool isPosEqual(const objPos* refPos); // pass by pointer
        
        char getSymbolIfPosEqual(const objPos* refPos); // pass by pointer
};

#endif