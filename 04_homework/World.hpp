#pragma once
#include "Ball.hpp"
#include "Physics.hpp"
#include <string>
#include <vector>
#include "dust.hpp"

class Painter;

class World {
  public:
    World(const std::string& worldFilePath);
    void show(Painter& painter) const;
    void update(double time);
    void spawnDust(const Point& pos, int amount);

  private:
    // Границы мира заданы углами прямоугольника
    Point topLeft;
    Point bottomRight;
    // Объект физического движка
    Physics physics;
    // Контейнер с шарами
    std::vector<Ball> balls;
    std::vector<Dust> dusts;
    // Длина отрезка времени, который не был
    // учтен при прошлой симуляции. См. реализацию update
    double restTime = 0.;
    static constexpr double PI = 3.14159265358979323846;
};
