#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QPoint>

class Circle : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY( QPointF pos READ pos WRITE setPos )

public:
    Circle( const QRectF &r, QGraphicsItem *parent = 0 );
    ~Circle();
    QPoint pos();
    void setPos( const QPointF &p );

};

#endif
