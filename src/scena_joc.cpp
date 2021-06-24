#include "../include/scena_joc.h"
#include "../include/init.h"
#include <cstdio>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void scena_joc::update()
{
    long long timpTrecut = update_timp();
    if (saving==0)
        update_events();
    else
        saving_screen();
    logic(timpTrecut);
    draw();
}

void scena_joc::logic(long long timpTrecut)
{
    update_clocks(timpTrecut);
    for (int i = 1; i <= numarAnd; i++)
    {
        if (andGates[i].active==1)
            andGates[i].run();
    }
    for (int i = 1; i <= numarOr; i++)
    {
        if (orGates[i].active==1)
            orGates[i].run();
    }
    for (int i = 1; i <= numarXor; i++)
    {
        if (xorGates[i].active==1)
            xorGates[i].run();
    }
    for (int i = 1; i <= numarNot; i++)
    {
        if (notGates[i].active==1)
            notGates[i].run();
    }
    update_buttons();
    update_surse();

}

void scena_joc::draw()
{
    window.clear();

    window.draw(background);
    draw_lines();
    draw_and_gates();
    draw_or_gates();
    draw_xor_gates();
    draw_clocks();
    draw_not_gates();
    draw_surse();
    //draw_buttons();
    if (playgorund&&piesaSelectata!=2)
        window.draw(ghost);
    draw_piese();
    draw_markers();
    if (saving==1)
    {
        sf::Text presetName;
        presetName.setFont(font);
        presetName.setCharacterSize(80);
        presetName.setColor(sf::Color::Black);
        presetName.setString("Preset Name:");
        presetName.setPosition(sf::Vector2f(width/2,height/2));
        fix_marker(presetName,sf::FloatRect(width/2-1,height/2-1,2,2));
        window.draw(presetName);

        sf::Text theName;
        theName.setFont(font);
        theName.setCharacterSize(80);
        theName.setColor(sf::Color::Black);
        theName.setString(preset_name);
        theName.setPosition(sf::Vector2f(width/2,height/2));
        fix_marker(theName,sf::FloatRect(width/2-1,height/2+80,2,2));
        window.draw(theName);
    }

    window.display();
}

void scena_joc::draw_and_gates()
{
    for (int i = 1; i <= numarAnd; i++)
    {
        if (andGates[i].active==1)
        {
            window.draw(andGates[i].shape);

            if (andGates[i].input1!=NULL)
                andGates[i].lineInput1.set_color((connectors[andGates[i].lineInput1.indiceConnector].get_state() == 0) ? opritC : pornitC);
            else
                andGates[i].lineInput1.set_color(inactiveC);
            window.draw(andGates[i].lineInput1.shape, 2, sf::Lines);

            if (andGates[i].input2!=NULL)
                andGates[i].lineInput2.set_color((connectors[andGates[i].lineInput2.indiceConnector].get_state() == 0) ? opritC : pornitC);
            else
                andGates[i].lineInput2.set_color(inactiveC);
            window.draw(andGates[i].lineInput2.shape, 2, sf::Lines);

            if (andGates[i].output!=NULL)
                andGates[i].lineOutput.set_color((connectors[andGates[i].lineOutput.indiceConnector].get_state() == 0) ? opritC : pornitC);
            else
                andGates[i].lineOutput.set_color(inactiveC);
            window.draw(andGates[i].lineOutput.shape, 2, sf::Lines);
        }
    }
}

void scena_joc::draw_or_gates()
{
    for (int i = 1; i <= numarOr; i++)
    {
        if (orGates[i].active==1)
        {
            window.draw(orGates[i].shape);

            orGates[i].lineInput1.set_color((connectors[orGates[i].lineInput1.indiceConnector].get_state() == 0) ? opritC : pornitC);
            if (orGates[i].input1==NULL)
                orGates[i].lineInput1.set_color(inactiveC);
            window.draw(orGates[i].lineInput1.shape, 2, sf::Lines);

            orGates[i].lineInput2.set_color((connectors[orGates[i].lineInput2.indiceConnector].get_state() == 0) ? opritC : pornitC);
            if (orGates[i].input2==NULL)
                orGates[i].lineInput2.set_color(inactiveC);
            window.draw(orGates[i].lineInput2.shape, 2, sf::Lines);

            orGates[i].lineOutput.set_color((connectors[orGates[i].lineOutput.indiceConnector].get_state() == 0) ? opritC : pornitC);
            if (orGates[i].output==NULL)
                orGates[i].lineOutput.set_color(inactiveC);
            window.draw(orGates[i].lineOutput.shape, 2, sf::Lines);
        }
    }
}

void scena_joc::draw_xor_gates()
{
    for (int i = 1; i <= numarXor; i++)
    {
        if (xorGates[i].active==1)
        {
            window.draw(xorGates[i].shape);

            xorGates[i].lineInput1.set_color((connectors[xorGates[i].lineInput1.indiceConnector].get_state() == 0) ? opritC : pornitC);
            if (xorGates[i].input1==NULL)
                xorGates[i].lineInput1.set_color(inactiveC);
            window.draw(xorGates[i].lineInput1.shape, 2, sf::Lines);

            xorGates[i].lineInput2.set_color((connectors[xorGates[i].lineInput2.indiceConnector].get_state() == 0) ? opritC : pornitC);
            if (xorGates[i].input2==NULL)
                xorGates[i].lineInput2.set_color(inactiveC);
            window.draw(xorGates[i].lineInput2.shape, 2, sf::Lines);

            xorGates[i].lineOutput.set_color((connectors[xorGates[i].lineOutput.indiceConnector].get_state() == 0) ? opritC : pornitC);
            if (xorGates[i].output==NULL)
                xorGates[i].lineOutput.set_color(inactiveC);
            window.draw(xorGates[i].lineOutput.shape, 2, sf::Lines);
        }
    }
}

void scena_joc::draw_not_gates()
{
    for (int i = 1; i <= numarNot; i++)
    {
        if (notGates[i].active==1)
        {
            window.draw(notGates[i].shape);
            notGates[i].lineInput.set_color((connectors[notGates[i].lineInput.indiceConnector].get_state() == 0) ? opritC : pornitC);
            if (notGates[i].input==NULL)
                notGates[i].lineInput.set_color(inactiveC);
            window.draw(notGates[i].lineInput.shape, 2, sf::Lines);
            notGates[i].lineOutput.set_color((connectors[notGates[i].lineOutput.indiceConnector].get_state() == 0) ? opritC : pornitC);
            if (notGates[i].output==NULL)
                notGates[i].lineOutput.set_color(inactiveC);
            window.draw(notGates[i].lineOutput.shape, 2, sf::Lines);
        }
    }
}

void scena_joc::draw_lines()
{
    for (int i = 1; i <= numarLines; i++)
    {
        if (lines[i].active==1)
        {
            lines[i].shape[0].color = lines[i].shape[1].color = (connectors[lines[i].indiceConnector].get_state() == 0) ? opritC : pornitC;
            window.draw(lines[i].shape, 2, sf::Lines);
        }
    }
}

void scena_joc::draw_buttons()
{
    int x=1;
    int y=1;
    int k=1;
    for (int i=1; i<=numarConectoare; i++)
    {
        if (connectors[i].alive==1)
        {
            buttons[k].setPosition(sf::Vector2f(x,y));
            buttons[k].setFillColor((connectors[i].get_state()==1)?pornitC:opritC);
            window.draw(buttons[k]);
            x+=72;
            if (x>1366-72)
            {
                x=1;
                y+=72;
            }
            k++;
        }
    }
}

