#include "GmPhysObject.h"


GmPhysObject::GmPhysObject(GmGameScene *parentScene) : QObject(parentScene)
{
    m_velocityLinear = QVector2D(0,0);
    m_velocityAngular = 0;
    setRotationalMass();

    m_defName = "";
    p_grafix = new GmModel2D(this);
}

void GmPhysObject::copyFrom(const GmPhysObject* other)
{
    setParent(other->parent());
    p_grafix = other->p_grafix;
    m_defName = other->m_defName;
    m_objectType = other->m_objectType;
    m_objectState = other->m_objectState;
    m_millisToLive = other->m_millisToLive;
    m_mass = other->m_mass;
    m_massRadius = other->m_massRadius;
    m_massRotational = other->m_massRotational;
    m_energyInternal = other->m_energyInternal;
    m_health = other->m_health;

    setX(other->x());
    setY(other->y());
    m_velocityLinear = QVector2D(0,0);
    m_velocityAngular = 0;
    m_motionType = other->m_motionType;
}

void GmPhysObject::setDefName(QString *name)
{
    m_defName = QString(*name);
}

void GmPhysObject::updateGame(int millis)
{
    updateState(millis);
    updatePhysics(millis);

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

void GmPhysObject::damage(int value)
{
    m_health -= value;
}

void GmPhysObject::heal(int value)
{
    m_health += value;
}

void GmPhysObject::destroy()
{
    m_health = 0;
    m_objectState = GMOBJ_STATE_DEAD;
}

void GmPhysObject::destruct()
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
    return m_millisToLive;
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
        setRotationalMass(mass, m_massRadius);
    }
}

qreal GmPhysObject::energyInternal() const
{
    return  m_energyInternal;
}

qreal GmPhysObject::radius() const
{
    return m_massRadius;
}

void GmPhysObject::setRadius(qreal radius)
{
    if(radius >= 0)
    {
        m_massRadius = radius;
        setRotationalMass(m_mass, m_massRadius);
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
    return *p_boundRect; //TODO
}

void GmPhysObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    p_grafix->drawPolygonAtLayer(GmGrafix::DummyLayer, painter);
}

void GmPhysObject::setRotationalMass(qreal mass, qreal radius)
{
    m_massRotational = mass * radius * radius * 0.5; //cylinder formula
}

void GmPhysObject::updateState(int millis)
{
    switch (m_objectState){
    case GMOBJ_STATE_ALIVE:
    {
        if(m_millisToLive <= 0 || (m_health <= 0 && m_health != GMOBJ_HEALTH_UNDESTRUCTIBLE))
        {
            m_objectState = GMOBJ_STATE_DYING;
            onDyingState();
        }
        if(m_millisToLive != GMOBJ_TTL_ETERNAL)
            m_millisToLive -= millis;
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

void GmPhysObject::updatePhysics(int millis)
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
    p += m_velocityLinear.toPointF() * millis;
    setPos(p);
    setRotation(rotation()+m_velocityAngular * millis);
}

void GmPhysObject::onDyingState()
{

}

void GmPhysObject::onDeadState()
{

}
