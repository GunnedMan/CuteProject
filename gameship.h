#ifndef GAMESHIP_H
#define GAMESHIP_H

#include <QObject>
#include <gamephysobject.h>


class GameShip : public GamePhysObject
{
    Q_OBJECT

public:
    GameShip(QObject *parent = nullptr);
    void UpdateGame(int ticks = 1) override;
    void SetThrustMain(qreal value);
    void SetThrustLat(qreal value);
    void SetThrustRot(qreal value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


protected:
    //ship
    qreal m_thrust;
    qreal m_thrustLat;



};

#endif // GAMESHIP_H