void scena_joc::draw_clocks()
{
    for (int i = 1; i <= numarClocks; i++)
    {
        if (ceasuri[i].active==1)
        {
            window.draw(ceasuri[i].shape);
            if (ceasuri[i].outputConnector==NULL)
                ceasuri[i].lineOutput.set_color(inactiveC);
            else
                ceasuri[i].lineOutput.set_color((connectors[ceasuri[i].lineOutput.indiceConnector].get_state() == 0) ? opritC : pornitC);
            window.draw(ceasuri[i].bara);
            window.draw(ceasuri[i].lineOutput.shape, 2, sf::Lines);

        }
    }
}

void scena_joc::draw_markers()
{
    for (int i = 1; i <= numarMarkers; i++)
    {
        window.draw(markers[i]);
    }
}

void scena_joc::draw_piese()
{
    for (int i=1; i<=numarPiese; i++)
    {
        if (piesaSelectata==i)
        {
            piese[i].setFillColor(pornitC);
        }
        else
        {
            piese[i].setFillColor(opritC);
        }
        window.draw(piese[i]);
    }
}

void scena_joc::draw_surse()
{
    for (int i=1; i<=numarSurse; i++)
    {
        if (sources[i].active==1)
        {
            if (sources[i].get_state()==1)
            {
                sources[i].shape.setFillColor(pornitC);
            }
            else
            {
                sources[i].shape.setFillColor(opritC);
            }
            window.draw(sources[i].shape);
            if (sources[i].lineOutput.indiceConnector==0)
            {
                sources[i].lineOutput.set_color(inactiveC);
            }
            else
            {
                if (connectors[sources[i].lineOutput.indiceConnector].get_state()==1)
                {
                    sources[i].lineOutput.set_color(pornitC);
                }
                else
                {
                    sources[i].lineOutput.set_color(opritC);
                }
            }
            window.draw(sources[i].lineOutput.shape,2,sf::Lines);

        }
    }
}


void scena_joc::verificare_final()
{

}

void scena_joc::reset(string preset)
{
    saving=0;
    numarClocks = 0;
    numarAnd = 0;
    numarConectoare = 0;
    numarDLatches = 0;
    numarOr = 0;
    numarNot = 0;
    numarMarkers = 0;
    playgorund = 0;
    numarPiese=0;
    numarLines=0;
    numarSurse=0;

    reset_porti();

    for (int i = 0; i < 100; i++)
    {
        markers[i].setFont(font);
        markers[i].setCharacterSize(20);
        markers[i].setString("NONE");
    }

    for (int i=1; i<100; i++)
    {
        piese[i].setPosition(sf::Vector2f(100*(i-1),768-100));
        piese[i].setSize(sf::Vector2f(100,100));
    }
    if (preset=="Playground")
    {
        setup_playgorund();
    }
    else
    {
        setup_special(preset);
    }
    int k=0;
    for (int i = 1; i < 768; i+=72)
    {
        for (int j=1; j< 1366; j+=72)
        {
            if (k==99)
                break;
            k++;
            buttons[k].setSize(sf::Vector2f(70, 70));
            buttons[k].setPosition(sf::Vector2f(j,i));
            buttons[k].setFillColor(opritC);
            buttons[k].setOutlineColor(buttonBorderC);
            buttons[k].setOutlineThickness(1);
        }
    }
    timp_precedent = globalClock.getElapsedTime().asMicroseconds();
}

void scena_joc::reset_porti()
{
    for (int i=1; i<100; i++)
        connectors[i].set_state(false);
    for (int i=1; i<30; i++)
    {
        notGates[i].reset();
        andGates[i].reset();
        orGates[i].reset();
        xorGates[i].reset();
        ceasuri[i].reset();
        sources[i].reset();
    }
    for (int i=1; i<100; i++)
        lines[i].reset();
}


void scena_joc::update_events()
{

    sf::Event event;
    sf::Mouse mouse;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            gameOn = 0;
        }
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                scena_curenta = -1;
            }
            if (event.key.code== sf::Keyboard::S&&playgorund==1)
            {
                preset_name="";
                saving=1;
            }
        }
        if ((int)event.type == (int)sf::Event::MouseButtonReleased&&(int)event.key.code==(int)sf::Mouse::Left)
        {
            for (int i=1; i<=numarSurse; i++)
            {
                if (sources[i].shape.getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window).x,mouse.getPosition(window).y))&&sources[i].active==1)
                {
                    sources[i].set_state(1-sources[i].get_state());
                }
            }
        }
        if (playgorund)
        {
            if (event.type==sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                    {
                        piesaSelectata--;
                        break;
                    }
                case sf::Keyboard::Right:
                    {
                        piesaSelectata++;
                        break;
                    }
                default:
                    {
                        break;
                    }
                }
                if (piesaSelectata<1)
                {
                    piesaSelectata=numarPiese;
                }

                if (piesaSelectata>numarPiese)
                {
                    piesaSelectata=1;
                }
            }
            ghost.setPosition(sf::Vector2f(mouse.getPosition(window).x,mouse.getPosition(window).y));

            if (event.type==sf::Event::MouseWheelScrolled)
            {
                bool ok=1;
                for (int i=1; i<=numarClocks; i++)
                {
                    if (ceasuri[i].active&&ceasuri[i].shape.getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window).x,mouse.getPosition(window).y)))
                    {
                        ok=0;
                        break;
                    }
                }
                if (event.mouseWheelScroll.delta>0&&ok==1)
                {
                    ghost.scale(1.05,1.05);
                }
                if (event.mouseWheelScroll.delta<0&&ok==1)
                {
                    ghost.scale(0.95,0.95);
                }
            }

            if (event.type==sf::Event::MouseButtonPressed&&mouse.isButtonPressed(mouse.Left))
            {
                bool ok=1;
                for (int i=1; i<=numarPiese; i++)
                    if (piese[i].getGlobalBounds().contains(sf::Vector2f(mouse.getPosition().x,mouse.getPosition().y)))
                    {
                        ok=0;
                        piesaSelectata=i;
                    }
                for (int i=1; i<=numarSurse; i++)
                {
                    if (sources[i].shape.getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window).x,mouse.getPosition(window).y))&&sources[i].active==1)
                    {
                        ok=0;
                    }
                }
                if (ok==1)
                    add(piesaSelectata,sf::Vector2f(mouse.getPosition(window).x,mouse.getPosition(window).y),sf::Vector2f(ghost.getGlobalBounds().width,ghost.getGlobalBounds().height));
            }
            if (event.type==sf::Event::MouseButtonPressed&&mouse.isButtonPressed(mouse.Right))
            {
                bool ok=1;
                if (ok==1)
                    erase(sf::Vector2f(mouse.getPosition().x,mouse.getPosition().y));
            }
            if (setLine==1)
            {
                lines[numarLines].shape[1].position=sf::Vector2f(mouse.getPosition(window).x,mouse.getPosition(window).y);
                connect(numarLines,0);
            }
        }
        if (event.type==sf::Event::MouseWheelScrolled)
        {
            for (int i=1; i<=numarClocks; i++)
            {
                if (ceasuri[i].active&&ceasuri[i].shape.getGlobalBounds().contains(sf::Vector2f(mouse.getPosition(window).x,mouse.getPosition(window).y)))
                {
                    if (event.mouseWheelScroll.delta>0)
                    {
                        ceasuri[i].timpTrue-=50000;
                        if (ceasuri[i].timpTrue<30)
                            ceasuri[i].timpTrue=30;
                        ceasuri[i].timpFalse+=50000;
                        if (ceasuri[i].timpFalse>2000000)
                            ceasuri[i].timpFalse=2000000;
                    }
                    if (event.mouseWheelScroll.delta<0)
                    {
                        ceasuri[i].timpFalse-=50000;
                        if (ceasuri[i].timpFalse<30)
                            ceasuri[i].timpFalse=30;
                        ceasuri[i].timpTrue+=50000;
                        if (ceasuri[i].timpTrue>2000000)
                            ceasuri[i].timpTrue=2000000;
                    }
                }
            }
        }
    }
}


