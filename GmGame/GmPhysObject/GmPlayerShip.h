#ifndef GMPLAYERSHIP_H
#define GMPLAYERSHIP_H

#include <QObject>
#include <QtDebug>
#include <QVariantAnimation>
#include <QEasingCurve>

#include "GmPhysObject.h"
#include <GmGame/GmInput/GmInput.h>

class GmPlayerShip : public GmPhysObject
{
    Q_OBJECT
    
public:
    explicit GmPlayerShip(QObject *parent = nullptr);
    void copyFrom(const GmPlayerShip* other);
    void updateGame(int ticks = 1) override;
    void SetThrustMain(double value);
    void SetThrustLat(double value);
    void SetThrustRot(double value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void SetInput(GmInput* input);

private:
    void UpdateInput(int ticks);
    void UpdateThrust(int ticks);

protected:
    //ship
    GmInput* m_input;

private:
    const int TicksToMaxThrust = 500;
    double m_maxThrustMain;
    double m_maxThrustLat;
    double m_maxThrustRot;

    double m_thrustMain;
    double m_thrustLat;
    double m_thrustRot;
    
    
};

#endif // GAMESHIP_H
