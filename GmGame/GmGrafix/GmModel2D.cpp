#include "GmModel2D.h"

GmModel2D::GmModel2D(QObject *parent) : QObject(parent)
{
    clear();
}

GmModel2D::~GmModel2D()
{

}

QPolygonF GmModel2D::getPolygonAtLayer(int layer) const
{
    return m_polygons[layer];
}

void GmModel2D::draw(QPainter *painter, const GmModel2D::DrawOptions options) const
{
    painter->save();
    for(int i = 0; i < MaxLayers; i++)
        drawPolygonAtLayer(i, painter);
    if(options != DRAWOPT_NONE)
    {
        QBrush br;
        painter->setBrush(br);
        if(options == DRAWOPT_COLLPOLY)
        {
            painter->setPen(Qt::red);
            painter->drawPolygon(m_collisionPolygon);
        }
        if(options == DRAWOPT_BOUNDRECT)
        {
            painter->setPen(Qt::blue);
            painter->drawRect(m_boundRect);
        }
        if(options == DRAWOPT_COLLRADIUS)
        {
            painter->setPen(Qt::yellow);
            painter->drawArc(0,0,m_maxCollisionRadius * 2, m_maxCollisionRadius * 2, 0, 360);
        }

    }
    painter->restore();
}

bool GmModel2D::isLayerEmpty(int layer) const
{
    return m_polygons[layer].length() == 0;
    QAbstractGraphicsShapeItem;
    
    
}



inline void GmModel2D::drawPolygonAtLayer(int layer, QPainter *painter) const
{
    painter->setPen(m_pens[layer]);
    painter->setBrush(m_brushes[layer]);
    painter->drawPolygon(m_polygons[layer]);
}

void GmModel2D::setPolygonAtLayer(int layer, const QPolygonF *polygon, const QPen *pen, const QBrush *brush)
{
    if(layer >= MaxLayers)
        return;
    m_polygons[layer] = *polygon;
    m_pens[layer] = *pen;
    m_brushes[layer] = *brush;
}

void GmModel2D::clear()
{
    for(int i = 0; i < MaxLayers; i++)
    {
        m_polygons[i] = QPolygonF();
        m_pens[i] = QPen();
        m_brushes[i] = QBrush();
    }
    SetDummyGrafix();
}

void GmModel2D::SetDummyGrafix()
{
    m_polygons[0].clear();
    m_polygons[0] << QPointF(0,0)
                  << QPointF(0,10)
                  << QPointF(10,0)
                  << QPointF(0,-10)
                  << QPointF(-10,0)
                  << QPointF(0,10);
}
