
#include "mapa.h"
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
            return Qt::white;
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



void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
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
    state = State::HIT;

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
    //cout << "Painting Piece..." << endl;
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

