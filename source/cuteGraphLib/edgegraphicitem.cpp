//
//  EdgeGraphicItem.cpp
//  cuteGraphLib
//
//  Created by Daniel König on 07.01.13.
//
//

#include "edgegraphicitem.h"

#define Pi 3.1415926

cuteGraphLib::EdgeGraphicItem::EdgeGraphicItem(QPainterPath painterPath, QColor line) :
GraphicItem(QRectF(painterPath.boundingRect()), line), painterPath(painterPath)
{
    hasTailArrow = false;
    hasHeadArrow = true;
    penStyle = Qt::SolidLine;
    lineWidth = 1;
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
}

cuteGraphLib::EdgeGraphicItem::~EdgeGraphicItem()
{

}

QRectF cuteGraphLib::EdgeGraphicItem::boundingRect() const
{
    return (this->getClickableArea().boundingRect());
}

QPainterPath cuteGraphLib::EdgeGraphicItem::shape() const
{
    return getClickableArea();
}

QPainterPath cuteGraphLib::EdgeGraphicItem::getClickableArea() const
{
    QPainterPath path;
    QPainterPathStroker stroker;
    stroker.setWidth(20);
    path = (stroker.createStroke(painterPath));
    return path.simplified();
}

void cuteGraphLib::EdgeGraphicItem::drawNormalArrowHead()
{
    qreal arrowSize = 11;
    
    if(hasHeadArrow){
        arrowHead.clear();
        qreal angle = (painterPath.angleAtPercent(1) * Pi) / 180;
        angle -= Pi;
        arrowHead << painterPath.currentPosition();
        arrowHead << painterPath.currentPosition() + QPointF(sin(angle + Pi / 3) * arrowSize, cos(angle + Pi / 3) * arrowSize);
        arrowHead << painterPath.currentPosition() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);
    }
}

void cuteGraphLib::EdgeGraphicItem::drawNormalArrowTail()
{
    qreal arrowSize = 11;
       
    if(hasTailArrow){
        arrowTail.clear();
        qreal angle = (painterPath.angleAtPercent(0) * Pi) / 180;
        arrowTail << painterPath.pointAtPercent(0);
        arrowTail << painterPath.pointAtPercent(0) + QPointF(sin(angle + Pi / 3) * arrowSize, cos(angle + Pi / 3) * arrowSize);
        arrowTail << painterPath.pointAtPercent(0) + QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);
    }
}

void cuteGraphLib::EdgeGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(lineColor);
    
    painter->setBrush(brush);
    
    QRectF rec = boundingRect();
    
    std::map<std::string, std::string>::const_iterator iterator;
    
    if(hasHeadArrow)
    {
        iterator = userAttributes.find("arrowhead");
        if(iterator != userAttributes.end())
        {
            std::string dir = userAttributes.find("arrowhead")->second;
            
            if(dir == "normal"){
                drawNormalArrowHead();
            }
            
            if(dir == "dot"){
                if(hasHeadArrow){
                    QPointF curPos = painterPath.currentPosition();
                    painter->drawEllipse(curPos.x() - 5, curPos.y()-10, 10, 10);
                }
            }
        }
        else
        {
            drawNormalArrowHead();
        }
    }
    
    if(hasTailArrow)
    {
        iterator = userAttributes.find("arrowtail");
        if(iterator != userAttributes.end())
        {
            std::string dir = userAttributes.find("arrowtail")->second;
            
            if(dir == "normal")
                drawNormalArrowTail();
            
            if(dir == "dot")
            {
                    QPointF tailPos = painterPath.pointAtPercent(0);
                    painter->drawEllipse(tailPos.x() - 5, tailPos.y(), 10, 10);
            }
        }
        else
        {
            drawNormalArrowHead();
        }
    }
    
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    
    QPen pen;
    pen.setColor(lineColor);
    pen.setStyle(penStyle);

    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);

    
    painter->drawPolygon(arrowHead);
    painter->drawPolygon(arrowTail);
    
    pen.setWidth(lineWidth);
    painter->setPen(pen);
    painter->setBrush(QBrush(Qt::NoBrush));
    painter->drawPath(painterPath);
    
    painter->setPen(fontColor);
    painter->drawText(rec, Qt::AlignCenter, getLabel());
    painter->restore();
}


void cuteGraphLib::EdgeGraphicItem::setColor(QColor &line, QColor &font)
{
    lineColor = line;
    fontColor = font;
    update();
}

void cuteGraphLib::EdgeGraphicItem::setColorFromAttributes()
{
    std::vector<std::string> colors;
    colors.push_back("fillcolor");
    colors.push_back("color");
    colors.push_back("fontcolor");
    
    for(size_t i = 0; i < colors.size(); i++)
    {
        if(userAttributes.count(colors.at(i)) > 0)
        {
            QColor newColor;
            
            std::string colorToUse = userAttributes.find(colors.at(i))->second;
            newColor.setNamedColor(QString(colorToUse.c_str()));
            
            if(newColor.isValid())
            {
                if(colors.at(i) == "color")
                    lineColor = newColor;
                
                if(colors.at(i) == "fontcolor")
                    fontColor = newColor;
            }
            else
            {
                std::cout << "Color " << colorToUse << " is not valid!" << std::endl;
            }
        }
    }
}

void cuteGraphLib::EdgeGraphicItem::setLineWidth(double w)
{
    lineWidth = w;
}

void cuteGraphLib::EdgeGraphicItem::applyStyleFromAttributes()
{
    std::map<std::string, std::string>::const_iterator iterator = userAttributes.find("style");
    if(iterator != userAttributes.end())
    {
        std::string style = userAttributes.find("style")->second;
        if(style == "dotted")
            penStyle = Qt::DotLine;
        if(style == "solid")
            penStyle = Qt::SolidLine;
        if(style == "dashdot")
            penStyle = Qt::DashDotLine;
    }
    
    //Linienbreite:
    iterator = userAttributes.find("penwidth");
    if(iterator != userAttributes.end())
    {
        std::string style = userAttributes.find("penwidth")->second;
        lineWidth = atof(style.c_str());
    }
    
    //Pfeilspitzen:
    iterator = userAttributes.find("dir");
    if(iterator != userAttributes.end())
    {
        std::string dir = userAttributes.find("dir")->second;
        if(dir == "none"){
            hasHeadArrow = false;
            hasTailArrow = false;
        }
        
        if(dir == "both"){
            hasHeadArrow = true;
            hasTailArrow = true;
        }

        if(dir == "back"){
            hasHeadArrow = false;
            hasTailArrow = true;
        }
        
        if(dir == "forward"){
            hasHeadArrow = true;
            hasTailArrow = false;
        }
    }
    
    setColorFromAttributes();
}