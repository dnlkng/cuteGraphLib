#include "visualizeritemfactory.h"

#define DPI 96.0    /// DPI des Bildschirms.
#define GDPI 72.0   /// DPI, welche von Graphviz intern benutzt wird. 
#define MID 2
#define STEP 3
#define START 0

cuteGraphLib::VisualizerItemFactory::VisualizerItemFactory(QObject *parent) :
    QObject(parent)
{
    this->setParent(parent);
    scale = (DPI/GDPI);
    graph = NULL;
    graphvizContext = gvContext();
}

cuteGraphLib::VisualizerItemFactory::~VisualizerItemFactory()
{
    gvFreeContext(graphvizContext);
}

void cuteGraphLib::VisualizerItemFactory::parseAttributes(GraphicItem *item, Agedge_t *edge)
{
    std::vector<std::string> keysToCheck = additionalKeysToParse;
    keysToCheck.push_back("shape");
    keysToCheck.push_back("fillcolor");
    keysToCheck.push_back("color");
    keysToCheck.push_back("fontcolor");
    keysToCheck.push_back("style");
    keysToCheck.push_back("penwidth");
    keysToCheck.push_back("dir");
    keysToCheck.push_back("arrowhead");
    keysToCheck.push_back("arrowtail");
    
    for(size_t i=0; i< keysToCheck.size(); i++)
    {
        std::string &key = keysToCheck.at(i);
        char *value = agget(edge, const_cast<char*>(key.c_str()));
        
        if(value && strcmp(value, ""))
            item->userAttributes.insert(std::pair<std::string, std::string>(key, std::string(value)));
    }
}

void cuteGraphLib::VisualizerItemFactory::parseAttributes(GraphicItem *item, Agnode_t *node)
{
    std::vector<std::string> keysToCheck = additionalKeysToParse;
    keysToCheck.push_back("shape");
    keysToCheck.push_back("fillcolor");
    keysToCheck.push_back("color");
    keysToCheck.push_back("fontcolor");
    keysToCheck.push_back("style");

    for(size_t i=0; i< keysToCheck.size(); i++)
    {
        std::string &key = keysToCheck.at(i);
        char *value = agget(node, const_cast<char*>(key.c_str()));
        
        if(value && strcmp(value, ""))
            item->userAttributes.insert(std::pair<std::string, std::string>(key, std::string(value)));
    }
}

void cuteGraphLib::VisualizerItemFactory::addParsableKey(std::string key)
{
    additionalKeysToParse.push_back(key);
}

QRectF cuteGraphLib::VisualizerItemFactory::getRectForGraph()
{
    int x1 = graph->u.bb.LL.x * scale;
    int y1 = graph->u.bb.LL.y * scale;
    int x2 = graph->u.bb.UR.x * scale;
    int y2 = graph->u.bb.UR.y * scale;
    
    return QRectF(x1,y1,x2,y2);
}

void cuteGraphLib::VisualizerItemFactory::addNodesToItem(VisualizerItem &item)
{    
    for(Agnode_t *actualNode = agfstnode(graph); actualNode; actualNode = agnxtnode(graph, actualNode))
    {
        for (Agedge_t *actualEdge = agfstout(graph, actualNode); actualEdge; actualEdge = agnxtout(graph, actualEdge))
            edges.push_back(actualEdge);

        double x = actualNode->u.coord.x*scale  - (actualNode->u.width*DPI)/MID;
        double y = (graph->u.bb.UR.y - actualNode->u.coord.y) * scale - (actualNode->u.height*DPI)/MID;
        double h = actualNode->u.height * DPI;
        double w = actualNode->u.width * DPI;
        QRectF myRect(x, y, w, h);
        
        cuteGraphLib::NodeGraphicItem *myItem = new cuteGraphLib::NodeGraphicItem(myRect,Qt::red,Qt::darkRed);
        
        std::string textLabel(actualNode->u.label->text);
        myItem->setLabel(actualNode->u.label->text);
        item.nodes.insert(std::pair<std::string, cuteGraphLib::NodeGraphicItem*>(textLabel, myItem));
        
        parseAttributes(myItem, actualNode);
        myItem->setColorFromAttributes();
        
        boolean isBox = strcmp(actualNode->u.shape->name,"box") == 0;
        myItem->setShapeToBox(isBox);
    }
}

