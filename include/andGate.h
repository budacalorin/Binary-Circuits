#ifndef ANDGATE_H
#define ANDGATE_H

#include "conector.h"
#include "SFML/Graphics.hpp"
#include "line.h"

class andGate
{
    public:
        conector *input1;
        conector *input2;
        conector *output;
        sf::RectangleShape shape;

        line lineInput1;
        line lineInput2;
        line lineOutput;

        int indiceInput1;
        int indiceInput2;

        bool active;


        andGate();
        bool run();
        void reset();
};

#endif // ANDGATE_H
