#ifndef SHIP_H
#define SHIP_H
#include "mapa.h"

class Ship
{
public:
    Ship();
    void setBoat();
    int randSide();
    int setRand();
    bool checkIsLegal(Piece &piece);

    bool checkIsBorder(int x, int y,Piece &piece);
private:
    std::vector<Piece> pieces;
   // std::map<std::string,int> statek;
};

#endif // SHIP_H
