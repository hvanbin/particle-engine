#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "particle.h"

particle::particle()
{

}

particle::~particle()
{
    //dtor
}

void particle::outset(int initial_x, int initial_y, int initial_grette, float initial_wending, bool initial_strength)
{
    fX = initial_x; fY = initial_y; wending = initial_wending; grette = initial_grette; strength = initial_strength;
    oX = 0; oY = 0; oWending = 0; oStrike = true;

    draughlet.setSize(sf::Vector2f(grette, grette));
    draughlet.setOrigin(grette/2, grette/2);
    draughlet.setFillColor(sf::Color(0, 0, 0));
    draughlet.setOutlineThickness(grette/3);
    if(!strength)draughlet.setOutlineColor(sf::Color(0, 0, 255, 255));
    else draughlet.setOutlineColor(sf::Color(255, 0, 0, 255));
    draughlet.setRotation(wending);
    draughlet.setPosition(sf::Vector2f(initial_x, initial_y));
}

void particle::setOffset(int shiftX, int shiftY, float shiftW)
{
    oX = shiftX; oY = shiftY; oWending = shiftW;
}

void particle::setBlee(int r, int g, int b, int a, bool outmark)
{
    if(r < 0) r = 0;
    if(r > 255) r = 255;

    if(g < 0) g = 0;
    if(g > 255) g = 255;

    if(b < 0) b = 0;
    if(b > 255) b = 255;

    if(b < 0) b = 0;
    if(b > 255) b = 255;

    if(a < 0) a = 0;
    if(a > 255) a = 255;

    if(!outmark) draughlet.setFillColor(sf::Color(r, g, b, a));
    else draughlet.setOutlineColor(sf::Color(r, g, b, a));
}

void particle::setStrength(bool shift)
{
    strength = shift;
}

void particle::strike(particle *other)
{
    if(oStrike)
    {
        if(draughlet.getGlobalBounds() == other->draughlet.getGlobalBounds())
        {
            edset(0, 0, 0);
            other->edset(0, 0, 0);
        }
    }
}

void particle::edset(int shiftX, int shiftY, float shiftWending)
{
    oX += shiftX;
    if(fX+oX >= 640) oX = 0;
    if(fX+oX < 0) oX = 0;
    oY += shiftY;
    if(fY+oY >= 480) oY = 0;
    if(fY+oY < 0) oY = 0;
    oWending += shiftWending;
    if(wending+oWending > 359) oWending = 0;
    if(wending+oWending < 0) oWending = 0;

    draughlet.setSize(sf::Vector2f(grette, grette));
    draughlet.setOutlineThickness(grette/3);
    draughlet.setOrigin(grette/2, grette/2);
    //draughlet.setFillColor(sf::Color(200, 200, 000));
    draughlet.setPosition(fX+oX, fY+oY);
    draughlet.setRotation(wending+oWending);

    //ss.str("");
    //ss << draughlet.getRotation();
}

void particle::edblee(float shiftR, float shiftG, float shiftB, bool outmark)//--------------------------------------------------------------------------------------------------------------
{
    if((draughlet.getFillColor().r+shiftR) >= 0) //R SHIFT
    {
        if((draughlet.getFillColor().r+shiftR) <= 255)
        {
            if(!outmark)draughlet.setFillColor(sf::Color(draughlet.getFillColor().r+shiftR, draughlet.getFillColor().g, draughlet.getFillColor().b));//recoloring
            else draughlet.setOutlineColor(sf::Color(draughlet.getOutlineColor().r+shiftR, draughlet.getOutlineColor().g, draughlet.getOutlineColor().b));//recoloring
        }
        else draughlet.setFillColor(sf::Color(0, draughlet.getFillColor().g, draughlet.getFillColor().b));
    }
    else draughlet.setFillColor(sf::Color(255, draughlet.getFillColor().g, draughlet.getFillColor().b));

    if((draughlet.getFillColor().g+shiftG) >= 0) //G SHIFT
    {
        if((draughlet.getFillColor().g+shiftG) <= 255)
        {
            if(!outmark) draughlet.setFillColor(sf::Color(draughlet.getFillColor().r, draughlet.getFillColor().g+shiftG, draughlet.getFillColor().b)); //recoloring
            else draughlet.setOutlineColor(sf::Color(draughlet.getOutlineColor().r, draughlet.getOutlineColor().g+shiftG, draughlet.getOutlineColor().b)); //recoloring
        }
        else draughlet.setFillColor(sf::Color(draughlet.getFillColor().r, 0, draughlet.getFillColor().b));
    }
    else draughlet.setFillColor(sf::Color(draughlet.getFillColor().r, 255, draughlet.getFillColor().b));

    if((draughlet.getFillColor().b+shiftB) >= 0) //B SHIFT
    {
        if((draughlet.getFillColor().b+shiftB) <= 255)
        {
            if(!outmark) draughlet.setFillColor(sf::Color(draughlet.getFillColor().r, draughlet.getFillColor().g, draughlet.getFillColor().b+shiftB)); //recoloring
            else draughlet.setOutlineColor(sf::Color(draughlet.getOutlineColor().r, draughlet.getOutlineColor().g, draughlet.getOutlineColor().b+shiftB));//recoloring
        }
        else draughlet.setFillColor(sf::Color(draughlet.getFillColor().r, draughlet.getFillColor().g, 0));
    }
    else draughlet.setFillColor(sf::Color(draughlet.getFillColor().r, draughlet.getFillColor().g, 255));
}

