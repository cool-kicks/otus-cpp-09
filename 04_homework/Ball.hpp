#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"
#include "Color.hpp"

class Ball {
public:
    Ball(const Point& center_, double radius_, const Color& color_ = Color(1.0, 0.0, 0.0),
        const Velocity& velocity_ = Velocity(), bool isCollidable = true)
        : center(center_),
        velocity(velocity_),
        radius(radius_),
        color(color_),
        mass(4.0 / 3.0 * PI * radius_ * radius_ * radius_),
        isCollidable_(isCollidable) {}

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const{return mass;}
    bool isCollidable() const { return isCollidable_; }

private:
    Point center;
    Velocity velocity;
    double radius;
    Color color;
    double mass;
    static constexpr double PI = 3.14159265358979323846;
    bool isCollidable_;

};
