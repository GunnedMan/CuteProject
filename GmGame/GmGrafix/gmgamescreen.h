#ifndef GMGAMESCREEN_H
#define GMGAMESCREEN_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <GmGame/GmPhysObject/GmPlayerShip.h>


class GmGameScreen : public QGraphicsView
{
    Q_OBJECT
public:
    GmGameScreen(QWidget* parent = nullptr)
        : QGraphicsView(parent)
    {
        setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    }
    
    void setPlayerShip(GmPlayerShip* ship)
    {
        p_playerShip = ship;
        
    }
    
    void updateGame(int millis)
    {
        
    }
    
    
    
    
private:
    GmPlayerShip* p_playerShip;
    
};

#endif // GMGAMESCREEN_H
