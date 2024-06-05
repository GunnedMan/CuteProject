#ifndef GMDATABASE_H
#define GMDATABASE_H

#include <QObject>
#include <QList>
#include <QHash>

#include <GmGame/GmPhysObject/GmPhysObject.h>
#include <GmGame/GmUtility.h>

class GmDatabase : public QObject
{
    Q_OBJECT
public:
    explicit GmDatabase(QObject *parent = nullptr)
        : QObject(parent)
    {
        m_objects = QHash<QString,GmPhysObject*>();
    }

    GmPhysObject* getObject(QString* defName)
    {
        return GmUtility::CopyPhysObject(m_objects[*defName]);
    }

private:
    void Init()
    {

    }


private:

QHash<QString,GmPhysObject*> m_objects;


};

#endif // GMDATABASE_H
