#ifndef CUSTOM_VIEW_H
#define CUSTOM_VIEW_H 
#endif /* Not def: CUSTOM_VIEW_H */

#include <QObject>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QPainter>
#include <QPaintEvent>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QPoint>

class CustomView : public QGraphicsView
{
    Q_OBJECT

public:
    CustomView( QWidget *w = 0 );
    ~CustomView();

protected:
    void mouseDoubleClickEvent( QMouseEvent * event );
    void mousePressEvent( QMouseEvent * event );
    void mouseMoveEvent( QMouseEvent * event );
    // void paintEvent( QPaintEvent *event );
    

private:
    QGraphicsScene *scene;
    bool isTracking;
    QPoint startPoint;
    QGraphicsLineItem trackLine;
    
};

    
    
