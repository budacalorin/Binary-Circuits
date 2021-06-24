#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <fstream>
#include "include/init.h"
#include "include/scena_joc.h"
#include "include/scena_meniu.h"
using namespace std;

bool gameOn = 1;
int height = 768;
int width = 1366;
int scena_curenta = 1;

scena_meniu meniu_principal;
scena_meniu meniu_circuite;
scena_joc joc_principal;
sf::Texture background_texture;
sf::Texture *p_background_texture;
sf::RectangleShape background;
sf::Clock globalClock;

sf::RenderWindow window(sf::VideoMode(width, height), "", sf::Style::Fullscreen);
sf::Clock ceas_general;
sf::Color pornitC,opritC,andC,orC,notC,clockC,textC,buttonBorderC,piceBorderC,ghostBorderC,inactiveC;
sf::Font dejaVuSans;
sf::Font font;
sf::Font arial;

sf::Texture notT;
sf::Texture andT;
sf::Texture orT;
sf::Texture xorT;
sf::Texture clockT;
void set_color(sf::Color &culoare,int r,int g,int b,int a=255)
{
    culoare.r=r;
    culoare.g=g;
    culoare.b=b;
    culoare.a=a;
}

void setup()
{
    set_color(pornitC,255, 0, 0,200);
    set_color(opritC,244, 172, 69,200);
    set_color(andC,76, 254, 118);
    set_color(notC,251, 186, 114);
    set_color(orC,42, 157, 143);
    set_color(clockC,132, 160, 124);
    set_color(textC,0,0,0);
    set_color(buttonBorderC,0,0,0);
    set_color(piceBorderC,0,0,0);
    set_color(ghostBorderC,242, 112, 89);
    set_color(inactiveC,50, 50, 50);

    dejaVuSans.loadFromFile("DejaVuSans.ttf");
    arial.loadFromFile("arial.ttf");

    background_texture.loadFromFile("img/lab2.png");
    p_background_texture = &background_texture;
    background.setTexture(p_background_texture);
    background.setSize(sf::Vector2f(width, height));
    meniu_principal.adaugare_optiune("Play");
    meniu_principal.adaugare_optiune("Exit");
    meniu_principal.generare_text();
    andT.loadFromFile("img/and.png");
    notT.loadFromFile("img/not3.png");
    orT.loadFromFile("img/or.png");
    xorT.loadFromFile("img/xor.png");
    clockT.loadFromFile("img/clock.png");
}

int main()
{
    setup();


    font=arial;


    sf::Clock ceas;
    sf::Clock c;
    int fps = 0;
    int timp_per_frame = 1000000 / 120;
    while (gameOn)
    {
        fps++;
        if (c.getElapsedTime().asSeconds() >= 1)
        {
            c.restart();
            //cout << fps << endl;
            fps = 0;
        }
        int timp = ceas.getElapsedTime().asMicroseconds();
        if (scena_curenta==-1)
        {
            meniu_circuite.numar_optiuni=0;
            meniu_circuite.adaugare_optiune("Playground");
            ifstream fin("saves/saves.txt");

            char text[100];
            while (fin.peek()!=EOF)
            {
                fin.getline(text,100);
                ifstream fin("saves/saves.txt");
                if (text[0]=='N'&&text[1]==':')
                {
                    strcpy(text,text+2);
                    meniu_circuite.adaugare_optiune(text);
                }

            }
            meniu_circuite.generare_text();
            fin.close();
            scena_curenta=3;
        }
        if (scena_curenta == 0)
        {
            joc_principal.reset(meniu_circuite.optiuni[meniu_circuite.optiune_curenta]);
            scena_curenta = 2;
        }
        if (scena_curenta == 1)
        {
            meniu_principal.update();
        }
        if (scena_curenta == 2)
        {
            joc_principal.update();
        }
        if (scena_curenta == 3)
        {
            meniu_circuite.update();
        }


        if (ceas.getElapsedTime().asMicroseconds() - timp < timp_per_frame)
        {
            sf::sleep(sf::microseconds(timp_per_frame - (ceas.getElapsedTime().asMicroseconds() - timp)));
        }
    }
    return 0;
}
