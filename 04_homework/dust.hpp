#pragma once
#include "Point.hpp"
#include "Velocity.hpp"
#include "Color.hpp"
#include "Painter.hpp"

class Dust {
    public:
    Dust(const Point& pos, const Velocity& vel, double lifetime, double radius,
    Color color)
    : position(pos), velocity(vel), lifetime(lifetime), radius(radius), color(color){}

    void update(double dt){
        position = position + velocity.vector()*dt;
        lifetime -= dt;
    }

    bool expired() const {return lifetime <= 0.0;}

    void draw(Painter& painter) const {
        painter.draw(position, radius, color);
    }

    private:
    Point position;
    Velocity velocity;
    double lifetime;
    double radius;
    Color color;
};