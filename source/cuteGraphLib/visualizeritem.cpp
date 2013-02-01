#include "visualizeritem.h"

cuteGraphLib::VisualizerItem::VisualizerItem(std::string name, QGraphicsScene* scene, QObject *parent) :
    QObject(parent)
{
    this->name = name;
    this->scene = scene;
    scene->setParent(this);
}

cuteGraphLib::VisualizerItem::~VisualizerItem()
{
    delete scene;
}

std::string cuteGraphLib::VisualizerItem::getName() const
{
    return this->name;
}

QGraphicsScene *cuteGraphLib::VisualizerItem::getScene() const
{
    return this->scene;
}

cuteGraphLib::EdgeGraphicItem* cuteGraphLib::VisualizerItem::getEdgeForKey(std::string key)
{
    return edges.find(key)->second;
}

void cuteGraphLib::VisualizerItem::insertEdgeWithKey(EdgeGraphicItem* item, std::string key)
{
    edges.insert(std::pair<std::string, EdgeGraphicItem*>(key, item));
}