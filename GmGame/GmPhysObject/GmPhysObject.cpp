#include "GmPhysObject.h"


GmPhysObject::GmPhysObject(QObject *parent) : QObject(parent)
{
    m_velocityLinear = QVector2D(0,0);
    m_velocityAngular = 0;
    SetRotationalMass();

    m_defName = "";
    p_grafix = new GmGrafix(this);
    p_boundRect = new QRect(p_grafix->getPolygonAtLayer(GmGrafix::DummyLayer).boundingRect().toRect());
}

void GmPhysObject::setDefName(QString *name)
{
    m_defName = QString(*name);
}

void GmPhysObject::updateGame(int ticks)
{
    updateState(ticks);
    updatePhysics(ticks);

}

QVector2D GmPhysObject::velocityLin() const
{
    return m_velocityLinear;
}

qreal GmPhysObject::velocityAng() const
{
    return m_velocityAngular;
}

void GmPhysObject::applyImpulseG(QVector2D impulse, QPointF globalPoint)
{
    applyImpulseLin(impulse);
    QVector2D vectorToLocalCenter = QVector2D(globalPoint - pos());
    QVector3D vectorMult = QVector3D::crossProduct(vectorToLocalCenter, impulse);
    applyImpulseRot(vectorMult.z());
    //qDebug()<<QString("impulse: %1, %2").arg(impulse.x()).arg(impulse.y());
}

void GmPhysObject::applyImpulseL(QVector2D impulse, QPointF localPoint)
{
    QVector2D mappedImpulse = QVector2D(mapToScene(impulse.toPointF()) - pos());
    //qDebug()<<QString("mappedImpulse: %1, %2").arg(mappedImpulse.x()).arg(mappedImpulse.y());
    applyImpulseG(mappedImpulse, mapToScene(localPoint));
}

void GmPhysObject::applyImpulseLin(QVector2D impulse)
{
    if(m_mass == 0)
        return;
    m_velocityLinear += impulse / m_mass;
}

void GmPhysObject::applyImpulseRot(qreal impulse)
{
    if(m_massRotational == 0)
        return;
    m_velocityAngular += impulse / m_massRotational;
}

void GmPhysObject::setEnergyInternal(qreal energy)
{
    if(energy >= 0)
        m_energyInternal = energy;
}

void GmPhysObject::Damage(int value)
{
    m_health -= value;
}

void GmPhysObject::Heal(int value)
{
    m_health += value;
}

void GmPhysObject::Destroy()
{
    m_health = 0;
    m_objectState = GMOBJ_STATE_DEAD;
}

void GmPhysObject::Destruct()
{
    m_health = 0;
}

QString GmPhysObject::defName() const
{
    return m_defName;
}

GmPhysObject::GmObjectType GmPhysObject::gmType() const
{
    return m_objectType;
}

GmPhysObject::GmObjectState GmPhysObject::gmState() const
{
    return m_objectState;
}

int GmPhysObject::health() const
{
    return m_health;
}

int GmPhysObject::ticksToLive() const
{
    return m_ticksToLive;
}

qreal GmPhysObject::energyKinetic() const
{
    return m_mass * m_velocityLinear.lengthSquared() / 2;
}

qreal GmPhysObject::mass() const
{
    return  m_mass;
}

void GmPhysObject::setMass(qreal mass)
{
    if(mass >= 0)
    {
        m_mass = mass;
        SetRotationalMass(mass, m_radius);
    }
}

qreal GmPhysObject::energyInternal() const
{
    return  m_energyInternal;
}

qreal GmPhysObject::radius() const
{
    return m_radius;
}

void GmPhysObject::setRadius(qreal radius)
{
    if(radius >= 0)
    {
        m_radius = radius;
        SetRotationalMass(m_mass, m_radius);
    }
}

void GmPhysObject::setVelocityLin(QVector2D velocity)
{
    if(velocity.lengthSquared() < MaxVelocityLinearSquared)
        m_velocityLinear = velocity;
    else
        m_velocityLinear = MaxVelocityLinear * velocity.normalized();
}

void GmPhysObject::setVelocityAng(qreal velocity)
{
    if(velocity < abs(MaxVelocityRotational))
        m_velocityAngular = velocity;
    else if(velocity < 0)
        m_velocityAngular = - MaxVelocityRotational;
    else
        m_velocityAngular = MaxVelocityRotational;
}

QRectF GmPhysObject::boundingRect() const
{
    return *p_boundRect;
}

void GmPhysObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    p_grafix->drawPolygonAtLayer(GmGrafix::DummyLayer, painter);
}

void GmPhysObject::SetRotationalMass(qreal mass, qreal radius)
{
    m_massRotational = mass * radius * radius * 0.5; //cylinder formula
}

void GmPhysObject::updateState(int ticks)
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

void GmPhysObject::updatePhysics(int ticks)
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

void GmPhysObject::onDyingState()
{

}

void GmPhysObject::onDeadState()
{

}
