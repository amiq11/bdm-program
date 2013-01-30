#ifndef CUSTOM_VIEW_H
#define CUSTOM_VIEW_H 
#endif /* Not def: CUSTOM_VIEW_H */

#include <QMouseEvent>
#include <QGraphicsView>

class CustomView : public QGraphicsView
{
public:
    CustomView( QWidget *w );
    ~CustomView();

    void mousePressEvent( QMouseEvent * event );

};

    
    
