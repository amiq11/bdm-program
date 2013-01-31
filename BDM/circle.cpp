#include "circle.h"

Circle::Circle( const QRectF &r, QGraphicsItem *parent ) : QObject( (QObject*)parent ), QGraphicsEllipseItem( r, parent )
{
    
}

Circle::~Circle()
{
    
}

QPoint Circle::pos()
{
    return QPoint( this->rect().x(), this->rect().y() );
}

void Circle::setPos( const QPointF &p )
{
    this->setRect( p.x(), p.y(), this->rect().width(), this->rect().height() );
}
