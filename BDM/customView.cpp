#include "customView.h"
#include <iostream>
#include <string>
#include <QGraphicsEllipseItem>
#include <QSequentialAnimationGroup>
#include <QRect>
#include <unistd.h>
#include "circle.h"

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
        // QGraphicsEllipseItem *circle = new QGraphicsEllipseItem( event->x() - 5, event->y() - 5, 10, 10 );
        // scene->addItem( circle );
        // itemsEllipse.push_back( circle );

        isTracking = false;
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

void CustomView::timerEvent( QTimerEvent * event )
{
    // cout << "Timer" << endl;
    // if ( event->timerId() == timId ) {
    //     cout << "Anime" << endl;
    //     killTimer( timId );
    // } else {
    //     QWidget::timerEvent( event );
    // }
}

void CustomView::sendData()
{
    // string tmp;

    // comm.send( "Hello World!\n" );
    // usleep( 500*1000 );
    // int ret = comm.recv( tmp );
    // if ( ret > 0 ) {
    //     cout << tmp << endl;
    // } else {
    //     cerr << "nothing is received!" << endl;
    // }
}

void CustomView::clearField()
{
    vector < QList <QGraphicsLineItem *> > ::iterator it;
    if ( arrItems.size() > 0 ) {
        // オブジェクト削除
        it = arrItems.begin();
        QList <QGraphicsLineItem *> tmp = *it;
        while ( !tmp.isEmpty() ) {
            QGraphicsLineItem *item = tmp.front();
            scene->removeItem( item );
            delete item;
            tmp.pop_front();
        }
        arrItems.erase( it );
        // 円
        // if ( !itemsEllipse.isEmpty() ) {
        //     scene->removeItem( itemsEllipse.front() );
        //     delete itemsEllipse.front();
        //     itemsEllipse.pop_front();
        // }
        
        // 更新
        scene->update();
        cout << arrItems.size() << endl;
    } else {
#ifdef _DEBUG_        
        cerr << "All data is removed!" << endl;
#endif
    }
}

QPropertyAnimation* CustomView::setPosAnimation( QGraphicsLineItem *line, int ms )
{
    QPointF p1 = line->line().p1();
    QPointF p2 = line->line().p2();
    QPropertyAnimation *tmp = new QPropertyAnimation ( circle, "pos" );
    tmp->setDuration( ms );
    tmp->setStartValue( QPoint( p1.x()-5, p1.y()-5 ) );
    tmp->setEndValue( QPoint( p2.x()-5, p2.y()-5 ) );
    return tmp;
}


void CustomView::startAction()
{
    if ( arrItems.size() ) {
        QSequentialAnimationGroup *animation = new QSequentialAnimationGroup;
        
        QList <QGraphicsLineItem *> tmp = arrItems.front();
        QList <QGraphicsLineItem *> ::iterator it;
        QPointF p1 = tmp.front()->line().p1();
        
        if ( circle ) delete circle;
        this->circle = new Circle( QRectF( p1.x()-5 , p1.y()-5, 10, 10 ) );
        scene->addItem( circle );
        scene->update();

        for ( it = tmp.begin(); it < tmp.end(); it++ ) {
            QLineF line = (*it)->line();
            cout << line.length() << endl;
            animation->addAnimation( setPosAnimation( *it, line.length()*3 ) );
            cm.setCommand( line.length(), line.angle() );
        }
        animation->start();
        cm.start();
    }
    
    // sendData();
    clearField();
}