void scena_joc::add_and_gate(sf::Vector2f Size, sf::Vector2f position, sf::Color color)
{
    numarAnd++;

    andGates[numarAnd].active=1;

    andGates[numarAnd].shape.setSize(Size);
    andGates[numarAnd].shape.setOrigin(sf::Vector2f(Size.x / 2, Size.y / 2));
    andGates[numarAnd].shape.setPosition(position);
    andGates[numarAnd].shape.setFillColor(color);

    andGates[numarAnd].lineInput1.set_position(sf::Vector2f(position.x - Size.x / 2, position.y - Size.y / 4), sf::Vector2f(position.x - Size.x / 2 - Size.x / 4, position.y - Size.y / 4));

    andGates[numarAnd].lineInput2.set_position(sf::Vector2f(position.x - Size.x / 2, position.y + Size.y / 4), sf::Vector2f(position.x - Size.x / 2 - Size.x / 4, position.y + Size.y / 4));

    andGates[numarAnd].lineOutput.set_position(sf::Vector2f(position.x + (Size.x / 2), position.y), sf::Vector2f(position.x + (Size.x / 2) + (Size.x / 4), position.y));

    //add_marker(sf::Vector2f(position.x - Size.x / 2, position.y - Size.y / 8), "AND", Size.y / 3, textC, andGates[numarAnd].shape.getGlobalBounds());
}

void scena_joc::add_or_gate(sf::Vector2f Size, sf::Vector2f position, sf::Color color)
{
    numarOr++;

    orGates[numarOr].active=1;

    orGates[numarOr].shape.setSize(Size);
    orGates[numarOr].shape.setOrigin(sf::Vector2f(Size.x / 2, Size.y / 2));
    orGates[numarOr].shape.setPosition(position);
    orGates[numarOr].shape.setFillColor(color);

    orGates[numarOr].lineInput1.set_position(sf::Vector2f(position.x - Size.x / 4, position.y - Size.y / 4), sf::Vector2f(position.x - Size.x / 2 - Size.x / 4, position.y - Size.y / 4));

    orGates[numarOr].lineInput2.set_position(sf::Vector2f(position.x - Size.x / 4, position.y + Size.y / 4), sf::Vector2f(position.x - Size.x / 2 - Size.x / 4, position.y + Size.y / 4));

    orGates[numarOr].lineOutput.set_position(sf::Vector2f(position.x + Size.x / 2, position.y), sf::Vector2f(position.x + Size.x / 2 + Size.x / 4, position.y));

    //add_marker(sf::Vector2f(position.x - Size.x / 2, position.y - Size.y / 8), "OR", Size.y / 2, textC, orGates[numarOr].shape.getGlobalBounds());
}

void scena_joc::add_xor_gate(sf::Vector2f Size, sf::Vector2f position, sf::Color color)
{
    numarXor++;

    xorGates[numarXor].active=1;

    xorGates[numarXor].shape.setSize(Size);
    xorGates[numarXor].shape.setOrigin(sf::Vector2f(Size.x / 2, Size.y / 2));
    xorGates[numarXor].shape.setPosition(position);
    xorGates[numarXor].shape.setFillColor(color);

    xorGates[numarXor].lineInput1.set_position(sf::Vector2f(position.x - Size.x / 4, position.y - Size.y / 4), sf::Vector2f(position.x - Size.x / 2 - Size.x / 4, position.y - Size.y / 4));

    xorGates[numarXor].lineInput2.set_position(sf::Vector2f(position.x - Size.x / 4, position.y + Size.y / 4), sf::Vector2f(position.x - Size.x / 2 - Size.x / 4, position.y + Size.y / 4));

    xorGates[numarXor].lineOutput.set_position(sf::Vector2f(position.x + Size.x / 2, position.y), sf::Vector2f(position.x + Size.x / 2 + Size.x / 4, position.y));

    //add_marker(sf::Vector2f(position.x - Size.x / 2, position.y - Size.y / 8), "OR", Size.y / 2, textC, xorGates[numarOr].shape.getGlobalBounds());
}

void scena_joc::add_not_gate(sf::Vector2f Size, sf::Vector2f position, sf::Color color)
{
    numarNot++;

    notGates[numarNot].active=1;

    notGates[numarNot].shape.setSize(Size);
    notGates[numarNot].shape.setOrigin(sf::Vector2f(Size.x / 2, Size.y / 2));
    notGates[numarNot].shape.setPosition(position);
    notGates[numarNot].shape.setFillColor(color);

    notGates[numarNot].lineInput.set_position(sf::Vector2f(position.x - Size.x / 2, position.y), sf::Vector2f(position.x - Size.x / 2 - Size.x / 4, position.y));

    notGates[numarNot].lineOutput.set_position(sf::Vector2f(position.x + Size.x / 2, position.y), sf::Vector2f(position.x + Size.x / 2 + Size.x / 4, position.y));

    //add_marker(sf::Vector2f(position.x - Size.x / 2, position.y), "NOT", Size.y / 3, textC, notGates[numarNot].shape.getGlobalBounds());
}

void scena_joc::add_clock(sf::Vector2f Size, sf::Vector2f position, sf::Color color, int timpTrue, int timpFalse)
{
    numarClocks++;

    ceasuri[numarClocks].active=1;

    ceasuri[numarClocks].shape.setSize(Size);
    ceasuri[numarClocks].shape.setOrigin(sf::Vector2f(Size.x / 2, Size.y / 2));
    ceasuri[numarClocks].shape.setPosition(position);
    ceasuri[numarClocks].shape.setFillColor(color);
    ceasuri[numarClocks].semn = false;
    ceasuri[numarClocks].timpTrue = timpTrue;
    ceasuri[numarClocks].timpFalse = timpFalse;
    ceasuri[numarClocks].timpRamas = timpFalse;

    ceasuri[numarClocks].bara.setSize(sf::Vector2f(Size.x/2-Size.x/40,1));
    ceasuri[numarClocks].bara.setPosition(position);

    ceasuri[numarClocks].lineOutput.set_position(sf::Vector2f(position.x + Size.x / 2, position.y), sf::Vector2f(position.x + Size.x / 2 + Size.x / 4, position.y));

    //add_marker(sf::Vector2f(position.x - Size.x / 2, position.y), "CLOCK", Size.y / 4, textC, ceasuri[numarClocks].shape.getGlobalBounds());
}

void scena_joc::add_piesa(string text)
{
    numarPiese++;
    int l=text.length();
    add_marker(sf::Vector2f(0,668),text,100/(l+1),textC,piese[numarPiese].getGlobalBounds());
}


long long scena_joc::update_timp()
{
    long long aux = timp_precedent;
    timp_precedent = globalClock.getElapsedTime().asMicroseconds();
    return globalClock.getElapsedTime().asMicroseconds() - aux;

}

void scena_joc::update_clocks(long long timpTrecut)
{
    for (int i = 1; i <= numarClocks; i++)
    {
        if (ceasuri[i].active==1)
            ceasuri[i].update(timpTrecut);
    }
}

void scena_joc::update_buttons()
{

}

void scena_joc::add_marker(sf::Vector2f position, string text, int characterSize, sf::Color color, sf::FloatRect rect)
{
    numarMarkers++;
    markers[numarMarkers].setCharacterSize(characterSize);
    markers[numarMarkers].setPosition(position);
    markers[numarMarkers].setString(text);
    markers[numarMarkers].setFillColor(color);

    fix_marker(markers[numarMarkers], rect);
}

