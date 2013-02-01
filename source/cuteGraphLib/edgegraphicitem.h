#ifndef EDGEGRAPHICITEM_H
#define EDGEGRAPHICITEM_H

#include "graphicitem.h"
#include <QPainterPath>

namespace cuteGraphLib
{
    /*!
     \brief Stellt eine Kante im Graphen dar.

            Spezielle Eigenschaften von Kanten sind hier
            definiert.
     */
    class EdgeGraphicItem : public GraphicItem
    {

    public:

        EdgeGraphicItem(QPainterPath painterPath, QColor line); /**< Erstellt ein EdgeGraphicItem. */
        ~EdgeGraphicItem(); 

        QRectF boundingRect() const;
        QPainterPath shape() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); /**< Zeichnet das EdgeGraphicItem */
        
        /*!
            Setzt die Farbe der Kante.

            \param line die Linienfarbe
            \param font die Textfarbe der Beschriftung
        */
        void setColor(QColor &line, QColor &font);  /**< Setzt die Linien- und Schriftfarbe. */
        void setColorFromAttributes();              /**< Setzt die Frabatribute aus den User-Atributen des Dot-Strings. */
        void setLineWidth(double width);            /**< Setzt die Breite der dargestellten Linie. */
        void applyStyleFromAttributes();            /**< Setzt die Linienartatribute aus den User-Atributen des Dot-Strings. */

    protected:
        
        qreal lineWidth;                        /**< Die Breite der dargestellten Linie. */
        qreal clickableLineWidth;               /**< Die Breite des klickbaren Bereichs auf der Linie. */
        QPainterPath painterPath;               /**< Zum Zeichnen der Linie. */
        QPolygonF arrowHead;                    /**< Die Pfeilspitze für den Anfang. */
        QPolygonF arrowTail;                    /**< Die Pfeilspitze für das Ende. */
        Qt::PenStyle penStyle;                  /**< Der LinenStyle (Dashed, Solid) siehe enum Qt::PenStyle*/
        
        bool hasTailArrow;                   /**< Gibt an ob am Ende eine Pfeilspitze gezeichnet werden soll */
        bool hasHeadArrow;                   /**< Gibt an ob am Start eine Pfeilspitze gezeichnet werden soll */
        
        QPainterPath getClickableArea() const;  /**< Gibt den Klickbereich zurück. */
        void drawNormalArrowHead();             /**< Zeichnet eine normale Pfeilespitze */
        void drawNormalArrowTail();             /**< Zeichnet eine normale Pfeilespitze */
    };
}

#endif // EDGEGRAPHICITEM_H
