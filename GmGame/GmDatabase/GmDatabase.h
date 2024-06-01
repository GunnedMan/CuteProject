#ifndef GMDATABASE_H
#define GMDATABASE_H

#include <QObject>
#include <QList>

#include <GmGame/GmPhysObject/GmPhysObject.h>

class GmDatabase : public QObject
{
    Q_OBJECT
public:
    explicit GmDatabase(QObject *parent = nullptr)
        : QObject(parent)
    {
        m_objects = new QList<GmPhysObject>();
    }

    GmPhysObject* getObject(QString* defName)
    {
        for(int i = 0; i < m_objects->length(); i++)
        {
            if(m_objects->at(i).defName() == defName)
                return new GmPhysObject(m_objects->at(i));
        }
    }

private:
    void Init()
    {

    }


private:

QList<GmPhysObject>* m_objects;


};

#endif // GMDATABASE_H
