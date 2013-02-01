#include "dialog.h"
#include <QApplication>
#include "visualizeritemfactory.h"
#include <sstream>
#include <QPointer>
#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtGui>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPointer<MainWindow> mainWindow = new MainWindow();
    mainWindow->show();
    
    int ret = app.exec();
    
    delete mainWindow;
    
    return ret;
}
