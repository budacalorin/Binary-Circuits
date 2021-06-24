#include "line.h"

line::line()
{
    //ctor
}

void line::set_color(sf::Color col)
{
    color = col;
    shape[1].color = col;
    shape[0].color = col;
}

void line::set_position(sf::Vector2f posX, sf::Vector2f posY)
{
    shape[0].position = posX;
    shape[1].position = posY;
}

void line::set_connector(int indice)
{
    indiceConnector = indice;
}

void line::reset()
{
    active=0;
}
