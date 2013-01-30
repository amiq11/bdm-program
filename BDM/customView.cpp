#include "customView.h"
#include <iostream>
#include <string>
#include <QGraphicsEllipseItem>
#include <QRect>

using namespace std;


CustomView::CustomView( QWidget *w ) : QGraphicsView( w ) 
{
    // scene = new QGraphicsScene( w->geometry() );    
    // cout << w->x() << "," << w->y() << "," << w->height() << "," << w->width() << endl;
    scene = new QGraphicsScene( QRect( 0, 0, 600, 500 ) );
    this->setScene( scene );
    scene->addItem( &trackLine );
    isTracking = false;
}

CustomView::~CustomView()
{

}

void CustomView::mouseDoubleClickEvent( QMouseEvent * event ) 
{
    cout << "Double Clicked " << event->x() << ", " << event->y() << endl;
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem( event->x() - 5, event->y() - 5, 10, 10 );
    scene->addItem( circle );

    if ( isTracking ) {
        isTracking = false;
        // QGraphicsLineItem *line = new QGraphicsLineItem( startPoint.x(), startPoint.y(), event->x(), event->y() );
        // scene->addItem( line );
    }
    
    scene->update();
}



void CustomView::mousePressEvent( QMouseEvent * event ) 
{

    // Print MousePress Event
    cout << "Pressed " << event->x() << ", " << event->y() << endl;

    string button;
    if ( event->button() & Qt::LeftButton )  button += "Left ";
    if ( event->button() & Qt::RightButton ) button += "Right ";
    if ( event->button() & Qt::MidButton )   button += "Mid ";
    cout << "Button is " << button << endl;

    // track
    if ( !isTracking ) {
        startPoint = event->pos();
        isTracking = true;
    } else {
        QGraphicsLineItem *line = new QGraphicsLineItem( startPoint.x(), startPoint.y(), event->x(), event->y() );
        scene->addItem( line );
        startPoint = event->pos();
        scene->update();
        
    }
}

void CustomView::mouseMoveEvent( QMouseEvent * event )
{
    cout << "Moved " << event->x() << ", " << event->y() << endl;

    if ( isTracking ) {
        trackLine.setLine( startPoint.x(), startPoint.y(), event->x(), event->y() );
        scene->update();
    }
    
}

