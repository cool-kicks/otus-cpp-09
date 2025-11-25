#include "World.hpp"
#include "Painter.hpp"
#include <fstream>
#include <iostream>


// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) {

    std::ifstream stream(worldFilePath);
    if (!stream.is_open()) {
        std::cerr << "Failed to open world file: " << worldFilePath << std::endl;
        return;
    }
  
    stream >> topLeft >> bottomRight;
    physics.setWorldBox(topLeft, bottomRight);

    physics.setCollisionCallback([this](const Point& p) {
        spawnDust(p, 20);
    });


    while (stream.good()) {
        Point center;
        Velocity vel;
        Color color;
        double radius;
        bool isCollidable;

        stream >> center >> vel >> color >> radius >> std::boolalpha >> isCollidable;
        if (!stream.good()) break;

        balls.emplace_back(center, radius, color, vel, isCollidable);
        
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }

    for (const auto& d : dusts)
    d.draw(painter);
}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls, ticks);

    for (auto& d : dusts)
    d.update(timePerTick);

    dusts.erase(
    std::remove_if(dusts.begin(), dusts.end(),
                   [](const Dust& d){ return d.expired(); }),
    dusts.end());
}

void World::spawnDust(const Point& pos, int amount)
{
    for (int i = 0; i < amount; i++) {
        double angle = (rand() / double(RAND_MAX)) * 2.0 * PI;
        double speed = (rand() / double(RAND_MAX)) * 120 + 30;

        Velocity v(speed * cos(angle), speed * sin(angle));

        double lifetime = (rand() / double(RAND_MAX)) * 0.5 + 0.3;
        double radius = (rand() / double(RAND_MAX)) * 10 +5;

        Color col(1.0, 0.8, 0.3);

        dusts.emplace_back(pos, v, lifetime, radius, col);
    }
}