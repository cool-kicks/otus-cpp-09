#pragma once
#include "Ball.hpp"
#include <vector>
#include <functional>

class Physics {
  public:
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    void update(std::vector<Ball>& balls, size_t ticks) const;
    void setCollisionCallback(std::function<void(const Point&)> callback) {
        collisionCallback = callback;
    }
    

  private:
    void collideBalls(std::vector<Ball>& balls) const;
    void collideWithBox(std::vector<Ball>& balls) const;
    void move(std::vector<Ball>& balls) const;
    void processCollision(Ball& a, Ball& b,
                          double distanceBetweenCenters2) const;

  private:
    Point topLeft;
    Point bottomRight;
    double timePerTick;
    std::function<void(const Point&)> collisionCallback;
};
