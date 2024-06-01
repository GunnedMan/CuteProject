#ifndef GMGRAFIX_H
#define GMGRAFIX_H

#include <QObject>
#include <QPolygonF>
#include <QVector>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QBrush>
#include <QPen>

#define GMGRAFIX_LAYERS 32
#define GMGRAFIX_DUMMYLAYER 31

class GmGrafix : public QObject
{
    Q_OBJECT
public:
    static const int DummyLayer = GMGRAFIX_DUMMYLAYER;
    explicit GmGrafix(QObject *parent = nullptr);
    ~GmGrafix();

    QPolygonF getPolygonAtLayer(int layer) const;
    bool isLayerEmpty(int layer) const;
    void drawPolygonAtLayer(int layer, QPainter *painter) const;
    void setPolygonAtLayer(int layer, const QPolygonF* polygon, const QPen* pen, const QBrush* brush);
    void clear();

private:
    void SetDummyGrafix();

private:
    static const int MaxLayers = GMGRAFIX_LAYERS;
    QPolygonF m_polygons[GMGRAFIX_LAYERS];
    QPen m_pens[GMGRAFIX_LAYERS];
    QBrush m_brushes[GMGRAFIX_LAYERS];


};


#endif // GMGRAFIX_H
