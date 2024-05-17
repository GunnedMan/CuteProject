#include "gameship.h"

GameShip::GameShip(QObject *parent) : GamePhysObject(parent)
{

    setMass(100);
    setRadius(50);

    p_boundRect = new QRect(QPoint(-50,-30), QPoint(50,20));
    p_grafix = new QVector<QPointF>();
    p_grafix->append(QPointF( 20,-30));
    p_grafix->append(QPointF( 50, 10));
    p_grafix->append(QPointF( 20, 20));
    p_grafix->append(QPointF(-20, 20));
    p_grafix->append(QPointF(-50, 10));
    p_grafix->append(QPointF(-20,-30));
    p_grafix->append(QPointF(  0,  0));
    p_grafix->append(QPointF( 20,-30));
    p_grafix->append(QPointF(-20,-30));
}

void GameShip::UpdateGame(int ticks)
{
    //m_velocityLinear =

    GamePhysObject::UpdateGame(ticks);
}

void GameShip::SetThrustMain(qreal value)
{
    ApplyImpulseL(QVector2D(0,-value), QPointF(-200, 10));
    ApplyImpulseL(QVector2D(0,-value), QPointF(200, 10));
}

void GameShip::SetThrustLat(qreal value)
{
    m_thrustLat = value;
}

void GameShip::SetThrustRot(qreal value)
{
    ApplyImpulseRot(value);
}

void GameShip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GamePhysObject::paint(painter, option, widget);
    painter->drawPolygon(*p_grafix);
    //QString s = QString("vel %1, %2").arg(m_velocityLinear.x()).arg(m_velocityLinear.y());
    QString s = QString("pos %1, %2").arg(pos().x()).arg(pos().y());
    painter->drawText(0,0, s);

}
