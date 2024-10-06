#pragma once
typedef struct Color{
    unsigned char r; // Red component
    unsigned char g; // Green component
    unsigned char b; // Blue component
    unsigned char a; // Alpha component

    // Constructor to initialize the color
    Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}

    Color(const Color& other)
        : r(other.r), g(other.g), b(other.b), a(other.a) {}


}color_t;