#include "gmphysicalobject.h"


GmPhysicalObject::GmPhysicalObject(QObject *parent) : QObject(parent)
{
    m_velocityLinear = QVector2D(0,0);
    m_velocityAngular = 0;
    SetRotationalMass();

    p_grafix = new GmGrafix(this);
    p_boundRect = new QRect(p_grafix->getPolygonAtLayer(GmGrafix::DummyLayer).boundingRect().toRect());
}

void GmPhysicalObject::updateGame(int ticks)
{
    //
    updateState(ticks);
    updatePhysics(ticks);

}

QVector2D GmPhysicalObject::velocityLin() const
{
    return m_velocityLinear;
}

qreal GmPhysicalObject::velocityAng() const
{
    return m_velocityAngular;
}

void GmPhysicalObject::applyImpulseG(QVector2D impulse, QPointF globalPoint)
{
    applyImpulseLin(impulse);
    QVector2D vectorToLocalCenter = QVector2D(globalPoint - pos());
    QVector3D vectorMult = QVector3D::crossProduct(vectorToLocalCenter, impulse);
    applyImpulseRot(vectorMult.z());
    //qDebug()<<QString("impulse: %1, %2").arg(impulse.x()).arg(impulse.y());
}

void GmPhysicalObject::applyImpulseL(QVector2D impulse, QPointF localPoint)
{
    QVector2D mappedImpulse = QVector2D(mapToScene(impulse.toPointF()) - pos());
    //qDebug()<<QString("mappedImpulse: %1, %2").arg(mappedImpulse.x()).arg(mappedImpulse.y());
    applyImpulseG(mappedImpulse, mapToScene(localPoint));
}

void GmPhysicalObject::applyImpulseLin(QVector2D impulse)
{
    if(m_mass == 0)
        return;
    m_velocityLinear += impulse / m_mass;
}

void GmPhysicalObject::applyImpulseRot(qreal impulse)
{
    if(m_massRotational == 0)
        return;
    m_velocityAngular += impulse / m_massRotational;
}

void GmPhysicalObject::setEnergyInternal(qreal energy)
{
    if(energy >= 0)
        m_energyInternal = energy;
}

void GmPhysicalObject::Damage(int value)
{
    m_health -= value;
}

void GmPhysicalObject::Heal(int value)
{
    m_health += value;
}

void GmPhysicalObject::Destroy()
{
    m_health = 0;
    m_objectState = GMOBJ_STATE_DEAD;
}

void GmPhysicalObject::Destruct()
{
    m_health = 0;
}

GmPhysicalObject::GmObjectType GmPhysicalObject::gmType() const
{
    return m_objectType;
}

GmPhysicalObject::GmObjectState GmPhysicalObject::gmState() const
{
    return m_objectState;
}

int GmPhysicalObject::health() const
{
    return m_health;
}

int GmPhysicalObject::ticksToLive() const
{
    return m_ticksToLive;
}

qreal GmPhysicalObject::energyKinetic() const
{
    return m_mass * m_velocityLinear.lengthSquared() / 2;
}

qreal GmPhysicalObject::mass() const
{
    return  m_mass;
}

void GmPhysicalObject::setMass(qreal mass)
{
    if(mass >= 0)
    {
        m_mass = mass;
        SetRotationalMass(mass, m_radius);
    }
}

qreal GmPhysicalObject::energyInternal() const
{
    return  m_energyInternal;
}

qreal GmPhysicalObject::radius() const
{
    return m_radius;
}

void GmPhysicalObject::setRadius(qreal radius)
{
    if(radius >= 0)
    {
        m_radius = radius;
        SetRotationalMass(m_mass, m_radius);
    }
}

void GmPhysicalObject::setVelocityLin(QVector2D velocity)
{
    if(velocity.lengthSquared() < MaxVelocityLinearSquared)
        m_velocityLinear = velocity;
    else
        m_velocityLinear = MaxVelocityLinear * velocity.normalized();
}

void GmPhysicalObject::setVelocityAng(qreal velocity)
{
    if(velocity < abs(MaxVelocityRotational))
        m_velocityAngular = velocity;
    else if(velocity < 0)
        m_velocityAngular = - MaxVelocityRotational;
    else
        m_velocityAngular = MaxVelocityRotational;
}

QRectF GmPhysicalObject::boundingRect() const
{
    return *p_boundRect;
}

void GmPhysicalObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    p_grafix->drawPolygonAtLayer(GmGrafix::DummyLayer, painter);
}

void GmPhysicalObject::SetRotationalMass(qreal mass, qreal radius)
{
    m_massRotational = mass * radius * radius * 0.5; //cylinder formula
}

void GmPhysicalObject::updateState(int ticks)
{
    switch (m_objectState){
    case GMOBJ_STATE_ALIVE:
    {
        if(m_ticksToLive <= 0 || (m_health <= 0 && m_health != GMOBJ_HEALTH_UNDESTRUCTIBLE))
        {
            m_objectState = GMOBJ_STATE_DYING;
            onDyingState();
        }
        if(m_ticksToLive != GMOBJ_TTL_ETERNAL)
            m_ticksToLive -= ticks;
    }
        break;

    case GMOBJ_STATE_DYING:
    {
        m_objectState = GMOBJ_STATE_DEAD;
        onDeadState();
    }
        break;

    default:
    {
        m_objectState = GMOBJ_STATE_DEAD;
    }
        break;
    }
}

void GmPhysicalObject::updatePhysics(int ticks)
{
    if(m_objectState == GMOBJ_STATE_DEAD)
        return;
    if(m_motionType == GMOBJ_MOTION_FADELINEAR)
    {
        if(m_velocityLinear.lengthSquared() > MinVelocitySquared)
            m_velocityLinear *= VelocityFadeCoef;
        else
        {
            m_velocityLinear.setX(0);
            m_velocityLinear.setY(0);
        }
    }
    if(m_velocityLinear.lengthSquared() > MaxVelocityLinearSquared)
        m_velocityLinear = m_velocityLinear.normalized() * MaxVelocityLinearSquared;
    QPointF p = pos();
    p += m_velocityLinear.toPointF() * ticks;
    setPos(p);
    setRotation(rotation()+m_velocityAngular * ticks);
}

void GmPhysicalObject::onDyingState()
{

}

void GmPhysicalObject::onDeadState()
{

}
