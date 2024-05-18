#include "gameship.h"

GameShip::GameShip(QObject *parent) : GamePhysObject(parent)
{
    m_maxThrustMain = 0.08;
    m_maxThrustLat = 0.04;
    m_maxThrustRot = 8;

    m_thrustMain = 0;
    m_thrustLat = 0;
    m_thrustRot = 0;
    SetPhysix(100,50);

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

    m_input = nullptr;
}

void GameShip::UpdateGame(int ticks)
{
    if(m_input != nullptr)
        UpdateInput(ticks);
    UpdateThrust(ticks);
    GamePhysObject::UpdateGame(ticks);
    
}

void GameShip::SetThrustMain(qreal value)
{
    m_thrustMain = value;
}

void GameShip::SetThrustLat(qreal value)
{
    m_thrustLat = value;
}

void GameShip::SetThrustRot(qreal value)
{
    m_thrustRot = value;
}

void GameShip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(p_grafix == nullptr)
        GamePhysObject::paint(painter, option, widget);
    else
        painter->drawPolygon(*p_grafix);
    //QString s = QString("vel %1, %2").arg(m_velocityLinear.x()).arg(m_velocityLinear.y());
    //QString s = QString("pos %1, %2").arg(pos().x()).arg(pos().y());

    //painter->drawText(0,0, s);

}

void GameShip::SetInput(InputHandler *input)
{
    m_input = input;
}

void GameShip::UpdateInput(int ticks)
{
    int pressedTicks;
    if(m_input->IsKeyPressed(Qt::Key::Key_W, &pressedTicks))
    {
        if(pressedTicks > TicksToMaxThrust)
            pressedTicks = TicksToMaxThrust;
        SetThrustMain(-m_maxThrustMain * pressedTicks / TicksToMaxThrust);
    }
    else if(m_input->IsKeyPressed(Qt::Key::Key_S, &pressedTicks))
    {
        if(pressedTicks > TicksToMaxThrust)
            pressedTicks = TicksToMaxThrust;
        SetThrustMain(m_maxThrustMain * pressedTicks / TicksToMaxThrust);
    }
    else
        SetThrustMain(0);

    if(m_input->IsKeyPressed(Qt::Key::Key_Q, &pressedTicks))
    {
        if(pressedTicks > TicksToMaxThrust)
            pressedTicks = TicksToMaxThrust;
        SetThrustRot(-m_maxThrustRot * pressedTicks / TicksToMaxThrust);
    }
    else if(m_input->IsKeyPressed(Qt::Key::Key_E, &pressedTicks))
    {
        if(pressedTicks > TicksToMaxThrust)
            pressedTicks = TicksToMaxThrust;
        SetThrustRot(m_maxThrustRot * pressedTicks / TicksToMaxThrust);
    }
    else
        SetThrustRot(0);

    if(m_input->IsKeyPressed(Qt::Key::Key_A, &pressedTicks))
    {
        if(pressedTicks > TicksToMaxThrust)
            pressedTicks = TicksToMaxThrust;
        SetThrustLat(-m_maxThrustLat * pressedTicks / TicksToMaxThrust);
    }
    else if(m_input->IsKeyPressed(Qt::Key::Key_D, &pressedTicks))
    {
        if(pressedTicks > TicksToMaxThrust)
            pressedTicks = TicksToMaxThrust;
        SetThrustLat(m_maxThrustLat * pressedTicks / TicksToMaxThrust);
    }
    else
        SetThrustLat(0);

}

void GameShip::UpdateThrust(int ticks)
{
    ApplyImpulseL(QVector2D(0, m_thrustMain * ticks), QPointF(0, 10));
    ApplyImpulseL(QVector2D(m_thrustLat * ticks, 0), QPointF(0, 0));
    ApplyImpulseRot(m_thrustRot * ticks);
}
