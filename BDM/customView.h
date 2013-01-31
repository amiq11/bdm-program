#ifndef CUSTOM_VIEW_H
#define CUSTOM_VIEW_H 

#include <QObject>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QPainter>
#include <QPaintEvent>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsItemGroup>
#include <QPoint>
#include <QList>
#include "commDevice.h"

class CustomView : public QGraphicsView
{
    Q_OBJECT

public:
    CustomView( QWidget *w = 0 );
    ~CustomView();

public slots:
    void clearField();
    void sendData();

protected:
    void mouseDoubleClickEvent( QMouseEvent * event );
    void mousePressEvent( QMouseEvent * event );
    void mouseMoveEvent( QMouseEvent * event );

private:
    QGraphicsScene *scene;
    bool isTracking;
    QPoint startPoint;
    QGraphicsLineItem trackLine;
    QList <QGraphicsItem *> items;
    std::vector < QList <QGraphicsItem *> >  arrItems;
    CommDevice comm;
};

    
    
#endif /* Not def: CUSTOM_VIEW_H */
