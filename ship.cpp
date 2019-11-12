#include "ship.h"

Ship::Ship()
{


}


int Ship::setRand(){
    return 1+rand()%10;
}


int Ship::randSide(){
    return 1+rand()%4;
}


bool Ship::checkIsLegal(Piece &piece){
    if(piece.getState() == BLANK)
    {
        return true;
    }
    else
    {
        return false;
    }
}



/*
bool Ship::checkIsBorder(int x, int y,Piece &piece){
    if(piece.getState() != SHIP)
    {
        return true;
    }
    return false;
}
void Ship::setBoat(int x, int y)
{
        x = setRand();
        y = setRand();
   
         Piece* Map::getPiece(int row, int col)->State == 
}
*/




