#include <iostream>
#include <ode/ode.h>

using namespace std;

static dWorldID world;
static dSpaceID space;
static dJointGroupID contactgroup;

void startPhysics()
{
    dInitODE();
    contactgroup = dJointGroupCreate(0);
    world = dWorldCreate();
    space = dSimpleSpaceCreate(0);
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
    contact.surface.mode = 0;
    contact.surface.mu = dInfinity;
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

    // while (true)
    // {
        stepPhysics();
    // }

    cleanupPhysics();

    return 0;
}