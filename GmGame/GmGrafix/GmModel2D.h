#ifndef GMMODEL_H
#define GMMODEL_H

#include <QObject>
#include <QPolygonF>
#include <QVector>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QAbstractGraphicsShapeItem>

class GmModel2D : public QObject
{
public:
    enum DrawOptions
    {
        DRAWOPT_NONE = 0,
        DRAWOPT_BOUNDRECT = 1 << 0,
        DRAWOPT_COLLRADIUS = 1 << 1,
        DRAWOPT_COLLPOLY = 1 << 2,
    };
    
    enum GmModelElement2DType
    {
        ELEMENT2DTYPE_NONE,
        ELEMENT2DTYPE_COLLIDER,
        ELEMENT2DTYPE_POLY,
        ELEMENT2DTYPE_POLYANIMSTART,
        ELEMENT2DTYPE_POLYANIMEND,
    };
    
    struct GmModelElement2D
    {
        QString name;
        QPolygonF polygon;
        QPen pen;
        QBrush brush;
    };
    
    
    Q_OBJECT
public:
    explicit GmModel2D(QObject *parent = nullptr);
    ~GmModel2D();

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
    GmModelElement2DType m_model2dElements[MaxLayers];
    QPolygonF m_polygons[MaxLayers];
    QPen m_pens[MaxLayers];
    QBrush m_brushes[MaxLayers];
    
};


#endif // GMMODEL_H
