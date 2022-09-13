//
// Created by Ben on 20/07/2022.
//

#ifndef GAMEENGINE_TYPES_H
#define GAMEENGINE_TYPES_H
#include <iostream>
#include <math.h>

typedef struct vec2 {
    double x;
    double y;

    vec2(double a, double b) : x(a), y(b) {}
    vec2(double a) : x(a), y(a) {}
    vec2() : x(0.0), y(0.0) {}
    vec2(const vec2& v) : x(v.x), y(v.y) {}

    double length() const {
        return sqrt((x * x) + (y * y));
    }

    void operator+=(const vec2& b) {
        x += b.x;
        y += b.y;
    }

    void operator-=(const vec2& b) {
        x -= b.x;
        y -= b.y;
    }

    void operator*=(const vec2& b) {
        x *= b.x;
        y *= b.y;
    }

    vec2 operator+(const vec2& b) {
        return {x + b.x, y + b.y};
    }

    vec2 operator+(const vec2& b) const {
        return {x + b.x, y + b.y};
    }

    vec2 operator-(const vec2& b) {
        return {x - b.x, y - b.y};
    }

    vec2 operator*(const double& b) {
        return {x * b, y * b};
    }

    vec2 operator*(const double& b) const {
        return {x * b, y * b};
    }

    vec2 operator/(const double& b) {
        return {x / b, y / b};
    }

    vec2  operator/(const double& b) const {
        return {x / b, y / b};
    }

    vec2 operator/(const vec2& b) {
        return {x / b.x, y / b.y};
    }

    friend std::ostream& operator<<(std::ostream& os, const vec2& a) {
        os << "(" << a.x << ", " << a.y << ")";
        return os;
    }

} vec2;

typedef struct color {
    int r;
    int g;
    int b;
    int a;

    color(int a, int b, int c, int d = 0xFF) :
            r(a), g(b), b(c), a(d)
    {};
} Color;

const Color COLOR_WHITE =   {0xFF, 0xFF, 0xFF};
const Color COLOR_BLACK =   {0x00, 0x00, 0x00};
const Color COLOR_RED =     {0xFF, 0x00, 0x00};
const Color COLOR_GREEN =   {0x00, 0xFF, 0x00};
const Color COLOR_BLUE =    {0x00, 0x00, 0xFF};

const vec2 VEC2_UP = {0, -1};
const vec2 VEC2_RIGHT = {1, 0};
const vec2 VEC2_DOWN = {0, 1};
const vec2 VEC2_LEFT = {-1, 0};


#endif //GAMEENGINE_TYPES_H
