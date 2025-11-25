#pragma once
#include "Point.hpp"

class Velocity {
  public:
    Velocity() = default;
    
    Velocity(double x, double y) : vec{x, y} {}
    Velocity(const Point& vector) {
        setVector(vector);
    }

    void setVector(const Point& vector) {
        vec = vector;
    }

    Point vector() const {
        return vec;
    }

  private:
    Point vec;
};

inline std::istream& operator>>(std::istream& stream, Velocity& v) {
    Point p;
    stream >> p;        
    v.setVector(p);     
    return stream;
}