#ifndef NODEGRAPHICITEM_H
#define NODEGRAPHICITEM_H

#include "graphicitem.h"

namespace cuteGraphLib
{
    /*!
     \brief Stellt einen Knoten im Graphen dar.

            Spezielle Eigenschaften von Knoten sind hier
            definiert.
     */
    class NodeGraphicItem : public GraphicItem
    {

    public:

        NodeGraphicItem(QRectF rec,QColor fill, QColor line);   /**< Erstellt ein NodeGraphicItem */
        ~NodeGraphicItem();
        
        QRectF boundingRect() const;
        QPainterPath shape() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); /**< Zeichnet das Item */
        void setShapeToBox(bool isBox); /**< Setzt die Form des Knoten auf Rechteck oder Ellipse. \param isBox True für Rechteck, false für Ellipse*/
        
        /*! 
            \brief Setzt die Fraben des Knoten

            \param fill die Füllfarbe des Knoten
            \param line die Linienfarbe des Knoten
            \param font die Textfarbe der Beschriftung des Knoten
        */
        void setColor(QColor &fill, QColor &line, QColor &font);
        void setColorFromAttributes();  /**< Setzt die Farbe des Knotens basierend auf den Attributen*/

    protected:

        bool isBox;                     /**< Die Form des Items. Wenn true, dann*/
        QColor fillColor;               /**< Die Füllfarbe des Items.*/
    };
}

#endif // NODEGRAPHICITEM_H
