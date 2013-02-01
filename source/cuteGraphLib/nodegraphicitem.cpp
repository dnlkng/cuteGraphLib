#include "nodegraphicitem.h"

cuteGraphLib::NodeGraphicItem::NodeGraphicItem(QRectF rec, QColor fill, QColor line) :
    GraphicItem(rec, line)
{
    isBox = true;
    fillColor = fill;
}

cuteGraphLib::NodeGraphicItem::~NodeGraphicItem()
{

}

QRectF cuteGraphLib::NodeGraphicItem::boundingRect() const
{
    return (this->boundingBox);
}

QPainterPath cuteGraphLib::NodeGraphicItem::shape() const
{
    QPainterPath path;
    if(isBox)
    {
        path.addRect(boundingRect());
    }
    else
    {
        path.addEllipse(boundingRect());
    }
    return path;
}

void cuteGraphLib::NodeGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    
    //Check if item is invisible:
    std::map<std::string, std::string>::const_iterator iterator = userAttributes.find("style");
    if(iterator != userAttributes.end())
    {
        std::string style = userAttributes.find("style")->second;
        if(style == "invis")
            return;
    }
        
    QRectF rec = boundingRect();
    QBrush brush(fillColor);
    QPainterPath path;
    
    path.closeSubpath();

//    painter->save();
//    painter->setRenderHint(QPainter::Antialiasing);
    
    if(isBox)
    {
        path.addRect(rec);
    }
    else
    {
        path.addEllipse(rec);
    }
    
    painter->fillPath(path,fillColor);

    painter->setPen(lineColor);
    painter->drawPath(path);
    
    painter->setPen(fontColor);
    painter->drawText(rec, Qt::AlignCenter, getLabel());
//    painter->restore();
}

void cuteGraphLib::NodeGraphicItem::setShapeToBox(bool isBox)
{
    this->isBox = isBox;
}

void cuteGraphLib::NodeGraphicItem::setColor(QColor &fill, QColor &line, QColor &font)
{
    fillColor = fill;
    GraphicItem::setColor(line, font);
}

void cuteGraphLib::NodeGraphicItem::setColorFromAttributes()
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
                if(colors.at(i) == "fillcolor")
                       fillColor = newColor;
                
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
