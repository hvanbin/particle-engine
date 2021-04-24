#ifndef PARTICLE_H
#define PARTICLE_H

extern sf::Font commonFont;

class particle
{
    protected:

        sf::RectangleShape draughlet;
        /*std::ostringstream ss;
        sf::Text bewriting;*/

        int fX; int fY; //initial position
        int oX; int oY; //change position
        bool oStrike; //collision switch
        float wending; //initial direction
        float oWending; //change to direction
        int grette; //initial size
        bool strength; //determines whether particle is reset (edset) after hitting window boundaries
        void brimUnderseeking(int steps, int farthing); //farthing is used to inform the boundary check of what quadrant of rotation the particle is in.
    public:

        particle();
        virtual ~particle();

        void outset(int initial_x, int initial_y, int initial_grette, float initial_wending, bool initial_strength); //pseudo-constructor, sets initial values

        void setOffset(int shiftX, int shiftY, float shiftW);
        void setBlee(int r, int g, int b, int a, bool outmark); //sets color, outmark determines if for outline, done!
        void setStrength(bool shift);
        void strike(particle *other); //WIP

        void edset(int shiftX, int shiftY, float oWending); //reset function allowing for stored (dynamic) offsets, does not rewrite initial values
        void edblee(float shiftR, float shiftG, float shiftB, bool outmark); //recolors the particle with checks
        void edgrette(float shift); //resizes particle with checks
        void spin(float shift);//rotates the particle with checks
        void beway(int steps);//teh Be5t c0d3z evar!! moves particle based on rotation

        void draw(sf::RenderWindow *windough);
        void console();
};

#endif // PARTICLE_H
