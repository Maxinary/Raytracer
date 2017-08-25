#include "Color.h"

Color operator*(const Color& c, double d){
	return Color{(unsigned char)(c.r*d),(unsigned char)(c.g*d),(unsigned char)(c.b*d)};
}

Color operator*(double d, const Color& c){
	return Color{(unsigned char)(c.r*d),(unsigned char)(c.g*d),(unsigned char)(c.b*d)};
}

Color operator+(const Color& c1, const Color& c2){
	double r1 = ((double)c1.r/255);
	double r2 = ((double)c2.r/255);
	unsigned char r0 = (unsigned char)(255*(r1+r2-r1*r2));

	double g1 = ((double)c1.g/255);
	double g2 = ((double)c2.g/255);
	unsigned char g0 = (unsigned char)(255*(g1+g2-g1*g2));

	double b1 = ((double)c1.b/255);
	double b2 = ((double)c2.b/255);
	unsigned char b0 = (unsigned char)(255*(b1+b2-b1*b2));

	return Color{r0,g0,b0};
}

Color operator*(const Color& c1, const Color& c2){
	double r1 = ((double)c1.r/255);
	double r2 = ((double)c2.r/255);
	unsigned char r0 = (unsigned char)(255*(r1*r2));

	double g1 = ((double)c1.g/255);
	double g2 = ((double)c2.g/255);
	unsigned char g0 = (unsigned char)(255*(g1*g2));

	double b1 = ((double)c1.b/255);
	double b2 = ((double)c2.b/255);
	unsigned char b0 = (unsigned char)(255*(b1*b2));

	return Color{r0,g0,b0};	
}
