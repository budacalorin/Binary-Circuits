#ifndef CEAS_H
#define CEAS_H
#include "conector.h"
#include "line.h"
#include <SFML/Graphics.hpp>

class ceas
{
    public:
        int timpRamas;
        bool semn;
        int timpTrue;
        int timpFalse;
        conector *outputConnector;
        sf::RectangleShape shape;
        line lineOutput;
        bool active;
        sf::RectangleShape bara;


        ceas();
        void update(long long timpTrecut);
        void reset();
};

#endif // CEAS_H
