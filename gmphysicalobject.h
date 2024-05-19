#ifndef GAMEPHYSOBJECT_H
#define GAMEPHYSOBJECT_H


#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QtMath>
#include <QVector2D>
#include <QVector3D>
#include <QtDebug>


#include <gmgrafix.h>

class GmPhysicalObject : public QObject, public QGraphicsItem
{
public:

    enum GmObjectType
    {
        GMOBJ_TYPE_NONE,
        GMOBJ_TYPE_PARTICLE,
        GMOBJ_TYPE_CHUNK,
        GMOBJ_TYPE_COLLECTIBLE,
        GMOBJ_TYPE_SHIP,
        GMOBJ_TYPE_SHIPPLAYER,
        GMOBJ_TYPE_BULLET,
    };

    enum GmObjectState
    {
        GMOBJ_STATE_ALIVE,
        GMOBJ_STATE_DYING,
        GMOBJ_STATE_DEAD,
    };

    enum GmObjectHealth
    {
        GMOBJ_HEALTH_UNDESTRUCTIBLE = 0x7FFFFFFF,
    };

    enum GmObjectTicksToLive
    {
        GMOBJ_TTL_ETERNAL = 0x7FFFFFFF,
    };

    enum GmObjectMotion
    {
        GMOBJ_MOTION_FREE,
        GMOBJ_MOTION_FADELINEAR,
    };



    Q_OBJECT
public:
    explicit GmPhysicalObject(QObject *parent = nullptr);
    virtual void updateGame(int ticks = 1);
    virtual void setRadius(qreal radius);
    virtual void setMass(qreal mass);
    virtual void setVelocityLin(QVector2D velocity);
    virtual void setVelocityAng(qreal velocity);
    virtual void applyImpulseG(QVector2D force, QPointF globalPoint);
    virtual void applyImpulseL(QVector2D force, QPointF localPoint);
    virtual void applyImpulseLin(QVector2D force);
    virtual void applyImpulseRot(qreal force);
    virtual void setEnergyInternal(qreal energy);
    virtual void Damage(int value);
    virtual void Heal(int value);
    virtual void Destroy();
    virtual void Destruct();

    virtual GmObjectType gmType() const;
    virtual GmObjectState gmState() const;
    virtual int health() const;
    virtual int ticksToLive() const;
    virtual qreal mass() const;
    virtual QVector2D velocityLin() const;
    virtual qreal velocityAng() const;
    virtual qreal radius() const;
    virtual qreal energyKinetic() const;
    virtual qreal energyInternal() const;

    // QGraphicsItem
protected:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void SetRotationalMass(qreal mass = 10, qreal radius = 10);
    virtual void updateState(int ticks = 1);
    virtual void updatePhysics(int ticks = 1);
    virtual void onDyingState();
    virtual void onDeadState();


protected:
    const qreal MaxVelocityLinear = 1000;
    const qreal MaxVelocityLinearSquared = MaxVelocityLinear * MaxVelocityLinear;
    const qreal MaxVelocityRotational = 10;
    const qreal VelocityFadeCoef = 0.99;
    const qreal MinVelocity = 0.001;
    const qreal MinVelocitySquared = MinVelocity * MinVelocity;

    //QGraphicsItem
    QRect* p_boundRect;
    GmGrafix* p_grafix;

    //game
    GmObjectType m_objectType = GMOBJ_TYPE_NONE;
    GmObjectState m_objectState = GMOBJ_STATE_ALIVE;
    int m_ticksToLive = GMOBJ_TTL_ETERNAL;
    //physical
    qreal m_mass = 0;
    qreal m_radius = 0;
    qreal m_massRotational = 0;
    QVector2D m_velocityLinear = QVector2D(0,0);
    qreal m_velocityAngular = 0;
    GmObjectMotion m_motionType = GMOBJ_MOTION_FREE;

    //
    qreal m_energyInternal = 0;
    int m_health = GMOBJ_HEALTH_UNDESTRUCTIBLE;

};

#endif // GAMEPHYSOBJECT_H