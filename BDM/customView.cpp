#include "customView.h"
#include <iostream>
#include <string>
#include <QGraphicsEllipseItem>
#include <QRect>
#include <unistd.h>

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

    if ( isTracking ) {
        QGraphicsEllipseItem *circle = new QGraphicsEllipseItem( event->x() - 5, event->y() - 5, 10, 10 );
        scene->addItem( circle );
        items.push_back( circle );

        isTracking = false;
        // QGraphicsLineItem *line = new QGraphicsLineItem( startPoint.x(), startPoint.y(), event->x(), event->y() );
        // scene->addItem( line );
        arrItems.push_back( items );
        cout << arrItems.size() << endl;
        items.clear();
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
        items.push_back( line );
        scene->update();

        cout << items.size() << endl;
        
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

void CustomView::sendData()
{
    string tmp;

    comm.send( "Hello World!\n" );
    usleep( 500*1000 );
    int ret = comm.recv( tmp );
    if ( ret > 0 ) {
        cout << tmp << endl;
    } else {
        cerr << "nothing is received!" << endl;
    }
}

void CustomView::clearField()
{
    vector < QList <QGraphicsItem *> > ::iterator it;
    if ( arrItems.size() > 0 ) {
        it = arrItems.begin();
        QList <QGraphicsItem *> tmp = *it;
        while ( !tmp.isEmpty() ) {
            QGraphicsItem *item = tmp.front();
            scene->removeItem( item );
            delete item;
            tmp.pop_front();
        }
        arrItems.erase( it );
        scene->update();
        cout << arrItems.size() << endl;
    } else {
#ifdef _DEBUG_        
        cerr << "All data is removed!" << endl;
#endif
    }
}
    
