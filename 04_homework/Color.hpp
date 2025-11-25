#pragma once
#include <iostream>

class Color {
  public:
    Color();
    Color(double red, double green, double blue);

    double red() const;
    double green() const;
    double blue() const;

  private:
    double r{};
    double g{};
    double b{};
};

inline std::istream& operator>>(std::istream& stream, Color& c) {
    double red, green, blue;
    stream >> red >> green >> blue;
    c = Color(red, green, blue);
    return stream;
}
