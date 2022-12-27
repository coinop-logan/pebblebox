#include "graphics.h"
#include "utils.h"

sf::RenderWindow* setupGraphics()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(800, 600)), "3D Triangle");

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glViewport(0, 0, window->getSize().x, window->getSize().y);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspect = (GLfloat)window->getSize().x / (GLfloat)window->getSize().y;
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    return window;
}
void cleanupGraphics(sf::RenderWindow* window)
{
    delete window;
}

void display(sf::RenderWindow* window, vector<boost::shared_ptr<Entity>> entities)
{
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the camera position
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, -10.0f,  // Eye position
                0.0f, 0.0f, 0.0f,  // Look at position
                0.0f, 1.0f, 0.0f); // Up vector
    
    for (unsigned int i=0; i<entities.size(); i++)
    {
        drawEntity(window, entities[i]);
    }

    // Display the window
    window->display();
}

void drawEntity(sf::RenderWindow* window, boost::shared_ptr<Entity> entity)
{
    sf::Vector3f pos = getBodyPosition(entity->body);
    if (auto simpleBox = boost::dynamic_pointer_cast<SimpleBox, Entity>(entity))
    {
        glPushMatrix();
            glTranslatef(pos.x, pos.y, pos.z);
            glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 0.0f);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glEnd();
        glPopMatrix();
    }
}