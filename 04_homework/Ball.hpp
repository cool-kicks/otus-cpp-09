#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"
#include "Color.hpp"

class Ball {
public:
    Ball(const Point& center_, double radius_, const Color& color_ = Color(1.0, 0.0, 0.0))
        : center(center_), radius(radius_), color(color_) {}
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;

private:
    Point center;
    Velocity velocity;
    double radius;
    Color color;

};