void scena_joc::fix_marker (sf::Text &text, sf::FloatRect rectBox)
{
    sf::FloatRect rectMarker =text.getGlobalBounds();
    while ((rectBox.left + rectBox.width) - (rectMarker.left + rectMarker.width) > rectMarker.left - rectBox.left)
    {
        text.move(sf::Vector2f(1, 0));
        rectMarker =text.getGlobalBounds();
    }
    while ((rectBox.left + rectBox.width) - (rectMarker.left + rectMarker.width) < rectMarker.left - rectBox.left)
    {
        text.move(sf::Vector2f(-1, 0));
        rectMarker =text.getGlobalBounds();
    }
    while ((rectBox.top + rectBox.height) - (rectMarker.top + rectMarker.height) > rectMarker.top - rectBox.top)
    {
        text.move(sf::Vector2f(0, 1));
        rectMarker =text.getGlobalBounds();
    }
    while ((rectBox.top + rectBox.height) - (rectMarker.top + rectMarker.height) < rectMarker.top - rectBox.top)
    {
        text.move(sf::Vector2f(0, -1));
        rectMarker =text.getGlobalBounds();
    }
}

void scena_joc::setup_playgorund()
{
    playgorund=1;
    add_piesa("SOURCE");
    add_piesa("CONNECTOR");
    add_piesa("AND");
    add_piesa("OR");
    add_piesa("XOR");
    add_piesa("NOT");
    add_piesa("CLOCK");
    piesaSelectata=1;

    ghost.setFillColor(sf::Color::Transparent);
    ghost.setOutlineThickness(2);
    ghost.setOutlineColor(ghostBorderC);
    ghost.setSize(sf::Vector2f(100,100));
    ghost.setOrigin(sf::Vector2f(50,50));
}


void scena_joc::add(int piesa,sf::Vector2f position,sf::Vector2f Size)
{
    //cout << Size.x<<"\n";
    switch(piesa)
    {
    case 1:
        {
            add_source(Size,position,opritC);
            break;
        }
    case 2:
        {
            add_line(position);
            break;
        }
    case 3:
        {
            add_and_gate(Size,position,andC);
            break;
        }
    case 4:
        {
            add_or_gate(Size,position,orC);
            break;
        }
    case 5:
        {
            add_xor_gate(Size,position,orC);
            break;
        }
    case  6:
        {
            add_not_gate(Size,position,notC);
            break;
        }
    case 7:
        {
            add_clock(Size,position,clockC,1000000,1000000);
        }
    }
}

