#include "dialog.h"
#include "ui_dialog.h"
#include "mapa.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    scene->addItem(new Map(15, 15));
    scene->addItem(new Map(395, 15));
}


Dialog::~Dialog()
{
    delete ui;
}
