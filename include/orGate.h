#ifndef ORGATE_H
#define ORGATE_H
#include "conector.h"
#include <SFML/Graphics.hpp>
#include "line.h"
class orGate
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

        orGate();
        bool run();
        void reset();
};

#endif // ORGATE_H
