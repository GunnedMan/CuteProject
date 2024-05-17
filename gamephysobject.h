#ifndef GAMEPHYSOBJECT_H
#define GAMEPHYSOBJECT_H


#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QtMath>
#include <QVector2D>
#include <QVector3D>

class GamePhysObject : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit GamePhysObject(QObject *parent = nullptr);
    virtual void UpdateGame(int ticks = 1);
    virtual QVector2D velocityLin();
    virtual qreal velocityAng();
    virtual void ApplyImpulseG(QVector2D force, QPointF globalPoint);
    virtual void ApplyImpulseL(QVector2D force, QPointF localPoint);
    virtual void ApplyImpulseLin(QVector2D force);
    virtual void ApplyImpulseRot(qreal force);
    virtual qreal EnergyKinetic();

    virtual qreal mass();
    virtual void setMass(qreal mass);
    virtual qreal radius();
    virtual void setRadius(qreal radius);

signals:


    // QGraphicsItem interface
protected:
    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void SetPhysix(qreal mass = 10, qreal radius = 10);


private:
    QVector<QPointF>* p_grafixDummy;
protected:
    //QGraphicsItem
    QRect* p_boundRect;
    QVector<QPointF>* p_grafix;
    //game
    QVector2D m_velocityLinear;
    qreal m_velocityAngular;
    qreal m_mass;
    qreal m_radius;
    qreal m_massAngular;

};

#endif // GAMEPHYSOBJECT_H
