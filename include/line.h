#ifndef LINE_H
#define LINE_H
#include <SFML/Graphics.hpp>

class line
{
    public:
        sf::Color color;
        int indiceConnector;
        sf::Vertex shape[2];
        bool active;

        line();
        void set_position(sf::Vector2f posX, sf::Vector2f posY);
        void set_color(sf::Color col);
        void set_connector(int indice);
        void reset();

};

#endif // LINE_H
