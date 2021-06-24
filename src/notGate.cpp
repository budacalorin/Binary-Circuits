#include "notGate.h"
#include "init.h"
#include <iostream>
notGate::notGate()
{
    input = NULL;
    output = NULL;
    //shape.setOutlineThickness(1);
    //shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(100, 100, 100));
}

bool notGate::run()
{
    if (input != NULL && output != NULL)
    {
        output->set_state(!input->get_state());
        return !input->get_state();
    }
    return 0;
    //std::cout << "BUG, Poarta not rulata fara input";
}

void notGate::reset()
{
    active=0;
    indiceInput=0;
    input=output=NULL;
    lineInput.set_connector(0);
    lineOutput.set_connector(0);
    shape.setTexture(&notT);
}
