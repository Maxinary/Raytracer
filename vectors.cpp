#include <math.h>
#include "vectors.h"

using namespace vectors;

//V       V EEEEEE  CCCCC  33333
// V     V  E      C           3
//  V   V   EEEE   C       33333
//   V V    E      C           3
//    V     EEEEEE  CCCCC  33333
vec3::vec3(){
	x = 0;
	y = 0;
	z = 0;
}

vectors::vec3::vec3(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3 vec3::normalize() const{
	double length = this->length();
	
	return vectors::vec3(x/length, y/length, z/length);
}

double vec3::length() const{
	return sqrt(x*x+y*y+z*z);
}

vec3 vec3::scale(double d) const{
	return vec3(x*d,y*d,z*d);
}

double vectors::vec3::dist(vec3 a) const{
	double dx = (a.x-this->x);
	double dy = (a.y-this->y);
	double dz = (a.z-this->z);

	return sqrt(dx*dx+dy*dy+dz*dz);
}

const vec3 vec3::operator+(const vec3& a) const {
	return vec3(this->x+a.x, this->y+a.y, this->z+a.z);
}

const vec3 vec3::operator-(const vec3& a) const {
	return vec3(this->x-a.x, this->y-a.y, this->z-a.z);
}

const vec3 vec3::operator*(const vec3& a) const {
	return vec3(this->x*a.x, this->y*a.y, this->z*a.z);
}

const vec3 vec3::operator/(const vec3& a) const {
	return vec3(this->x/a.x, this->y/a.y, this->z/a.z);
}

double vec3::dot(vec3 a) const{
	return this->x*a.x + this->y*a.y + this->z*a.z;
}

const vec3 vec3::cross(vec3 a) const{
	return vec3(this->y*a.z - this->z*a.y, this->z*a.x - this->x*a.z, this->x*a.y - this->y*a.x); 
}

// MM    MM      A    TTTTTTTTT 33333
// M M  M M     A A       T         3
// M  MM  M    AAAAA      T     33333
// M      M   A     A     T         3
// M      M  A       A    T     33333

mat3::mat3(){
	row1 = vec3(0,0,0);
	row2 = vec3(0,0,0);
	row3 = vec3(0,0,0);
}

mat3::mat3(vec3 r1, vec3 r2, vec3 r3){
	row1 = r1;
	row2 = r2;
	row3 = r3;
}

const vectors::vec3 operator*(const vectors::vec3& v, const vectors::mat3& m){
	return vec3(
			v.x*m.row1.x + v.y*m.row1.y + v.z*m.row1.z,
			v.x*m.row2.x + v.y*m.row2.y + v.z*m.row2.z,
			v.x*m.row3.x + v.y*m.row3.y + v.z*m.row3.z
		);
}
