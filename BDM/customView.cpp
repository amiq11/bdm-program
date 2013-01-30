#include "customView.h"
#include <iostream>
#include <string>

using namespace std;


CustomView::CustomView( QWidget *w ) : QGraphicsView( w )
{
    
}

CustomView::~CustomView()
{
    
}

void CustomView::mousePressEvent( QMouseEvent * event ) 
{
    cout << "Pressed " << event->x() << ", " << event->y() << endl;

    string button;
    if ( event->button() & Qt::LeftButton )  button += "Left ";
    if ( event->button() & Qt::RightButton ) button += "Right ";
    if ( event->button() & Qt::MidButton )   button += "Mid ";
    

    cout << "Button is " << button << endl;
    
}

   

