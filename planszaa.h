#ifndef PLANSZAA_H
#define PLANSZAA_H
#include <QGraphicsItem>
#include <QPainter>
class planszaa : public QGraphicsItem
{
public:
    planszaa();

    QRectF boundingRect() const override;
    void rysuj(QPainter * event, const QStyleOptionGraphicsItem* option, QWidget* widget);
};

#endif // PLANSZAA_H
