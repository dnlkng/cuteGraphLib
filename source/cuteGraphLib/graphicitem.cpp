#include "graphicitem.h"

cuteGraphLib::GraphicItem::GraphicItem(QRectF rec, QColor line) :
    boundingBox(rec)
{
    fontColor = Qt::black;
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
}

cuteGraphLib::GraphicItem::~GraphicItem()
{

}

QRectF cuteGraphLib::GraphicItem::boundingRect() const
{
    return boundingBox;
}

void cuteGraphLib::GraphicItem::setLabel(const QString &newlabel)
{
    label = newlabel;
}

const QString &cuteGraphLib::GraphicItem::getLabel() const
{
    return label;
}

void cuteGraphLib::GraphicItem::addAdditionalUserAttribute(std::string key, std::string value)
{
    userAttributes.insert(std::pair<std::string, std::string>(key, value));
}

void cuteGraphLib::GraphicItem::setColor(QColor &line, QColor &font)
{
    lineColor = line;
    fontColor = font;
    
    update();
}

void cuteGraphLib::GraphicItem::setColorFromAttributes()
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
                std::cout << "Color " << colorToUse << " is not valid!" << std::endl;
        }
    }
}

void cuteGraphLib::GraphicItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   
}

void cuteGraphLib::GraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        signalRightClicked();
    else
        signalClicked();
}

void cuteGraphLib::GraphicItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    signalDoubleClicked();
}

void cuteGraphLib::GraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
    signalOnHoverEnter();
}

void cuteGraphLib::GraphicItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
    signalOnHoverLeave();
}

void cuteGraphLib::GraphicItem::hoverMoveEvent(QGraphicsSceneHoverEvent * event)
{
    signalOnHoverMove();
}
