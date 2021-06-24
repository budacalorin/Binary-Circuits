#include "source.h"

source::source()
{
    lineOutput.active=1;
    lineOutput.indiceConnector=0;
    output=NULL;

    shape.setFillColor(sf::Color(100,100,100));
}

bool source::run()
{
    if (output!=NULL)
    {
        output->set_state(state);
        return state;
    }
    return 0;
}

bool source::get_state()
{
    return state;
}

void source::set_state(bool stare)
{
    state=stare;
}

void source::reset()
{
    active=0;
    state=0;
    lineOutput.indiceConnector=0;
    output=NULL;
}
