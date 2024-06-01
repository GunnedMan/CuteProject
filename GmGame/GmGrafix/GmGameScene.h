#ifndef GMGAMESCENE_H
#define GMGAMESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <GmGame/GmPhysObject/GmPhysObject.h>

class GmGameScene : public QGraphicsScene
{
public:
    GmGameScene(QObject* parent = nullptr)
        : QGraphicsScene(parent)
    {
    }

    GmPhysObject* spawnObject(GmPhysObject* model, QPointF position, QVector2D velocity)
    {

    }

};

#endif // GMGAMESCENE_H
