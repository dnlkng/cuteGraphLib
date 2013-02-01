#include <QtGui>
#include "cutegraphviewer.h"
#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include <iostream>

CuteGraphViewer::CuteGraphViewer(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    itemfactory = new cuteGraphLib::VisualizerItemFactory(this);
    itemfactory->addParsableKey("foobarbaz");

    // Zweite Ebene mehr NICHT
    dotString2 = "digraph secondDot {A->B;}";
    secondItem = itemfactory->createVisualizerItem("cuteGraphLib - cuteGraph (Sub-Window)",dotString2,this);
    dialogWindow = new Dialog(this);
    dialogWindow->setScene(secondItem->getScene());
    dialogWindow->setWindowTitle(QString(secondItem->getName().c_str()));

    item = NULL;

    green = QColor(Qt::green);
    red = QColor(Qt::red);
    yellow = QColor(Qt::yellow);
    darkYellow = QColor(Qt::darkYellow);
    black = QColor(Qt::black);
    darkGray = QColor(Qt::darkGray);
    lightGray = QColor(Qt::lightGray);

}

CuteGraphViewer::~CuteGraphViewer() {

    delete itemfactory;

    if(item != NULL) {
        delete item;
    }
    delete secondItem;

}

void CuteGraphViewer::on_previewButton_clicked()
{
    if(item != NULL) {
        delete item;
        item = NULL;
    }

    // Update the contents in graphicsView
    if(!plainTextEdit->toPlainText().isEmpty()) {
        dotString1 = plainTextEdit->toPlainText().toStdString();
        item = itemfactory->createVisualizerItem("cuteGraphLib - cuteGraph (Main-Window)",dotString1,this);
        graphicsView->setScene(item->getScene());
//        secondItem->nodes.find("A")->second->signalClicked.connect(boost::bind(&CuteGraphViewer::changeScene, this, item->getScene()));
    }

    std::map<std::string, cuteGraphLib::NodeGraphicItem*>::const_iterator iterator = item->nodes.find("A");
    if(iterator != item->nodes.end())
    {
         item->nodes.find("A")->second->signalDoubleClicked.connect(boost::bind(&CuteGraphViewer::showDialog, this, dialogWindow));
         item->nodes.find("A")->second->signalClicked.connect(boost::bind(&CuteGraphViewer::foobar, this));
         item->nodes.find("A")->second->setColor(green, darkYellow, black);
    }

    iterator = item->nodes.find("B");
    if(iterator != item->nodes.end())
    {
         item->nodes.find("B")->second->signalClicked.connect(boost::bind(&CuteGraphViewer::changeColor, this, item->nodes.find("B")->second));
    }

    iterator = item->nodes.find("C");
    if(iterator != item->nodes.end())
    {
        item->nodes.find("C")->second->signalClicked.connect(boost::bind(&CuteGraphViewer::log, this, "single clicked item C"));
        item->nodes.find("C")->second->signalDoubleClicked.connect(boost::bind(&CuteGraphViewer::log, this, "double clicked item C"));
        item->nodes.find("C")->second->setColor(yellow, darkYellow, red);
    }

    iterator = item->nodes.find("D");
    if(iterator != item->nodes.end())
    {
         item->nodes.find("D")->second->signalDoubleClicked.connect(boost::bind(&CuteGraphViewer::showDialog, this, dialogWindow));
    }

    iterator = item->nodes.find("E");
    if(iterator != item->nodes.end())
    {
         item->nodes.find("E")->second->signalRightClicked.connect(boost::bind(&CuteGraphViewer::showMsgRightClick, this, "E", this));
         item->nodes.find("E")->second->signalDoubleClicked.connect(boost::bind(&CuteGraphViewer::showMsgDoubleClick, this, "E", this));
    }

    iterator = item->nodes.find("1");
    if(iterator != item->nodes.end())
    {
         item->nodes.find("1")->second->signalClicked.connect(boost::bind(&CuteGraphViewer::changeScene, this, secondItem->getScene()));
    }

    iterator = item->nodes.find("2");
    if(iterator != item->nodes.end())
    {

         item->nodes.find("2")->second->signalClicked.connect(boost::bind(&CuteGraphViewer::showMsgLeftClick, this, "2", this));
         item->nodes.find("2")->second->setColor(lightGray, darkGray, red);
    }

    iterator = item->nodes.find("3");
    if(iterator != item->nodes.end())
    {
         item->nodes.find("3")->second->signalClicked.connect(boost::bind(&CuteGraphViewer::theAnswer, this));
    }

    iterator = item->nodes.find("A");
    if(iterator != item->nodes.end())
    {
        iterator = item->nodes.find("B");
        if(iterator != item->nodes.end())
        {
            item->getEdgeForKey("A -> B")->signalClicked.connect(boost::bind(&CuteGraphViewer::log, this, "LINE ITEM CLICKED"));
            item->getEdgeForKey("A -> B")->signalOnHoverEnter.connect(boost::bind(&CuteGraphViewer::hoverEnter, this));
            item->getEdgeForKey("A -> B")->signalOnHoverLeave.connect(boost::bind(&CuteGraphViewer::hoverLeave, this));
            item->getEdgeForKey("A -> B")->signalOnHoverMove.connect(boost::bind(&CuteGraphViewer::hoverMove, this));

            item->getEdgeForKey("A -> B")->setLineWidth(2.0);
            item->getEdgeForKey("A -> B")->setColor(darkYellow, green);
        }
    }
}

void CuteGraphViewer::foobar()
{
    std::cout << "FOOBAR" << std::endl;
}

void CuteGraphViewer::theAnswer()
{
    std::cout << "is 42" << std::endl;
}

void CuteGraphViewer::log(std::string text)
{
    std::cout << "Log: " << text << std::endl;
}

void CuteGraphViewer::showMsgLeftClick(std::string name, QWidget *parent)
{
    QMessageBox::information(parent, QString(name.c_str()), "Was left clicked");
}

void CuteGraphViewer::showMsgRightClick(std::string name, QWidget *parent)
{
    QMessageBox::information(parent, QString(name.c_str()), "Was right clicked");
}

void CuteGraphViewer::showMsgDoubleClick(std::string name, QWidget *parent)
{
    QMessageBox::information(parent, QString(name.c_str()), "Was double clicked");
}

void CuteGraphViewer::hoverEnter()
{
    std::cout << "hover enter" << std::endl;
}

void CuteGraphViewer::hoverLeave()
{
    std::cout << "hover leave" << std::endl;
}

void CuteGraphViewer::hoverMove()
{
    std::cout << "hover move" << std::endl;
}

void CuteGraphViewer::changeScene(QGraphicsScene *s)
{
    graphicsView->setScene(s);
}

void CuteGraphViewer::showDialog(Dialog *d)
{
    d->show();
}

void CuteGraphViewer::changeColor(cuteGraphLib::NodeGraphicItem *node)
{
    QColor blue(Qt::blue);
    QColor black(Qt::black);
    QColor yellow(Qt::yellow);

    node->setColor(blue, black, yellow);
    std::map<std::string, std::string>::const_iterator iter = node->userAttributes.find("foobarbaz");


    if(!(iter == node->userAttributes.end()))
    {
        QMessageBox msgBox;
        msgBox.setText(QString((iter->first).c_str())+": "+QString((iter->second).c_str()));
        msgBox.exec();

    }
}
