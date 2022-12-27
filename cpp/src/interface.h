#include <SFML/Graphics.hpp>

#ifndef INTERFACE_H
#define INTERFACE_H

using namespace std;

enum InterfaceEvent {
    Quit
};

optional<InterfaceEvent> handleEvent(sf::Event);

#endif // INTERFACE_H