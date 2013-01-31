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
#include <QPropertyAnimation>
#include "commDevice.h"
#include "circle.h"
#include "commandManager.h"

class CustomView : public QGraphicsView
{
    Q_OBJECT

public:
    CustomView( QWidget *w = 0 );
    ~CustomView();

public slots:
    void startAction();

protected:
    void mouseDoubleClickEvent( QMouseEvent * event );
    void mousePressEvent( QMouseEvent * event );
    void mouseMoveEvent( QMouseEvent * event );
    void timerEvent( QTimerEvent *event );
private:
    void clearField();
    void sendData();
    QPropertyAnimation *setPosAnimation( QGraphicsLineItem *line, int ms );

    QGraphicsScene *scene;
    bool isTracking;
    QPoint startPoint;
    QGraphicsLineItem trackLine;
    QList <QGraphicsLineItem *> items;
    QList <QGraphicsEllipseItem *> itemsEllipse;
    std::vector < QList <QGraphicsLineItem *> >  arrItems;

    Circle *circle = 0;
    CommandManager cm;
};

    
    
#endif /* Not def: CUSTOM_VIEW_H */
