#include <iostream>
#include <ode/ode.h>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>

#include "graphics.h"
#include "entities.h"
#include "interface.h"

using namespace std;

static dWorldID world;

//defines one group of objects that may interact
static dSpaceID space;

//Creates a group that will be filled with contact joints for all collisions on a given frame.
//every frame, the group is emptied after simulation
static dJointGroupID contactGroup;
vector<boost::shared_ptr<Entity>> entities;

void startPhysics()
{

    dInitODE();

    //init "contact" joint group
    contactGroup = dJointGroupCreate(0);
    
    world = dWorldCreate();
    space = dSimpleSpaceCreate(0);

    // dWorldSetGravity(world, 0, 0, -9.8);

    // dBodyAddForce(body2, -10, 0, 0);
}

void cleanupPhysics()
{
    dJointGroupDestroy(contactGroup);
    dSpaceDestroy (space);
    dWorldDestroy (world);
    dCloseODE();
}

//called when two object are near each other
static void nearCallback(void *, dGeomID o1, dGeomID o2)
{
    //two objects that might be colliding
    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);

    //where we define the behavior of this collision using a structure `contact`
    dContact contact;
    contact.surface.mode = dContactBounce;

    // "mu" is a physics term for friction
    contact.surface.mu = dInfinity; //Full friction, no slippage

    contact.surface.bounce = 1; // 1 = "full bounce"

    //if there is a contact: dCollide returns the number of contacts (i.e. collisions) we need to handle.
    //Here, the third argument "1" indicates we will only ever deal with 1 collision (otherwise we'd need a for loop and an array)
    if (dCollide (o1,o2,1,&contact.geom,sizeof(dContactGeom))) {
        //Creates a "contact" type joint. Passes in world, joint contact group for collision, and a reference to the behavior of the contact.
        dJointID c = dJointCreateContact (world,contactGroup,&contact);

        //connects the bodies by the newly defined joint
        dJointAttach (c,b1,b2);
    }
}

void stepPhysics()
{
    // Below, note that the `contactGroup` is used as a sort of temporary container for all of the
    // "contact" joints, which were created in nearCallback for every collision
    // then these are cleared.
    // The result is that when `dWorldQuickStep` is called, there are joints representing the constraints of current collisions

    // This calls our nearCallback for every possible collision - which adds "contact" joints to contactGroup
    dSpaceCollide(space,0,&nearCallback);

    // simulate the world for 0.05 seconds
    dWorldQuickStep (world,0.05);

    // This clears all of the "contact" joints
	dJointGroupEmpty(contactGroup);
}

int main()
{
    sf::RenderWindow* window = setupGraphics();
    startPhysics();

    entities.push_back(boost::shared_ptr<SimpleBox>(new SimpleBox(world, space)));
    entities.push_back(boost::shared_ptr<SimpleBox>(new SimpleBox(world, space)));

    dBodyAddForce(entities[0]->body, 0.01, 0, 0);
    dBodySetPosition(entities[1]->body, 1, 0, 0);

    while (true)
    {
        stepPhysics();

        sf::Event event;
        while (window->pollEvent(event))
        {
            auto maybeInterfaceEvent = handleEvent(event);
            if (maybeInterfaceEvent)
            {
                switch (*maybeInterfaceEvent)
                {
                    case Quit:
                    {
                        window->close();
                        break;
                    }
                }
            }
        }
        
        display(window, entities);
    }

    cleanupPhysics();
    cleanupGraphics(window);

    return 0;
}