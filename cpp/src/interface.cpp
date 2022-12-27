#include "interface.h"

optional<InterfaceEvent> handleEvent(sf::Event event)
{
    switch (event.type)
    {
        case sf::Event::Closed:
        {
            return Quit;
            break;
        }
        default:
            return {};
    }
}