#include "entities.h"

Entity::Entity(tuple<dBodyID, dGeomID> bodyAndGeom)
{
    body = get<0>(bodyAndGeom);
    geom = get<1>(bodyAndGeom);
}

tuple<dBodyID, dGeomID> SimpleBox::createBodyAndGeom(dWorldID world, dSpaceID space)
{
    dMass m;
    dMassSetBox (&m, 1, 0.5f, 0.5f, 0.5f);
    dMassAdjust (&m, 1);
    
    dBodyID generatedBody = dBodyCreate(world);
    dBodySetMass(generatedBody, &m);
    dBodySetPosition (generatedBody, 0, 0, 1);

    dGeomID generatedGeom = dCreateBox(space, 0.5, 0.5, 0.5);

    dGeomSetBody(generatedGeom, generatedBody);

    return {generatedBody, generatedGeom};
}
SimpleBox::SimpleBox(dWorldID world, dSpaceID space)
    : Entity(createBodyAndGeom(world, space)) {}