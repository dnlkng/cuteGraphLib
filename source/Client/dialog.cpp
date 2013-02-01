#include "dialog.h"
#include "ui_dialog.h"
#include "visualizeritemfactory.h"
#include <QGraphicsScene>
#include <iostream>

Dialog::Dialog(QWidget *parent, QGraphicsScene *scene) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setScene(QGraphicsScene* scene)
{
    ui->graphicsView->setScene(scene);
    update();
}
