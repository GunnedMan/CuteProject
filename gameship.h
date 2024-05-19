#ifndef GAMESHIP_H
#define GAMESHIP_H

#include <QObject>
#include <QtDebug>
#include <QVariantAnimation>
#include <QEasingCurve>

#include <gmphysicalobject.h>
#include <inputhandler.h>

class GameShip : public GmPhysicalObject
{
    Q_OBJECT

public:
    GameShip(QObject *parent = nullptr);
    void updateGame(int ticks = 1) override;
    void SetThrustMain(qreal value);
    void SetThrustLat(qreal value);
    void SetThrustRot(qreal value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void SetInput(InputHandler* input);

private:
    void UpdateInput(int ticks);
    void UpdateThrust(int ticks);

protected:
    //ship
    InputHandler* m_input;

private:
    const int TicksToMaxThrust = 500;
    qreal m_maxThrustMain;
    qreal m_maxThrustLat;
    qreal m_maxThrustRot;

    qreal m_thrustMain;
    qreal m_thrustLat;
    qreal m_thrustRot;
    
    
};

#endif // GAMESHIP_H
