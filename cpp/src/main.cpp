#include <iostream>
#include <ode/ode.h>

using namespace std;

static dWorldID world;
static dSpaceID space;
static dJointGroupID contactgroup;
static dBodyID body1, body2;
static dGeomID geom1, geom2;

void startPhysics()
{
    dInitODE();
    contactgroup = dJointGroupCreate(0);
    world = dWorldCreate();
    space = dSimpleSpaceCreate(0);

    // dWorldSetGravity(world, 0, 0, -9.8);

    dMass m;
    dMassSetBox (&m, 1, 0.5f ,0.5f, 0.5f);
    dMassAdjust (&m, 1);
    
    body1 = dBodyCreate(world);
    dBodySetMass(body1,&m);
    dBodySetPosition (body1, 0, 0, 1);
    body2 = dBodyCreate(world);
    dBodySetMass(body2,&m);
    dBodySetPosition (body2, 1, 0, 1);

    geom1 = dCreateBox(space, 0.5, 0.5, 0.5);
    geom2 = dCreateBox(space, 0.5, 0.5, 0.5);

    dGeomSetBody(geom1, body1);
    dGeomSetBody(geom2, body2);

    dBodyAddForce(body2, -10, 0, 0);
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

    while (true)
    {
        stepPhysics();
        const dReal* pos = dBodyGetPosition(body1);
        cout << "1: " << pos[0] << ", " << pos[1] << ", " << pos[2] << endl;
        pos = dBodyGetPosition(body2);
        cout << "2: " << pos[0] << ", " << pos[1] << ", " << pos[2] << endl;
        cin.get();
    }

    cleanupPhysics();

    return 0;
}