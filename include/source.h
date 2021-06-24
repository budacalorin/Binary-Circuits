#ifndef SOURCE_H
#define SOURCE_H
#include "line.h"
#include "conector.h"
#include <SFML/Graphics.hpp>

class source
{
    public:
        line lineOutput;
        conector *output;
        sf::RectangleShape shape;
        bool active;
        bool state;

        source();
        void reset();
        bool run();
        void set_state(bool stare);
        bool get_state();

};

#endif // SOURCE_H
