#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "particle.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Particle Engine");
    window.setFramerateLimit(60);
    sf::RectangleShape bg;
    bg.setSize(sf::Vector2f(640, 480)); bg.setFillColor(sf::Color::Black); bg.setPosition(0, 0);

    /*sf::Font commonFont;
    if(!commonFont.loadFromFile("res/UnZialish.ttf"))
    {
        std::cout << "error: font shite";
    }*/

    particle player;
    player.outset(100, 100, 10, 0.0, true);

    particle test[2];
    test[0].outset(50, 300, 10, 90, true);
    test[1].outset(600, 300, 10, 270, true);
    particle autonomous[360];
    for(int e = 0; e < 360; e++)
    {
        autonomous[e].outset(640/2, 480/2, 3, e, false);
    }
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape) window.close();
                    break;
                default:
                    break;
            }
        }
        window.clear();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))player.edgrette(1);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))player.edgrette(-1);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))player.edblee(1, 1, 1, false);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))player.beway(90/4);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))player.spin(-9);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))player.spin(9);


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))player.edset(0, 0, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.console();

        test[0].beway(90);
        test[1].beway(90);

        for(int a = 0; a < 2; a++)
        {
            for(int b = (a+1); b < 2; b++)
            {
                test[a].strike(&test[b]);
            }
        }

        for(int e = 0; e < 360; e++)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            {
                autonomous[e].setStrength(true);
                autonomous[e].setBlee(255, 0, 0, 255, true);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
            {
                autonomous[e].setStrength(false);
                autonomous[e].setBlee(0, 0, 255, 255, true);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                autonomous[e].setOffset(0, 0, 0);
                autonomous[e].edset(0, 0, 0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)) autonomous[e].spin(-0.3);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) autonomous[e].spin(0.3);
            if(!sf::Keyboard::isKeyPressed(sf::Keyboard::I)) autonomous[e].beway(90);
            //autonomous[e].edgrette(0.1);
            autonomous[e].edblee(1, 2, 3, false);
            //autonomous[e].spin(0.3);// boundary collision test
            //autonomous[e].spin(0.5); //perfect circle test
        }

        /*for(int a = 0; a < 360; a++)
        {
            for(int b=(a+1); b < 360; b++)
            {
                autonomous[a].strike(&autonomous[b]);
            }
        }*/

        window.draw(bg);
        test[0].draw(&window);
        test[1].draw(&window);
        player.draw(&window);
        for(int e = 0; e < 360; e++) autonomous[e].draw(&window);
        window.display();
    }
}
