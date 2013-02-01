#ifndef VISUALIZERITEMFACTORY_H
#define VISUALIZERITEMFACTORY_H

#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QObject>
#include <vector>
#include <iostream>
#include <gvc.h>
#include "nodegraphicitem.h"
#include "visualizeritem.h"
#include "edgegraphicitem.h"

namespace cuteGraphLib
{
    /*!
        \brief Factory zum Erstellen von VisualizerItems.

        Die VisualizerItemFactory nimmt einen Dot-Language-String entgegen
        und lässt von Graphviz einen Graphen layouten. Diesen Graphen wertet
        die Factory aus und erstellt ein VisualizerItem, welches eine
        QGraphicsScene mit entsprechend angeordneten Knoten(NodeGraphicItem)
        und Kanten(EdgeGraphicItem) enthält.
    */
    class VisualizerItemFactory : public QObject
    {

    public:

        VisualizerItemFactory(QObject *parent = 0);         /**< Erstellt die VisualizerItemFactory */
        ~VisualizerItemFactory();

        /*!
            Erstellt ein ViszualizerItem

            \param name der Name des ViszualizerItem
            \param dot der Dot-String, der den Graphen beschreibt
            \param parent das Parent-Objekt, für die automatische Speicherfreigabe
            
            \return das VisualizerItem
        */
        VisualizerItem *createVisualizerItem(std::string name, std::string dot, QObject *parent);

        /*!
            Um ein zusätzliches, nicht von Dot vordefiniertes Key-Value-Paar
            auszulesen, kann der Factory ein extra Key übergeben werden. Dieser
            wird dann beim parsen der Dot Attribute mit einfließen.

            \param key der zusätzliche Key
        */
        void addParsableKey(std::string key);

    private:

        GVC_t *graphvizContext;                             /**< Hier speichert Graphivz alle kontextrelevanten Daten. */
        graph_t *graph;                                     /**< Die Struktur des Graphen. */
        std::vector<std::string> additionalKeysToParse;     /**< Die zusätzlichen Keys für's Dot-Parsing. */
        double scale;                                       /**< Die Skalierung für das Zeichnen */
        std::string name;                                   /**< Der Name des Graphen */
        std::vector<Agedge_t*> edges;                       /**< Alle Kanten eines Graphen */
        
        /*!
            Liest die Key-Value-Attribute aus der 
            Graphviz-Knotenstruktur und legt diese
            im GraphicItem ab.
        */
        void parseAttributes(GraphicItem *item, Agnode_t *node);
        void parseAttributes(GraphicItem *item, Agedge_t *edge);
        QRectF getRectForGraph();
        void addNodesToItem(VisualizerItem &item);
        void addEdgesToItem(VisualizerItem &item);
        void addEdgesToScene(QGraphicsScene &scene, VisualizerItem &item);
        void addNodesToScene(QGraphicsScene &scene, VisualizerItem &item);
    };
}



#endif // VISUALIZERITEMFACTORY_H
