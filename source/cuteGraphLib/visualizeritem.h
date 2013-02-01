#ifndef VISUALIZERITEM_H
#define VISUALIZERITEM_H

#include <QGraphicsScene>
#include <QObject>
#include <iostream>
#include "nodegraphicitem.h"
#include "edgegraphicitem.h"
#include <vector>
#include <map>

namespace cuteGraphLib
{
    /*!
     \brief Hält Infomrationen eines gesamten Graphen mit 
     seinen Kanten und Knoten.
     
     Verwaltet je eine Map für NodeGraphicItem und EdgeGraphicItem.
     Zusätzlich befindet sich hier die QGraphicsScene welche den Graphen
     darstellt.
     */
    class VisualizerItem : public QObject
    {

    public:

        VisualizerItem(std::string name, QGraphicsScene* scene, QObject *parent);   /**< Erstellt ein VisualizerItem */
        ~VisualizerItem();

        std::string getName() const;                                        /**< Gibt den Namen des Items zurück. */
        QGraphicsScene *getScene() const;                                   /**< Gibt die QGraphicsScene mit dem Graphen zurück. */
        
        std::map<std::string, NodeGraphicItem*> nodes;                      /**< Map mit NodeGraphicItem als Value und ID bzw Label des Nodes als Key*/
        
        EdgeGraphicItem* getEdgeForKey(std::string key);                    /**< Gibt die EdgeGraphicItem für den angebgenen Key zurück. */
        void insertEdgeWithKey(EdgeGraphicItem* item, std::string key);     /**< Fügt ein EdgeGraphicItem mit gegebenem Key hinzu. */

    private:

        std::string name;                                                   /**< Der Name des VisualizerItems */
        QGraphicsScene *scene;                                              /**< Die QGraphicsScene in die alles gezeichnet wird. */
        std::map<std::string, EdgeGraphicItem*> edges;                      /**< Map mit EdgeGraphicItem als Value und ID bzw. Label als Key. */
        
        friend class VisualizerItemFactory;
    };
}

#endif // VISUALIZERITEM_H
