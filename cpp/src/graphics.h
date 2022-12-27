#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "entities.h"

#ifndef GRAPHICS_H
#define GRAPHICS_H

sf::RenderWindow* setupGraphics();
void cleanupGraphics(sf::RenderWindow*);

void display(sf::RenderWindow*, vector<boost::shared_ptr<Entity>>);
void drawEntity(sf::RenderWindow*, boost::shared_ptr<Entity>);

#endif // GRAPHICS_H