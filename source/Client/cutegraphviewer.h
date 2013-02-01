#ifndef CUTEGRAPHVIEWER_H
#define CUTEGRAPHVIEWER_H

#include "ui_cutegraphviewer.h"
#include "visualizeritemfactory.h"
#include "visualizeritem.h"
#include "dialog.h"

class CuteGraphViewer : public QWidget, public Ui::Form
{
    Q_OBJECT

public:
    CuteGraphViewer(QWidget *parent = 0);
    ~CuteGraphViewer();

    std::string dotString1;
    std::string dotString2;

    cuteGraphLib::VisualizerItemFactory *itemfactory;
    cuteGraphLib::VisualizerItem *item;
    cuteGraphLib::VisualizerItem *secondItem;

    Dialog *dialogWindow;

    void setText();

    void foobar();
    void theAnswer();
    void log(std::string text);
    void showMsgLeftClick(std::string name, QWidget *parent = 0);
    void showMsgRightClick(std::string name, QWidget *parent = 0);
    void showMsgDoubleClick(std::string name, QWidget *parent = 0);
    void hoverEnter();
    void hoverLeave();
    void hoverMove();
    void changeScene(QGraphicsScene *s);
    void showDialog(Dialog *d);
    void changeColor(cuteGraphLib::NodeGraphicItem *node);

    QColor green;
    QColor red;
    QColor yellow;
    QColor darkYellow;
    QColor black;
    QColor darkGray;
    QColor lightGray;

public Q_SLOTS:
    void on_previewButton_clicked();

private:

//    struct WrapperClass
//    {
//        void foobar()
//        {
//            std::cout << "FOOBAR" << std::endl;
//        }

//        void theAnswer()
//        {
//            std::cout << "is 42" << std::endl;
//        }

//        void log(std::string text)
//        {
//            std::cout << "Log: " << text << std::endl;
//        }

//        void showMsgLeftClick(std::string name, QWidget *parent = 0)
//        {
//            QMessageBox::information(parent, QString(name.c_str()), "Was left clicked");
//        }

//        void showMsgRightClick(std::string name, QWidget *parent = 0)
//        {
//            QMessageBox::information(parent, QString(name.c_str()), "Was right clicked");
//        }

//        void showMsgDoubleClick(std::string name, QWidget *parent = 0)
//        {
//            QMessageBox::information(parent, QString(name.c_str()), "Was double clicked");
//        }

//        void hoverEnter()
//        {
//            std::cout << "hover enter" << std::endl;
//        }

//        void hoverLeave()
//        {
//            std::cout << "hover leave" << std::endl;
//        }

//        void hoverMove()
//        {
//            std::cout << "hover move" << std::endl;
//        }

//        void changeScene(QPointer<Dialog> d, QGraphicsScene *s)
//        {
//            d->setScene(s);
//        }

//        void showDialog(QPointer<Dialog> d)
//        {
//            d->show();
//        }

//        void changeColor(cuteGraphLib::NodeGraphicItem *node)
//        {
//            QColor blue(Qt::blue);
//            QColor black(Qt::black);
//            QColor yellow(Qt::yellow);

//            node->setColor(blue, black, yellow);
//            std::map<std::string, std::string>::const_iterator iter = node->userAttributes.find("foobarbaz");


//            if(!(iter == node->userAttributes.end()))
//            {
//                QMessageBox msgBox;
//                msgBox.setText(QString((iter->first).c_str())+": "+QString((iter->second).c_str()));
//                msgBox.exec();

//            }
//        }
//    };
};

#endif
