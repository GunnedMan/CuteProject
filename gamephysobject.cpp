#include "gamephysobject.h"


GamePhysObject::GamePhysObject(QObject *parent) : QObject(parent)
{
    p_boundRect = new QRect(QPoint(-10,-10), QPoint(10,0));
    p_grafixDummy = new QVector<QPointF>();
    p_grafixDummy->append(QPointF(  0, 10));
    p_grafixDummy->append(QPointF( 10,  0));
    p_grafixDummy->append(QPointF(  0,-10));
    p_grafixDummy->append(QPointF(-10,  0));
    p_grafixDummy->append(QPointF(  0, 10));
    p_grafixDummy->append(QPointF(  0,  0));
    SetPhysix();
}

void GamePhysObject::UpdateGame(int ticks)
{
    QPointF p = pos();
    p.setX(p.x() + m_velocityLinear.x() * ticks);
    p.setY(p.y() + m_velocityLinear.y() * ticks);
    setPos(p);
    setRotation(rotation()+m_velocityAngular * ticks);
}

QVector2D GamePhysObject::velocityLin()
{
    return m_velocityLinear;
}

qreal GamePhysObject::velocityAng()
{
    return m_velocityAngular;
}

void GamePhysObject::ApplyImpulseG(QVector2D impulse, QPointF globalPoint)
{
    ApplyImpulseLin(impulse);
    QVector2D vectorToLocalCenter = QVector2D(globalPoint - pos());
    QVector3D vectorMult = QVector3D::crossProduct(vectorToLocalCenter, impulse);
    ApplyImpulseRot(vectorMult.z());
}

void GamePhysObject::ApplyImpulseL(QVector2D impulse, QPointF localPoint)
{
    ApplyImpulseG(QVector2D(mapToScene(impulse.toPointF()) - pos()), mapToScene(localPoint));
}

void GamePhysObject::ApplyImpulseLin(QVector2D impulse)
{
    m_velocityLinear += impulse / m_mass;
}

void GamePhysObject::ApplyImpulseRot(qreal impulse)
{
    m_velocityAngular += impulse / m_massAngular;
}

qreal GamePhysObject::EnergyKinetic()
{
    return m_mass * m_velocityLinear.lengthSquared() / 2;
}

qreal GamePhysObject::mass()
{
    return  m_mass;
}

void GamePhysObject::setMass(qreal mass)
{
    if(mass > 0)
    {
        m_mass = mass;
        SetPhysix(mass, m_radius);
    }
}

qreal GamePhysObject::radius()
{
    return m_radius;
}

void GamePhysObject::setRadius(qreal radius)
{
    if(m_radius > 0)
    {
        m_radius = radius;
        SetPhysix(m_mass, m_radius);
    }
}

QRectF GamePhysObject::boundingRect() const
{
    return *p_boundRect;
}

void GamePhysObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPolygon(*p_grafixDummy);
}

void GamePhysObject::SetPhysix(qreal mass, qreal radius)
{
    m_massAngular = mass * radius * radius * 0.5; //cylinder formula
}
