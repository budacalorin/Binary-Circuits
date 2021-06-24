#ifndef NOTGATE_H
#define NOTGATE_H
#include "conector.h"
#include <SFML/Graphics.hpp>
#include "line.h"

class notGate
{
    public:
        notGate();
        conector *input;
        conector *output;
        sf::RectangleShape shape;
        line lineInput;
        line lineOutput;

        bool active;

        int indiceInput;

        bool run();
        void reset();
};

#endif // NOTGATE_H
