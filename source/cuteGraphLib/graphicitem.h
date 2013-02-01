#ifndef GRAPHICITEM_H
#define GRAPHICITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QLabel>
#include <QTextOption>
#include <QGraphicsSceneMouseEvent>
#include <boost/signal.hpp>
#include <iostream>
#include <map>

namespace cuteGraphLib
{
    /*!
     \brief Abstrakte Oberklasse für Knoten und Kanten im Graph

            Zusammengehörige Eigenschaften von NodeGraphicItem
            und EdgeGraphicItem sind hier zusammengefasst.
     */
    class GraphicItem : public QGraphicsItem
    {

    public:

        /*!
            \brief Konstruktor

            \param rec Der begrenzende Rahmen des GraphicItems
            \param line Die Farbe für die Rahmenlinie
        */
        GraphicItem(QRectF rec, QColor line);
        virtual ~GraphicItem();

        virtual QRectF boundingRect() const = 0;/**< Gibt die äußere Begrenzung des Items zurück. */
        virtual QPainterPath shape() const = 0; /**< Gibt die Form des Items zurück. Definiert auch den Klickbereich. */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0; /**< Zeichnet das Item. */
        void setLabel(const QString &label);          /**< Setzt das Label für das Item.*/
        const QString &getLabel() const;            /**< Gibt das Label für das Item zurück.*/
        void setColor(QColor &line, QColor &font);  /**< Setzt die Farbe. \param line Farbe der Linie \param font Farbe des Textes.*/
        void setColorFromAttributes();              /**< Setzt die Farben aus den userAttributes. */
        
        std::map<std::string, std::string> userAttributes; /**< Eine Map mit Attributen */
        void addAdditionalUserAttribute(std::string key, std::string value); /**< Setzt zusätzliche Attribute in Key-Value Form */
        
        boost::signal<void ()> signalClicked;           /**< Das Signal wird gegeben, wenn links geklickt wird. */
        boost::signal<void ()> signalRightClicked;      /**< Das Signal wird gegeben, wenn rechts geklickt wird. */
        boost::signal<void ()> signalDoubleClicked;     /**< Das Signal wird gegeben, wenn doppelt links geklickt wird. */
        boost::signal<void ()> signalOnHoverEnter;      /**< Das Signal wird gegeben, wenn die Form mit dem Zeiger betreten wird. */
        boost::signal<void ()> signalOnHoverLeave;      /**< Das Signal wird gegeben, wenn die Form mit dem Zeiger verlassen wird. */
        boost::signal<void ()> signalOnHoverMove;       /**< Das Signal wird gegeben, wenn die Form mit dem Zeiger überfahren wird. */
        
    protected:
        
        QColor fillColor;                               /**< Die Füllfarbe des Items.*/
        QColor lineColor;                               /**< Die Linienfarbe des Items.*/
        QColor fontColor;                               /**< Die Textfarbe des Items.*/
        QRectF boundingBox;                            /**< Die äußere Begrenzung des Items.*/
        QString label;                                  /**< Die Beschriftung des Items.*/

        void mousePressEvent(QGraphicsSceneMouseEvent *event);          /**< Wird beim drücken des Mousebuttons aufgerufen, wenn sich der Zeiger auf dem Item befindet. */
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);        /**< Wird beim loslassen des Mousebutton auf der Form aufgerufen. */
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);    /**< Wird beim Double-Mouseclick auf dem Item aufgerufen. */
        void hoverEnterEvent(QGraphicsSceneHoverEvent * event);         /**< Wird beim betreten des Shapes mit der Maus einmalig aufgerufen. */
        void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);         /**< Wird beim bewegen der Maus über den Shape aufgerufen. */
        void hoverMoveEvent(QGraphicsSceneHoverEvent * event);          /**< Wird beim verlassen der Maus vom Shape aufgerufen. */
    };
}

#endif // GRAPHICITEM_H
