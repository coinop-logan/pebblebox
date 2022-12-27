#include "utils.h"

sf::Vector3f getBodyPosition(dBodyID body)
{
    const dReal* pos = dBodyGetPosition(body);
    return sf::Vector3f(pos[0], pos[1], pos[2]);
}