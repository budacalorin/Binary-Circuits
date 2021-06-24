#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

extern sf::RenderWindow window;
extern sf::RectangleShape background;
extern sf::Texture background_texture;
extern bool gameOn;
extern int height;
extern int width;
extern int scena_curenta;
extern sf::Clock globalClock;
extern sf::Font font;
extern sf::Texture andT;
extern sf::Texture notT;
extern sf::Texture orT;
extern sf::Texture xorT;
extern sf::Texture clockT;

extern sf::Color pornitC,opritC,andC,orC,notC,clockC,textC,buttonBorderC,piceBorderC,ghostBorderC,inactiveC;
#endif // INIT_H_INCLUDED
