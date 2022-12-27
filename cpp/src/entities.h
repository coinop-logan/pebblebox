#include "ode/ode.h"
#include <tuple>

#ifndef ENTITIES_H
#define ENTITIES_H

using namespace std;

class Entity {
public:
    dBodyID body;
    dGeomID geom;
    Entity(tuple<dBodyID, dGeomID> bodyAndGeom);
    virtual void dummyFunc() {}
};

class SimpleBox : public Entity
{
public:
    tuple<dBodyID, dGeomID> createBodyAndGeom(dWorldID world, dSpaceID space);
    SimpleBox(dWorldID world, dSpaceID space);
    void dummyFunc() {}
};

#endif // ENTITIES_H