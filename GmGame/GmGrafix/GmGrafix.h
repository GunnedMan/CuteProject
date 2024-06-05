#ifndef GMGRAFIX_H
#define GMGRAFIX_H

#include <QObject>
#include <QPolygonF>
#include <QVector>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QBrush>
#include <QPen>

class GmGrafix : public QObject
{
public:
    enum DrawOptions
    {
        DRAWOPT_NONE = 0,
        DRAWOPT_BOUNDRECT = 1 << 0,
        DRAWOPT_COLLRADIUS = 1 << 1,
        DRAWOPT_COLLPOLY = 1 << 2,
    };
    
    
    Q_OBJECT
public:
    explicit GmGrafix(QObject *parent = nullptr);
    ~GmGrafix();

    QPolygonF getPolygonAtLayer(int layer) const;
    inline void draw(QPainter *painter, const DrawOptions options) const;
    void setPolygonAtLayer(int layer, const QPolygonF* polygon, const QPen* pen, const QBrush* brush);
    void clear();

private:
    void SetDummyGrafix();
    bool isLayerEmpty(int layer) const;
    inline void drawPolygonAtLayer(int layer, QPainter *painter) const;

private:
    static constexpr int MaxLayers = 16;
    
    
    QRectF m_boundRect;
    double m_maxCollisionRadius;
    double m_maxCollisionRadiusSquared;
    QPolygonF m_collisionPolygon;
    QPolygonF m_polygons[MaxLayers];
    QPen m_pens[MaxLayers];
    QBrush m_brushes[MaxLayers];
    
};


#endif // GMGRAFIX_H
