#include "gmgrafix.h"

GmGrafix::GmGrafix(QObject *parent) : QObject(parent)
{
    clear();
}

GmGrafix::~GmGrafix()
{

}

QPolygonF GmGrafix::getPolygonAtLayer(int layer) const
{
    return m_polygons[layer];
}

bool GmGrafix::isLayerEmpty(int layer) const
{
    return m_polygons[layer].length() == 0;
}

void GmGrafix::drawPolygonAtLayer(int layer, QPainter *painter) const
{
    if(layer >= GMGRAFIX_LAYERS)
        return;
    painter->save();
    painter->setPen(m_pens[layer]);
    painter->setBrush(m_brushes[layer]);
    painter->drawPolygon(m_polygons[layer]);
    painter->restore();
}

void GmGrafix::setPolygonAtLayer(int layer, const QPolygonF *polygon, const QPen *pen, const QBrush *brush)
{
    if(layer >= GMGRAFIX_LAYERS)
        return;
    m_polygons[layer] = *polygon;
    m_pens[layer] = *pen;
    m_brushes[layer] = *brush;
}

void GmGrafix::clear()
{
    for(int i = 0; i < MaxLayers; i++)
    {
        m_polygons[i] = QPolygonF();
        m_pens[i] = QPen();
        m_brushes[i] = QBrush();
    }
    SetDummyGrafix();
}

void GmGrafix::SetDummyGrafix()
{
    m_polygons[GMGRAFIX_DUMMYLAYER].clear();
    m_polygons[GMGRAFIX_DUMMYLAYER] << QPointF(0,0)
                  << QPointF(0,10)
                  << QPointF(10,0)
                  << QPointF(0,-10)
                  << QPointF(-10,0)
                  << QPointF(0,10);
}
