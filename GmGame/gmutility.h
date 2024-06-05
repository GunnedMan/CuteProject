#ifndef GMUTILITY_H
#define GMUTILITY_H

#include <GmGame/GmPhysObject/GmPhysObject.h>
#include <GmGame/GmPhysObject/GmPlayerShip.h>

class GmUtility
{
public:
    GmUtility();

    static GmPhysObject* CopyPhysObject(const GmPhysObject* other)
    {
        if(other == nullptr)
            return nullptr;
        switch (other->gmType())
        {
         case GmPhysObject::GmObjectType::GMOBJ_TYPE_NONE:
        {
            GmPhysObject* result = new GmPhysObject();
            result->copyFrom(other);
            return result;
        }
        case GmPhysObject::GmObjectType::GMOBJ_TYPE_SHIP:
        {
            GmPlayerShip* result = new GmPlayerShip();
            result->copyFrom(dynamic_cast<const GmPlayerShip*>(other));
            return result;
        }
        case GmPhysObject::GmObjectType::GMOBJ_TYPE_CHUNK:
            return nullptr;
        case GmPhysObject::GmObjectType::GMOBJ_TYPE_BULLET:
            return nullptr;
        case GmPhysObject::GmObjectType::GMOBJ_TYPE_PARTICLE:
            return nullptr;
        case GmPhysObject::GmObjectType::GMOBJ_TYPE_SHIPPLAYER:
            return nullptr;
        case GmPhysObject::GmObjectType::GMOBJ_TYPE_COLLECTIBLE:
            return nullptr;
        }
    }

};

#endif // GMUTILITY_H
