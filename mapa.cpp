#include "mapa.h"
#include "mapa.h"
#include <ctime>
#include <qgraphicsitem.h>
#include <stdio.h>
#include <iostream>
#include <QGraphicsSceneMouseEvent>


using namespace std;

Qt::GlobalColor getColor(State state) {
    switch (state) {
        case SHIP:
            return Qt::black;
        case HIT:
            return Qt::red;
        case MISS:
            return Qt::gray;
        case BLANK:
            return Qt::cyan;
        case BLOCK:
            return Qt::darkCyan;
    }
}


// size - wymiar mapy, ilosc kratek wysokosci / szerokosci
// x0, y0 - wspolrzedne lewego gornego rogu
//
Map::Map(int x0, int y0, int size, int pieceSize)
{
    this->size = size;

    int y = y0;
    for (int i = 0; i < size; i++) {

        vector<Piece*> *row = new vector<Piece*>();

        int x = x0;
        for (int j = 0; j < size; j++) {
            cout << "x " << x <<", y " << y << endl;//"x " <<"x " <<
            Piece *piece = new Piece(x, y, pieceSize);
            row->push_back(piece);
            x = x + pieceSize;
        }
        this->pieces.push_back(*row);
        y = y + pieceSize;
    }
}



QRectF Map::boundingRect() const
{
    return QRectF(10,10, 310, 310);
}

bool Map::checkPosition(int x ,int y){
    if(x <= 9 && x >= 0)
    {
        if(y <= 9 && y >= 0)
        {
    if(pieces[x][y]->getState() == 3){
       return true;
    }
        }}

       return false;

}
bool Map::checkBlock(int x,int y)
{
    if(x <= 9 && x >= 0)
    {
        if(y <= 9 && y >= 0)
        {
            if(pieces[x][y]->getState() == 3  || pieces[x][y]->getState() == 4 )
            {
                return true;
            }
        }
        else
        {
                return true;
        }
    }
    else
    {
        return true;
    }
    return false;
}

bool Map::checkBoard(int x, int y)
{
    if(x <= 9 && x >= 0)
    {
        if(y <= 9 && y>= 0)
        {
            if(checkPosition(x,y) == true)
            {
                return true;
            }
        }
    }
    return false;
}


void Map::push(int &x,int &y, int kierunek)
{
    switch(kierunek)
    {
        case 1:
            x--;
        break;
        case 2:
            y++;
        break;
        case 3:
            x++;
        break;
        case 4:
           y--;
        break;
    }
}
void Map::turn_right(int &kierunek){
    kierunek++;
        if(kierunek == 5)
        {
            kierunek = 1;
        }
}
void Map::turn_left(int &kierunek)
{
    kierunek--;
        if(kierunek == 0)
        {
            kierunek = 4;
        }
}

void Map::rotate180(int &kierunek)
{
    for(int i = 0; i<2; i++)
    {
        kierunek++;
        if(kierunek == 5)
        {
            kierunek = 1;
        }
    }
}

bool Map::test_dookola(int px, int py, int kier,int rozmiar)
{
    rotate180(kier);
    push(px,py,kier);

        if(checkPosition(px,py) == false)
            return  false;
    turn_right(kier);
    push(px,py,kier);
        if(checkPosition(px,py) == false)
            return  false;
    turn_right(kier);
        for(int i = rozmiar+1; i<0; i--){
            push(px,py,kier);
            if(checkBlock(px,py) == false)
                return false;
        }
    turn_right(kier);
        for(int i=0;i<2;i++)
                {
                    push(px,py,kier);
                    if(checkBlock(px,py)==false)
                    return false;
                }
        turn_right(kier);
        for(int i=rozmiar+1;i<0;i--)
                {
                    push(px,py,kier);
                    if(checkBlock(px,py)==false)
                    return false;
                }
                return true;
}

bool Map::check_all_boat(int x,int y, int kierunek, int rozmiar)
{
    int px = x;
    int py = y;
    bool test = true;
        for(int i=rozmiar;i>1;i--)
        {
            push(px,py,kierunek);
            if(checkBoard(px,py) == false)
            {
                test = false;
                break;
            }
        }
  // bool koniec = true;

        if(test == true)
        {
            px = x;
            py = y;

            if(test_dookola(px,py,kierunek,rozmiar) == true)
            {
                return true;
            }
        }
        return false;
}


void Map::setBlock(int x,int y)
{
    if(x <= 9 && x>=0)
    {
        if(y<=9 && y>=0)
        {
           pieces[x][y]->setState(BLOCK);
        }
    }
}
void Map::setBoad(int x,int y)
{
    pieces[x][y]->setState(SHIP);
}

void Map::setT(int px,int py,int kier,int rozmiar)
{
    rotate180(kier);
    push(px,py,kier);
    turn_right(kier);
    push(px,py,kier);
    turn_right(kier);
    setBlock(px,py);
    for(int i = rozmiar+1;i>0;i--)
    {
        push(px,py,kier);
        setBlock(px,py);
    }
    turn_right(kier);
    push(px,py,kier);
    turn_right(kier);
    setBlock(px,py);
    for(int k = rozmiar;k>0;k--)
    {
        push(px,py,kier);
        setBoad(px,py);
    }
    push(px,py,kier);
    setBlock(px,py);
    turn_left(kier);
    push(px,py,kier);
    turn_left(kier);
    setBlock(px,py);
    for(int i = rozmiar+1;i>0;i--)
    {
        push(px,py,kier);
        setBlock(px,py);
    }
}

Piece *Map::getPiece(int row, int col){
    return this->pieces[row][col];
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    srand( time( NULL ) );
    int x;
    int y;
    for(int k=0;k<5;k++)
        {
            int rozmiar=0;
            switch(k)
            {
                case 0:
                    rozmiar=5;
                    break;
                case 1:
                    rozmiar=4;
                    break;
                case 2:
                    rozmiar = 3;
                    break;
                case 3:
                    rozmiar = 3;
                    break;
                case 4:
                    rozmiar = 2;
                    break;

            }
     for(;;)
     {
          x=( rand() % 10 );
           y= ( rand() % 10 );

           if(checkPosition(x,y) == true)
           {
            int kierunek = (rand()%4)+1;
            if(check_all_boat(x,y,kierunek,rozmiar) == true)
            {
                setT(x,y,kierunek,rozmiar);
                break;
            }
           }
     }
   }

    for(std::vector<int>::size_type row = 0; row != pieces.size(); row++) {
        for(std::vector<int>::size_type col = 0; col != pieces[row].size(); col++) {
            pieces[row][col]->paint(painter, option, widget);
        }
    }
}



void Map::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    cout << event->pos().x() << ", " << event->pos().y() << endl;
}




Piece::Piece(const Piece &piece)
{
    qtRectangle = piece.qtRectangle;
    state = piece.state;
}


Piece::Piece(int x, int y, int size) {
    cout << "Creating Piece..." << endl;
    qtRectangle = QRect(x, y, size, size);
    state = State::BLANK;

}


QRectF Piece::boundingRect() const
{
    return QRectF(qtRectangle.x(), qtRectangle.y(), qtRectangle.width(), qtRectangle.height());
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    cout << "Painting Piece..." << endl;
    Qt::GlobalColor color = getColor(state);
    QBrush brush(color);

    painter->fillRect(qtRectangle, brush);
    painter->drawRect(qtRectangle);
}

void Piece::setState(State state)
{
    this->state = state;
}


State Piece::getState()
{
   return state;
}

