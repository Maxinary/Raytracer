#pragma once 

struct Color{
	unsigned char r,g,b;
};

Color operator*(const Color& c, double d);
Color operator*(double d, const Color& c);
Color operator+(const Color& c1, const Color& c2);
Color operator*(const Color& c1, const Color& c2);