int dist(sf::Vector2f p1,sf::Vector2f p2)
{
    int dx=(p1.x-p2.x)*(p1.x-p2.x);
    int dy=(p1.y-p2.y)*(p1.y-p2.y);
    int distanta=dx+dy;
    return (int)sqrt(distanta);
}
int dist(sf::Vector2f poz,sf::Vector2f p1,sf::Vector2f p2)
{
    int minim=dist(poz,p1);
    int q=dist(poz,p2);
    float md=((float)(p2.y-p1.y))/(p2.x-p1.x);
    float c1=-md*p1.x+p1.y;
    float a1=md;
    float b1=-1;
    float md2=-(1.f/md);
    float c2=-md2*poz.x+poz.y;
    float a2=md2;
    float b2=-1;
    float y=((float)(a2*c1-a1*c2))/(a1*b2-a2*b1);
    float x=-((float)(c1+b1*y))/a1;

    float w=((float)abs(md*poz.x - poz.y - md*p1.x+p1.y))/((float)(sqrt(1+md*md)));
    if (q<minim)
    {
        minim=q;
    }
    sf::Vector2f A=p1;
    sf::Vector2f B=p2;
    if (A.x>B.x)
        swap(A,B);
    if (w<minim&&(x>=A.x&&x<=B.x&&((y>=A.y&&y<=B.y)||(y>=B.y&&y<=A.y))))
    {
        minim=w;
    }
    return minim;
}
void scena_joc::erase(sf::Vector2f position)
{
    int minim=99999;
    for (int i=1; i<=numarAnd; i++)
    {
        if (andGates[i].shape.getGlobalBounds().contains(position)&&andGates[i].active==1)
        {
            //debug(andGates[i],"AND");
            andGates[i].active=0;
            return;
        }
    }
    for (int i=1; i<=numarNot; i++)
    {
        if (notGates[i].shape.getGlobalBounds().contains(position)&&notGates[i].active==1)
        {
            notGates[i].active=0;
            return;
        }
    }
    for (int i=1; i<=numarOr; i++)
    {
        if (orGates[i].shape.getGlobalBounds().contains(position)&&orGates[i].active==1)
        {
            //debug(orGates[i],"OR");
            orGates[i].active=0;
            return;
        }
    }
    for (int i=1; i<=numarXor; i++)
    {
        if (xorGates[i].shape.getGlobalBounds().contains(position)&&xorGates[i].active==1)
        {
            //debug(xorGates[i],"XOR");
            xorGates[i].active=0;
            return;
        }
    }
    for (int i=1; i<=numarClocks; i++)
    {
        if (ceasuri[i].shape.getGlobalBounds().contains(position)&&ceasuri[i].active==1)
        {
            ceasuri[i].active=0;
            return;
        }
    }
    for (int i=1; i<=numarSurse; i++)
    {
        if (sources[i].shape.getGlobalBounds().contains(position)&&sources[i].active==1)
        {
            sources[i].active=0;
            return;
        }
    }
    for (int i=1; i<=numarLines; i++)
    {
        if (lines[i].active==1)
        {
            int d=dist(position,lines[i].shape[0].position,lines[i].shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
        }
    }
    if (minim>20)
    {
        return;
    }
    for (int i=1; i<=numarLines; i++)
    {
        if (lines[i].active==1)
        {
            int d=dist(position,lines[i].shape[0].position,lines[i].shape[1].position);
            if (d==minim)
            {
                //cout << "linie care se sterge: " << i <<"\n";
                int aux=lines[i].indiceConnector;
                lines[i].set_connector(0);
                delete_connector(aux,i);
                lines[i].active=0;
                return;
            }
        }
    }

}



void scena_joc::connect(int indice,bool apply)
{
    int minim=99999;
    sf::Vector2f poz=lines[indice].shape[0].position;
    sf::Vector2f otherPoz=lines[indice].shape[1].position;
    if (poz!=otherPoz)
        swap(poz,otherPoz);
    for (int i=1; i<=numarAnd; i++)
    {
        if (andGates[i].active==1)
        {
            int d=dist(poz,andGates[i].lineInput1.shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
            d=dist(poz,andGates[i].lineInput2.shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
            d=dist(poz,andGates[i].lineOutput.shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
        }
    }
    for (int i=1; i<=numarNot; i++)
    {
        if (notGates[i].active==1)
        {
            int d=dist(poz,notGates[i].lineInput.shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
            d=dist(poz,notGates[i].lineOutput.shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
        }
    }
    for (int i=1; i<=numarOr; i++)
    {
        if (orGates[i].active)
        {
            int d=dist(poz,orGates[i].lineInput1.shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
            d=dist(poz,orGates[i].lineInput2.shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
            d=dist(poz,orGates[i].lineOutput.shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
        }
    }
    for (int i=1; i<=numarXor; i++)
    {
        if (xorGates[i].active)
        {
            int d=dist(poz,xorGates[i].lineInput1.shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
            d=dist(poz,xorGates[i].lineInput2.shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
            d=dist(poz,xorGates[i].lineOutput.shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
        }
    }
    for (int i=1; i<=numarClocks; i++)
    {
        if (ceasuri[numarClocks].active)
        {
            int d=dist(poz,ceasuri[i].lineOutput.shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
        }
    }
    for (int i=1; i<=numarSurse; i++)
    {
        if (sources[i].active==1)
        {
            int d=dist(poz,sources[i].lineOutput.shape[1].position);
            if (d<minim)
            {
                minim=d;
            }
        }
    }

    if (minim>50)
    {
        //cout << "nu s-a gasit\n";
        return;
    }

    for (int i=1; i<=numarAnd; i++)
    {
        if (andGates[i].active)
        {
            int d=dist(poz,andGates[i].lineInput1.shape[1].position);
            if (d==minim)
            {
                if (apply==1)
                {
                    if (andGates[i].lineInput1.indiceConnector==0)
                    {
                        andGates[i].indiceInput1=indice;
                        andGates[i].lineInput1.set_connector(lines[indice].indiceConnector);
                        andGates[i].input1=&connectors[lines[indice].indiceConnector];
                    }
                    else
                    {
                        andGates[i].indiceInput1=indice;
                        andGates[i].lineInput1.set_connector(lines[indice].indiceConnector);
                        andGates[i].input1=&connectors[lines[indice].indiceConnector];
                        //lines[indice].set_connector(andGates[i].lineInput1.indiceConnector);
                    }
                }
                sf::Vector2f pozitieNoua=andGates[i].lineInput1.shape[1].position;
                if (apply==1)
                {
                    lines[indice].set_position(pozitieNoua,otherPoz);
                }
                else
                {
                    lines[indice].set_position(otherPoz,pozitieNoua);
                }
                return;
            }
            d=dist(poz,andGates[i].lineInput2.shape[1].position);
            if (d==minim)
            {
                if (apply==1)
                {
                    if (andGates[i].lineInput2.indiceConnector==0)
                    {
                        andGates[i].indiceInput2=indice;
                        andGates[i].lineInput2.set_connector(lines[indice].indiceConnector);
                        andGates[i].input2=&connectors[lines[indice].indiceConnector];
                    }
                    else
                    {
                        andGates[i].indiceInput2=indice;
                        andGates[i].lineInput2.set_connector(lines[indice].indiceConnector);
                        andGates[i].input2=&connectors[lines[indice].indiceConnector];
                        //lines[indice].set_connector(andGates[i].lineInput2.indiceConnector);
                    }
                }
                sf::Vector2f pozitieNoua=andGates[i].lineInput2.shape[1].position;
                if (apply==1)
                {
                    lines[indice].set_position(pozitieNoua,otherPoz);
                }
                else
                {
                    lines[indice].set_position(otherPoz,pozitieNoua);
                }
                return;
            }
            d=dist(poz,andGates[i].lineOutput.shape[1].position);
            if (d==minim)
            {
                if (apply==1)
                {
                    if (andGates[i].lineOutput.indiceConnector==0)
                    {
                        andGates[i].lineOutput.set_connector(lines[indice].indiceConnector);
                        andGates[i].output=&connectors[lines[indice].indiceConnector];
                    }
                    else
                    {
                        fix(indice,andGates[i].lineOutput.indiceConnector);
                        connectors[lines[indice].indiceConnector].alive=0;
                        lines[indice].set_connector(andGates[i].lineOutput.indiceConnector);

                    }
                }
                sf::Vector2f pozitieNoua=andGates[i].lineOutput.shape[1].position;
                if (apply==1)
                {
                    lines[indice].set_position(pozitieNoua,otherPoz);
                }
                else
                {
                    lines[indice].set_position(otherPoz,pozitieNoua);
                }
                return;
            }
        }
    }
    for (int i=1; i<=numarNot; i++)
    {
        if (notGates[i].active)
        {
            int d=dist(poz,notGates[i].lineInput.shape[1].position);
            if (d==minim)
            {
                if (apply==1)
                {
                    if (notGates[i].input==NULL)
                    {
                        notGates[i].indiceInput=indice;
                        notGates[i].input=&connectors[lines[indice].indiceConnector];
                        notGates[i].lineInput.set_connector(lines[indice].indiceConnector);
                    }
                    else
                    {
                        notGates[i].indiceInput=indice;
                        notGates[i].input=&connectors[lines[indice].indiceConnector];
                        notGates[i].lineInput.set_connector(lines[indice].indiceConnector);
                        //lines[indice].set_connector(notGates[i].lineInput.indiceConnector);
                    }
                }
                sf::Vector2f pozitieNoua=notGates[i].lineInput.shape[1].position;
                if (apply==1)
                {
                    lines[indice].set_position(pozitieNoua,otherPoz);
                }
                else
                {
                    lines[indice].set_position(otherPoz,pozitieNoua);
                }
                return;
            }
            d=dist(poz,notGates[i].lineOutput.shape[1].position);
            if (d==minim)
            {
                if (apply==1)
                {
                    if (notGates[i].output==NULL)
                    {
                        notGates[i].output=&connectors[lines[indice].indiceConnector];
                        notGates[i].lineOutput.set_connector(lines[indice].indiceConnector);
                    }
                    else
                    {
                        fix(indice,notGates[i].lineOutput.indiceConnector);
                        connectors[lines[indice].indiceConnector].alive=0;
                        lines[indice].set_connector(notGates[i].lineOutput.indiceConnector);
                    }
                }
                sf::Vector2f pozitieNoua=notGates[i].lineOutput.shape[1].position;
                if (apply==1)
                {
                    lines[indice].set_position(pozitieNoua,otherPoz);
                }
                else
                {
                    lines[indice].set_position(otherPoz,pozitieNoua);
                }
                return;
            }
        }
    }
    for (int i=1; i<=numarOr; i++)
    {
        if (orGates[i].active)
        {
            int d=dist(poz,orGates[i].lineInput1.shape[1].position);
            if (d==minim)
            {
                if (apply==1)
                {
                    if (orGates[i].lineInput1.indiceConnector==0)
                    {
                        orGates[i].indiceInput1=indice;
                        orGates[i].lineInput1.set_connector(lines[indice].indiceConnector);
                        orGates[i].input1=&connectors[lines[indice].indiceConnector];
                    }
                    else
                    {
                        orGates[i].indiceInput1=indice;
                        orGates[i].lineInput1.set_connector(lines[indice].indiceConnector);
                        orGates[i].input1=&connectors[lines[indice].indiceConnector];
                        //lines[indice].set_connector(orGates[i].lineInput1.indiceConnector);
                    }
                }
                sf::Vector2f pozitieNoua=orGates[i].lineInput1.shape[1].position;
                if (apply==1)
                {
                    lines[indice].set_position(pozitieNoua,otherPoz);
                }
                else
                {
                    lines[indice].set_position(otherPoz,pozitieNoua);
                }
                return;
            }
            d=dist(poz,orGates[i].lineInput2.shape[1].position);
            if (d==minim)
            {
                if (apply==1)
                {
                    if (orGates[i].lineInput2.indiceConnector==0)
                    {
                        orGates[i].indiceInput2=indice;
                        orGates[i].lineInput2.set_connector(lines[indice].indiceConnector);
                        orGates[i].input2=&connectors[lines[indice].indiceConnector];
                    }
                    else
                    {
                        orGates[i].indiceInput2=indice;
                        orGates[i].lineInput2.set_connector(lines[indice].indiceConnector);
                        orGates[i].input2=&connectors[lines[indice].indiceConnector];
                        //lines[indice].set_connector(orGates[i].lineInput2.indiceConnector);
                    }
                }
                sf::Vector2f pozitieNoua=orGates[i].lineInput2.shape[1].position;
                if (apply==1)
                {
                    lines[indice].set_position(pozitieNoua,otherPoz);
                }
                else
                {
                    lines[indice].set_position(otherPoz,pozitieNoua);
                }
                return;
            }
            d=dist(poz,orGates[i].lineOutput.shape[1].position);
            if (d==minim)
            {
                if (apply==1)
                {
                    if (orGates[i].lineOutput.indiceConnector==0)
                    {
                        orGates[i].lineOutput.set_connector(lines[indice].indiceConnector);
                        orGates[i].output=&connectors[lines[indice].indiceConnector];
                    }
                    else
                    {
                        fix(indice,orGates[i].lineOutput.indiceConnector);
                        connectors[lines[indice].indiceConnector].alive=0;
                        lines[indice].set_connector(orGates[i].lineOutput.indiceConnector);
                    }
                }
                sf::Vector2f pozitieNoua=orGates[i].lineOutput.shape[1].position;
                if (apply==1)
                {
                    lines[indice].set_position(pozitieNoua,otherPoz);
                }
                else
                {
                    lines[indice].set_position(otherPoz,pozitieNoua);
                }
                return;
            }
        }
    }
    for (int i=1; i<=numarXor; i++)
    {
        if (xorGates[i].active)
        {
            int d=dist(poz,xorGates[i].lineInput1.shape[1].position);
            if (d==minim)
            {
                if (apply==1)
                {
                    if (xorGates[i].lineInput1.indiceConnector==0)
                    {
                        xorGates[i].indiceInput1=indice;
                        xorGates[i].lineInput1.set_connector(lines[indice].indiceConnector);
                        xorGates[i].input1=&connectors[lines[indice].indiceConnector];
                    }
                    else
                    {
                        xorGates[i].indiceInput1=indice;
                        xorGates[i].lineInput1.set_connector(lines[indice].indiceConnector);
                        xorGates[i].input1=&connectors[lines[indice].indiceConnector];
                        //lines[indice].set_connector(xorGates[i].lineInput1.indiceConnector);
                    }
                }
                sf::Vector2f pozitieNoua=xorGates[i].lineInput1.shape[1].position;
                if (apply==1)
                {
                    lines[indice].set_position(pozitieNoua,otherPoz);
                }
                else
                {
                    lines[indice].set_position(otherPoz,pozitieNoua);
                }
                return;
            }
            d=dist(poz,xorGates[i].lineInput2.shape[1].position);
            if (d==minim)
            {
                if (apply==1)
                {
                    if (xorGates[i].lineInput2.indiceConnector==0)
                    {
                        xorGates[i].indiceInput2=indice;
                        xorGates[i].lineInput2.set_connector(lines[indice].indiceConnector);
                        xorGates[i].input2=&connectors[lines[indice].indiceConnector];
                    }
                    else
                    {
                        xorGates[i].indiceInput2=indice;
                        xorGates[i].lineInput2.set_connector(lines[indice].indiceConnector);
                        xorGates[i].input2=&connectors[lines[indice].indiceConnector];
                        //lines[indice].set_connector(xorGates[i].lineInput2.indiceConnector);
                    }
                }
                sf::Vector2f pozitieNoua=xorGates[i].lineInput2.shape[1].position;
                if (apply==1)
                {
                    lines[indice].set_position(pozitieNoua,otherPoz);
                }
                else
                {
                    lines[indice].set_position(otherPoz,pozitieNoua);
                }
                return;
            }
            d=dist(poz,xorGates[i].lineOutput.shape[1].position);
            if (d==minim)
            {
                if (apply==1)
                {
                    if (xorGates[i].lineOutput.indiceConnector==0)
                    {
                        xorGates[i].lineOutput.set_connector(lines[indice].indiceConnector);
                        xorGates[i].output=&connectors[lines[indice].indiceConnector];
                    }
                    else
                    {
                        fix(indice,xorGates[i].lineOutput.indiceConnector);
                        connectors[lines[indice].indiceConnector].alive=0;
                        lines[indice].set_connector(xorGates[i].lineOutput.indiceConnector);
                    }
                }
                sf::Vector2f pozitieNoua=xorGates[i].lineOutput.shape[1].position;
                if (apply==1)
                {
                    lines[indice].set_position(pozitieNoua,otherPoz);
                }
                else
                {
                    lines[indice].set_position(otherPoz,pozitieNoua);
                }
                return;
            }
        }
    }
    for (int i=1; i<=numarClocks; i++)
    {
        if (ceasuri[i].active)
        {
            int d=dist(poz,ceasuri[i].lineOutput.shape[1].position);
            if (d==minim)
            {
                if (apply==1)
                {
                    if (ceasuri[i].outputConnector==NULL)
                    {
                        ceasuri[i].outputConnector=&connectors[lines[indice].indiceConnector];
                        ceasuri[i].lineOutput.set_connector(lines[indice].indiceConnector);
                    }
                    else
                    {
                        fix(indice,ceasuri[i].lineOutput.indiceConnector);
                        connectors[lines[indice].indiceConnector].alive=0;
                        lines[indice].set_connector(ceasuri[i].lineOutput.indiceConnector);
                    }
                }
                sf::Vector2f pozitieNoua=ceasuri[i].lineOutput.shape[1].position;
                if (apply==1)
                {
                    lines[indice].set_position(pozitieNoua,otherPoz);
                }
                else
                {
                    lines[indice].set_position(otherPoz,pozitieNoua);
                }
                return;
            }
        }
    }
    for (int i=1; i<=numarSurse; i++)
    {
        if (sources[i].active==1)
        {
            int d=dist(poz,sources[i].lineOutput.shape[1].position);
            if (d==minim)
            {
                if (apply==1)
                {
                    if (sources[i].output==NULL)
                    {
                        sources[i].output=&connectors[lines[indice].indiceConnector];
                        sources[i].lineOutput.set_connector(lines[indice].indiceConnector);
                    }
                    else
                    {
                        fix(indice,sources[i].lineOutput.indiceConnector);
                        connectors[lines[indice].indiceConnector].alive=0;
                        lines[indice].set_connector(sources[i].lineOutput.indiceConnector);
                    }
                }
                sf::Vector2f pozitieNoua=sources[i].lineOutput.shape[1].position;
                if (apply==1)
                {
                    lines[indice].set_position(pozitieNoua,otherPoz);
                }
                else
                {
                    lines[indice].set_position(otherPoz,pozitieNoua);
                }
            }
        }
    }
}

void scena_joc::delete_connector(int indice,int indice_linie)
{
    bool ok=0;
    //cout << indice <<endl;
    int nr=0;
    for (int j=1; j<=numarLines; j++)
    {
        if (lines[j].indiceConnector==indice)
        {
            nr++;
        }
    }

    for (int i=1; i<=numarAnd; i++)
    {
        if (andGates[i].output==&connectors[indice])
        {
            ok=1;
            if (nr==0)
            {
                //cout << "\nda...";
                andGates[i].output=NULL;
                andGates[i].lineOutput.set_connector(0);
                connectors[indice].alive=0;
            }
        }
        if (andGates[i].indiceInput1==indice_linie)
        {
            ok=1;
            andGates[i].input1=NULL;
            andGates[i].lineInput1.set_connector(0);
            andGates[i].indiceInput1=0;
            if (nr==0)
                connectors[indice].alive=0;
        }
        if (andGates[i].indiceInput2==indice_linie)
        {
            ok=1;
            andGates[i].input2=NULL;
            andGates[i].lineInput2.set_connector(0);
            andGates[i].indiceInput2=0;
            if (nr==0)
                connectors[indice].alive=0;
        }
    }
    for (int i=1; i<=numarOr; i++)
    {
        if (orGates[i].output==&connectors[indice])
        {
            ok=1;
            if (nr==0)
            {
                orGates[i].output=NULL;
                orGates[i].lineOutput.set_connector(0);
                connectors[indice].alive=0;
            }
        }
        if (orGates[i].indiceInput1==indice_linie)
        {
            ok=1;
            orGates[i].input1=NULL;
            orGates[i].lineInput1.set_connector(0);
            orGates[i].indiceInput1=0;
            if (nr==0)
                connectors[indice].alive=0;
        }
        if (orGates[i].indiceInput2==indice_linie)
        {
            ok=1;
            orGates[i].input2=NULL;
            orGates[i].lineInput2.set_connector(0);
            orGates[i].indiceInput2=0;
            if (nr==0)
                connectors[indice].alive=0;
        }
    }
    for (int i=1; i<=numarXor; i++)
    {
        if (xorGates[i].output==&connectors[indice])
        {
            ok=1;
            if (nr==0)
            {
                xorGates[i].output=NULL;
                xorGates[i].lineOutput.set_connector(0);
                connectors[indice].alive=0;
            }
        }
        if (xorGates[i].indiceInput1==indice_linie)
        {
            ok=1;
            xorGates[i].input1=NULL;
            xorGates[i].lineInput1.set_connector(0);
            xorGates[i].indiceInput1=0;
            if (nr==0)
                connectors[indice].alive=0;
        }
        if (xorGates[i].indiceInput2==indice_linie)
        {
            ok=1;
            xorGates[i].input2=NULL;
            xorGates[i].lineInput2.set_connector(0);
            xorGates[i].indiceInput2=0;
            if (nr==0)
                connectors[indice].alive=0;
        }
    }
    for (int i=1; i<=numarNot; i++)
    {
        if (notGates[i].output==&connectors[indice])
        {
            ok=1;
            if (nr==0)
            {
                notGates[i].output=NULL;
                notGates[i].lineOutput.set_connector(0);
                connectors[indice].alive=0;
            }
        }
        if (notGates[i].indiceInput==indice_linie)
        {
            ok=1;
            notGates[i].input=NULL;
            notGates[i].lineInput.set_connector(0);
            notGates[i].indiceInput=0;
            if (nr==0)
                connectors[indice].alive=0;
        }
    }
    for (int i=1; i<=numarClocks; i++)
    {
        if (ceasuri[i].outputConnector==&connectors[indice])
        {
            ok=1;
            if (nr==0)
            {
                ceasuri[i].outputConnector=NULL;
                ceasuri[i].lineOutput.set_connector(0);
                connectors[indice].alive=0;
            }
        }
    }
    for (int i=1; i<=numarSurse; i++)
    {
        if (sources[i].output==&connectors[indice])
        {
            ok=1;
            if (nr==0)
            {
                sources[i].output=NULL;
                sources[i].lineOutput.set_connector(0);
                connectors[indice].alive=0;
            }
        }
    }
    if (ok==0)
    {
        connectors[indice].alive=0;
    }
}


template <typename T>
void scena_joc::debug(T poarta,string nume)
{
    cout << "\n";
    cout << "Poarta " << nume << "\n";
    cout << "1: "<<poarta.indiceInput1 << "\n";
    cout << "2: "<<poarta.indiceInput2 << "\n";
};

void scena_joc::add_source(sf::Vector2f Size, sf::Vector2f position,sf::Color color)
{
    numarSurse++;
    sources[numarSurse].active=1;
    sources[numarSurse].shape.setSize(Size);
    sources[numarSurse].shape.setOrigin(sf::Vector2f(Size.x/2,Size.y/2));
    sources[numarSurse].shape.setPosition(position);
    sources[numarSurse].lineOutput.set_position(sf::Vector2f(position.x+Size.x/2,position.y),sf::Vector2f(position.x+Size.x/2+Size.x/4,position.y));
    sources[numarSurse].set_state(0);
    sources[numarSurse].lineOutput.active=1;
    sources[numarSurse].lineOutput.indiceConnector=0;
}

void scena_joc::update_surse()
{
    for (int i=1; i<=numarSurse; i++)
    {
        sources[i].run();
    }
}

void scena_joc::fix(int indiceLinie,int indiceConector)
{
    for (int i=1; i<=numarAnd; i++)
    {
        if (andGates[i].active==1)
        {
            if (andGates[i].indiceInput1==indiceLinie)
            {
                andGates[i].lineInput1.set_connector(indiceConector);
                andGates[i].input1=&connectors[indiceConector];
            }
            if (andGates[i].indiceInput2==indiceLinie)
            {
                andGates[i].lineInput2.set_connector(indiceConector);
                andGates[i].input2=&connectors[indiceConector];
            }
        }
    }
    for (int i=1; i<=numarNot; i++)
    {
        if (notGates[i].active==1)
        {
            if (notGates[i].indiceInput==indiceLinie)
            {
                notGates[i].lineInput.set_connector(indiceConector);
                notGates[i].input=&connectors[indiceConector];
            }
        }
    }
    for (int i=1; i<=numarOr; i++)
    {
        if (orGates[i].active)
        {
            if (orGates[i].indiceInput1==indiceLinie)
            {
                orGates[i].lineInput1.set_connector(indiceConector);
                orGates[i].input1=&connectors[indiceConector];
            }
            if (orGates[i].indiceInput2==indiceLinie)
            {
                orGates[i].lineInput2.set_connector(indiceConector);
                orGates[i].input2=&connectors[indiceConector];
            }
        }
    }
    for (int i=1; i<=numarXor; i++)
    {
        if (xorGates[i].active)
        {
            if (xorGates[i].indiceInput1==indiceLinie)
            {
                xorGates[i].lineInput1.set_connector(indiceConector);
                xorGates[i].input1=&connectors[indiceConector];
            }
            if (xorGates[i].indiceInput2==indiceLinie)
            {
                xorGates[i].lineInput2.set_connector(indiceConector);
                xorGates[i].input2=&connectors[indiceConector];
            }
        }
    }
}

void scena_joc::save(string name)
{
    FILE* saveFile;
    string file="saves/saves.txt";
    //cout << name<<endl;
    saveFile=fopen(file.data(),"a");

    fprintf(saveFile,"\nN:%s\n",name.data());
    for (int i=1; i<=numarAnd; i++)
    {
        if (andGates[i].active==1)
        {
            fprintf(saveFile,"1 %d %d %d %d %d %d %d %d\n",
                    (int)andGates[i].shape.getSize().x,(int)andGates[i].shape.getSize().y,
                    (int)andGates[i].shape.getPosition().x,(int)andGates[i].shape.getPosition().y,
                    (int)andGates[i].shape.getFillColor().r,(int)andGates[i].shape.getFillColor().g,(int)andGates[i].shape.getFillColor().b,(int)andGates[i].shape.getFillColor().a);
        }
    }
    for (int i=1; i<=numarOr; i++)
    {
        if (orGates[i].active==1)
        {
            fprintf(saveFile,"2 %d %d %d %d %d %d %d %d\n",
                    (int)orGates[i].shape.getSize().x,(int)orGates[i].shape.getSize().y,
                    (int)orGates[i].shape.getPosition().x,(int)orGates[i].shape.getPosition().y,
                    (int)orGates[i].shape.getFillColor().r,(int)orGates[i].shape.getFillColor().g,(int)orGates[i].shape.getFillColor().b,(int)orGates[i].shape.getFillColor().a);
        }
    }
    for (int i=1; i<=numarXor; i++)
    {
        if (xorGates[i].active==1)
        {
            fprintf(saveFile,"3 %d %d %d %d %d %d %d %d\n",
                    (int)xorGates[i].shape.getSize().x,(int)xorGates[i].shape.getSize().y,
                    (int)xorGates[i].shape.getPosition().x,(int)xorGates[i].shape.getPosition().y,
                    (int)xorGates[i].shape.getFillColor().r,(int)xorGates[i].shape.getFillColor().g,(int)xorGates[i].shape.getFillColor().b,(int)xorGates[i].shape.getFillColor().a);
        }
    }
    for (int i=1; i<=numarSurse; i++)
    {
        if (sources[i].active==1)
        {
            fprintf(saveFile,"4 %d %d %d %d  %d %d %d %d\n",
                    (int)sources[i].shape.getSize().x,(int)sources[i].shape.getSize().y,
                    (int)sources[i].shape.getPosition().x,(int)sources[i].shape.getPosition().y,
                    (int)sources[i].shape.getFillColor().r,(int)sources[i].shape.getFillColor().g,(int)sources[i].shape.getFillColor().b,(int)sources[i].shape.getFillColor().a);
        }
    }
    for (int i=1; i<=numarClocks; i++)
    {
        if (ceasuri[i].active==1)
        {
            fprintf(saveFile,"5 %d %d %d %d %d %d %d %d %d %d\n",
                    (int)ceasuri[i].shape.getSize().x,(int)ceasuri[i].shape.getSize().y,
                    (int)ceasuri[i].shape.getPosition().x,(int)ceasuri[i].shape.getPosition().y,
                    (int)ceasuri[i].shape.getFillColor().r,(int)ceasuri[i].shape.getFillColor().g,(int)ceasuri[i].shape.getFillColor().b,(int)ceasuri[i].shape.getFillColor().a,
                    (int)ceasuri[i].timpTrue,(int)ceasuri[i].timpFalse);
        }
    }
    for (int i=1; i<=numarNot; i++)
    {
        if (notGates[i].active==1)
        {
            fprintf(saveFile,"6 %d %d %d %d %d %d %d %d\n",
                    (int)notGates[i].shape.getSize().x,(int)notGates[i].shape.getSize().y,
                    (int)notGates[i].shape.getPosition().x,(int)notGates[i].shape.getPosition().y,
                    (int)notGates[i].shape.getFillColor().r,(int)notGates[i].shape.getFillColor().g,(int)notGates[i].shape.getFillColor().b,(int)notGates[i].shape.getFillColor().a);
        }
    }

    for (int i=1; i<=numarLines; i++)
    {
        if (lines[i].active==1)
        {
            fprintf(saveFile, "7 %d %d %d %d\n",
                    (int)lines[i].shape[0].position.x,(int)lines[i].shape[0].position.y,
                    (int)lines[i].shape[1].position.x,(int)lines[i].shape[1].position.y);
        }
    }
    fclose(saveFile);


}

void scena_joc::add_line(sf::Vector2f position)
{
    if (setLine==0)
    {
        setLine=1;
        numarLines++;
        numarConectoare++;
        int aux=numarConectoare;
        lines[numarLines].set_position(position,position);
        lines[numarLines].set_connector(numarConectoare);
        lines[numarLines].active=1;
        connect(numarLines,1);
        connectors[numarConectoare].alive=1;
        if (aux!=lines[numarLines].indiceConnector)
        {
            connectors[numarConectoare].alive=0;
            numarConectoare--;
        }
    }
    else
    {
        setLine=0;
        lines[numarLines].set_position(lines[numarLines].shape[0].position,position);
        connect(numarLines,1);
    }
}

void scena_joc::setup_special(string preset)
{
    //cout << preset <<endl;
    playgorund=0;
    ifstream fin("saves/saves.txt");
    char text[300];
    while (fin.peek()!=EOF)
    {
        fin.getline(text,300);
        if (text[0]=='N'&&text[1]==':')
        {
            strcpy(text,text+2);
            if (strcmp(preset.data(),text)==0)
            {
                //fin.getline(text,300);
                bool ok=1;
                while (ok==1&&fin.peek()!=EOF)
                {
                    fin.getline(text,300);
                    //cout << text <<endl;
                    if (text[0]=='N'&&text[1]==':')
                    {
                        ok=0;
                        break;
                    }
                    char *p=strtok(text," ");
                    int var[20];
                    int numar_variabile=0;
                    int numar=0;
                    while (p)
                    {
                        numar=0;
                        for (int i=0; p[i]!=NULL; i++)
                        {
                            numar=numar*10+p[i]-'0';
                        }
                        //cout << numar <<endl;
                        var[++numar_variabile]=numar;
                        p=strtok(NULL," ");
                    }
                    if (numar_variabile!=0)
                    {
                        switch(var[1])
                        {
                        case 1:
                            {
                                add_and_gate(sf::Vector2f(var[2],var[3]),sf::Vector2f(var[4],var[5]),sf::Color(var[6],var[7],var[8],var[9]));
                                break;
                            }
                        case 2:
                            {
                                add_or_gate(sf::Vector2f(var[2],var[3]),sf::Vector2f(var[4],var[5]),sf::Color(var[6],var[7],var[8],var[9]));
                                break;
                            }
                        case 3:
                            {
                                add_xor_gate(sf::Vector2f(var[2],var[3]),sf::Vector2f(var[4],var[5]),sf::Color(var[6],var[7],var[8],var[9]));
                                break;
                            }
                        case 4:
                            {
                                add_source(sf::Vector2f(var[2],var[3]),sf::Vector2f(var[4],var[5]),sf::Color(var[6],var[7],var[8],var[9]));
                                break;
                            }
                        case 5:
                            {
                                add_clock(sf::Vector2f(var[2],var[3]),sf::Vector2f(var[4],var[5]),sf::Color(var[6],var[7],var[8],var[9]),var[10],var[11]);
                                break;
                            }
                        case 6:
                            {
                                add_not_gate(sf::Vector2f(var[2],var[3]),sf::Vector2f(var[4],var[5]),sf::Color(var[6],var[7],var[8],var[9]));
                                break;
                            }
                        case 7:
                            {
                                add_line(sf::Vector2f(var[2],var[3]));
                                add_line(sf::Vector2f(var[4],var[5]));
                                break;
                            }
                        }
                    }
                }
                break;
            }
        }
    }
    fin.close();
}

void scena_joc::saving_screen()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type==sf::Event::Closed)
            gameOn=0;
        if (event.type==sf::Event::KeyReleased)
        {
            if (event.key.code==sf::Keyboard::Escape)
            {
                saving=0;
            }
            if (event.key.code==sf::Keyboard::Enter&&preset_name.size()>0)
            {
                ifstream fin ("saves/saves.txt");
                char linie[300];
                bool ok=1;
                while (fin.peek()!=EOF&&ok==1)
                {
                    fin.getline(linie,300);
                    if (linie[0]=='N'&&linie[1]==':')
                    {
                        strcpy(linie,linie+2);
                        if (strcmp(linie,preset_name.data())==0)
                            ok=0;
                    }
                }
                fin.close();
                if (ok==1)
                {
                    save(preset_name);
                    saving=0;
                }
            }
            if (event.key.code>=sf::Keyboard::A&&event.key.code<=sf::Keyboard::Z)
            {
                preset_name+='A'+event.key.code-sf::Keyboard::A;
            }
            if (event.key.code>=sf::Keyboard::Num0&&event.key.code<=sf::Keyboard::Num9)
            {
                preset_name+='0'+event.key.code-sf::Keyboard::Num0;
            }
            if (event.key.code>=sf::Keyboard::Numpad0&&event.key.code<=sf::Keyboard::Numpad9)
            {
                preset_name+='0'+event.key.code-sf::Keyboard::Numpad0;
            }
            if (event.key.code==sf::Keyboard::Space)
            {
                preset_name+=' ';
            }
            if (event.key.code==sf::Keyboard::Backspace&&preset_name.size()>0)
            {
                preset_name.erase(preset_name.size()-1,preset_name.size());
            }
        }
    }

}