void cuteGraphLib::VisualizerItemFactory::addEdgesToItem(VisualizerItem &item)
{
    for(size_t i=0; i< edges.size(); i++)
    {
        Agedge_t *edge = edges.at(i);
        QPainterPath path;
        
        //Calculate the path from the spline (only one spline, as the graph is strict. If it
        //wasn't, we would have to iterate over the first list too)
        //Calculate the path from the spline (only one as the graph is strict)
        if((edge->u.spl->list != 0) && (edge->u.spl->list->size%STEP == 1))
        {
            //If there is a starting point, draw a line from it to the first curve point
            if(edge->u.spl->list->sflag)
            {
                path.moveTo(edge->u.spl->list->sp.x*(scale),
                            (graph->u.bb.UR.y - edge->u.spl->list->sp.y)*(scale));
                path.lineTo(edge->u.spl->list->list[START].x*(scale),
                            (graph->u.bb.UR.y - edge->u.spl->list->list[START].y)*(scale));
            }
            else
            {
                path.moveTo(edge->u.spl->list->list[START].x*(scale),
                            (graph->u.bb.UR.y - edge->u.spl->list->list[START].y)*(scale));
            }
            
            //Loop over the curve points
            for(int i=1; i<edge->u.spl->list->size; i+=STEP)
            {
                path.cubicTo(edge->u.spl->list->list[i].x*(scale),
                             (graph->u.bb.UR.y - edge->u.spl->list->list[i].y)*(scale),
                             edge->u.spl->list->list[i+1].x*(scale),
                             (graph->u.bb.UR.y - edge->u.spl->list->list[i+1].y)*(scale),
                             edge->u.spl->list->list[i+2].x*(scale),
                             (graph->u.bb.UR.y - edge->u.spl->list->list[i+2].y)*(scale));
            }
            
            //If there is an ending point, draw a line to it
            if(edge->u.spl->list->eflag)
            {
                path.lineTo(edge->u.spl->list->ep.x*(scale),
                            (graph->u.bb.UR.y - edge->u.spl->list->ep.y)*(scale));
            }
        }
        
        cuteGraphLib::EdgeGraphicItem *line = new cuteGraphLib::EdgeGraphicItem(path, Qt::black);
        parseAttributes(line, edge);
        line->applyStyleFromAttributes();
        
//        scene.addItem(line);
        
        std::string key = std::string(ND_label(edge->tail)->text);
        key.append(" -> ");
        key.append(ND_label(edge->head)->text);
        
        item.insertEdgeWithKey(line, key);
    }

}

void cuteGraphLib::VisualizerItemFactory::addEdgesToScene(QGraphicsScene &scene, VisualizerItem &item)
{
    std::map<std::string, EdgeGraphicItem*>::iterator iter;
    for (iter = item.edges.begin(); iter != item.edges.end(); ++iter) {
        scene.addItem(iter->second);
    }
}

void cuteGraphLib::VisualizerItemFactory::addNodesToScene(QGraphicsScene &scene, VisualizerItem &item)
{
    std::map<std::string, NodeGraphicItem*>::iterator iter;
    for (iter = item.nodes.begin(); iter != item.nodes.end(); ++iter) {
        scene.addItem(iter->second);
    }
}

cuteGraphLib::VisualizerItem* cuteGraphLib::VisualizerItemFactory::createVisualizerItem(std::string name, std::string dot, QObject *parent)
{
    this->name = name;
    graph = agmemread(const_cast<char*>(dot.c_str()));
    gvLayout(graphvizContext, graph, "dot");
    
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(getRectForGraph());
    
    VisualizerItem *visualizerItem = new VisualizerItem(this->name, scene ,parent);
    addNodesToItem(*visualizerItem);
    addEdgesToItem(*visualizerItem);
    addEdgesToScene(*scene, *visualizerItem);
    addNodesToScene(*scene, *visualizerItem);
    
    gvFreeLayout(graphvizContext, graph);
    agclose(graph);
    edges.clear();
    return visualizerItem;
}
