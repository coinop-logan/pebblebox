#include <iostream>
#include <ode/ode.h>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "entities.h"

using namespace std;

static dWorldID world;
static dSpaceID space;
static dJointGroupID contactgroup;

vector<boost::shared_ptr<Entity>> entities;

void startPhysics()
{
    dInitODE();
    contactgroup = dJointGroupCreate(0);
    world = dWorldCreate();
    space = dSimpleSpaceCreate(0);

    // dWorldSetGravity(world, 0, 0, -9.8);

    // dBodyAddForce(body2, -10, 0, 0);
}

void cleanupPhysics()
{
    dJointGroupDestroy(contactgroup);
    dSpaceDestroy (space);
    dWorldDestroy (world);
    dCloseODE();
}

static void nearCallback(void *, dGeomID o1, dGeomID o2)
{
    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);

    dContact contact;
    contact.surface.mode = dContactBounce;
    contact.surface.mu = dInfinity;
    contact.surface.bounce = 1;
    if (dCollide (o1,o2,1,&contact.geom,sizeof(dContactGeom))) {
        dJointID c = dJointCreateContact (world,contactgroup,&contact);
        dJointAttach (c,b1,b2);
    }
}

void stepPhysics()
{
    dSpaceCollide(space,0,&nearCallback);
    dWorldQuickStep (world,0.05);
	dJointGroupEmpty(contactgroup);
}

int main()
{
    startPhysics();

    entities.push_back(boost::shared_ptr<SimpleBox>(new SimpleBox(world, space)));

    while (true)
    {
        stepPhysics();
        
        if (entities.size() > 0)
        {
            const dReal* pos = dBodyGetPosition(entities[0]->body);
            cout << "1: " << pos[0] << ", " << pos[1] << ", " << pos[2] << endl;
        }
        cin.get();
    }

    cleanupPhysics();

    return 0;
}