void particle::edgrette(float shift)//----------------------------------------------------------------------------------------------------------------------------------------------------
{
    draughlet.setSize(sf::Vector2f(draughlet.getSize().x+shift, draughlet.getSize().y+shift));
    draughlet.setOutlineThickness(draughlet.getSize().x/4);
    draughlet.setOrigin(draughlet.getSize().x/2, draughlet.getSize().x/2);
}

void particle::spin(float shift)//----------------------------------------------------------------------------------------------------------------------------------------------------------
{
    //ss.str("");
    //ss << draughlet.getRotation();

    if((draughlet.getRotation()+shift) >= 0)
    {
        if(draughlet.getRotation()+shift <= 359.0)
        {
            draughlet.rotate(shift);
        }
        else draughlet.rotate(shift-359);
    }
    else draughlet.rotate(359+shift);

    if(draughlet.getRotation() >= 0.000 && draughlet.getRotation() < 90.00) draughlet.setFillColor(sf::Color::Blue);
    if(draughlet.getRotation() >= 90.00 && draughlet.getRotation() < 180.0) draughlet.setFillColor(sf::Color::Green);
    if(draughlet.getRotation() >= 180.0 && draughlet.getRotation() < 270.0) draughlet.setFillColor(sf::Color::Red);
    if(draughlet.getRotation() >= 270.0 && draughlet.getRotation() < 360.0) draughlet.setFillColor(sf::Color::Yellow);
}

void particle::brimUnderseeking(int steps, int farthing)//------------------------------------------------------------------------------------------------------------------------------------
{
    if(draughlet.getPosition().y < 0)
    {
        if(draughlet.getPosition().x < 0 || draughlet.getPosition().x >= 640)
        {
            edset(10, 10, 0);
            return;
        }
        if(farthing == 1)
        {
            if(strength) draughlet.setRotation(90+(90-draughlet.getRotation()));
            else edset(0, 0, 0);
        }
        else if(farthing == 4)
        {
            if(strength) draughlet.setRotation(270-(90-(360-draughlet.getRotation())));
            else edset(0, 0, 0);
        }
        else edset(00, 00, 0); //this code will theoretically never run
    }
    if(draughlet.getPosition().x >= 640)
    {
        if(draughlet.getPosition().y < 0 || draughlet.getPosition().y >= 480)
        {
            edset(10, 10, 0);
            return;
        }
        if(farthing==1)
        {
            if(strength) draughlet.setRotation(360-(90-(90-draughlet.getRotation())));
            else edset(0, 0, 0);
        }
        else if(farthing==2)
        {
            if(strength) draughlet.setRotation(180+(90-(draughlet.getRotation()-90)));
            else edset(0, 0, 0);
        }
        else edset(00, 00, 0);
    }
    if(draughlet.getPosition().y >= 480)
    {
        if(draughlet.getPosition().x < 0 || draughlet.getPosition().x >= 640)
        {
            edset(10, 10, 0);
            return;
        }
        if(farthing == 2)
        {
            if(strength) draughlet.setRotation(90-(90-(180-draughlet.getRotation())));
            else edset(0, 0, 0);
        }
        else if(farthing == 3)
        {
            if(strength) draughlet.setRotation(270+(90-(draughlet.getRotation()-180)));
            else edset(0, 0, 0);
        }
        else edset(00, 00, 0);
    }
    if(draughlet.getPosition().x < 0) //left border
    {
        if(draughlet.getPosition().y < 0 || draughlet.getPosition().y >= 480)
        {
            edset(10, 10, 0);
            return;
        }
        if(farthing == 3)
        {
            if(strength) draughlet.setRotation(180-(90-(270-draughlet.getRotation())));
            else edset(0, 0, 0);
        }
        else if(farthing == 4)
        {
            if(strength) draughlet.setRotation(0+(90-(draughlet.getRotation()-270)));
            else edset(0, 0, 0);
        }
        else edset(00, 00, 0);
    }
}
void particle::beway(int steps)//---------------------------------------------------------------------------------------------------------------------------------------------------------
{

    if(draughlet.getRotation() >= 0.000 && draughlet.getRotation() < 90.00)
    {
        draughlet.move(draughlet.getRotation()/steps,-(90-draughlet.getRotation())/steps);
        brimUnderseeking(steps, 1);
    }
    if(draughlet.getRotation() >= 90.00 && draughlet.getRotation() < 180.0)
    {
        draughlet.move((180-draughlet.getRotation())/steps, (draughlet.getRotation()-90)/steps);
        brimUnderseeking(steps, 2);
    }
    if(draughlet.getRotation() >= 180.0 && draughlet.getRotation() < 270.0)
    {
        draughlet.move(-(draughlet.getRotation()-180)/steps, (270-draughlet.getRotation())/steps);
        brimUnderseeking(steps, 3);
    }
    if(draughlet.getRotation() >= 270.0 && draughlet.getRotation() < 360.0)
    {
        draughlet.move(-(360-draughlet.getRotation())/steps, -(draughlet.getRotation()-270)/steps);
        brimUnderseeking(steps, 4);
    }
}

void particle::draw(sf::RenderWindow *windough)
{
    //bewriting.setString(ss.str());
    //windough->draw(bewriting);
    windough->draw(draughlet);
}

void particle::console()
{
    std::cout << "rotation: " << draughlet.getRotation() <<  ", grette: " << draughlet.getSize().x << ", blee: (" << draughlet.getFillColor().r << draughlet.getFillColor().g << draughlet.getFillColor().b << ")\n";
}

void particle::setBewriting(sf::Font font, int x, int y)
{
    bewriting.setFont(font);
    bewriting.setString("test");
    bewriting.setColor(sf::Color::Red);
    bewriting.setCharacterSize(20);
    bewriting.setPosition(x, y);
}