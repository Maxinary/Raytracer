#pragma once

namespace vectors{
	class vec3{
	public:
		vec3();
		vec3(double x, double y, double z);
	
		double length() const;
		double dist(vec3) const;
		
		vec3 normalize() const;
		
		vec3 scale(double) const;
		
		const vec3 operator+(const vec3&) const;
		const vec3 operator-(const vec3&) const;
		const vec3 operator*(const vec3&) const;
		const vec3 operator/(const vec3&) const;
		
		double dot(const vec3) const;
		const vec3 cross(const vec3) const;
		
		double x, y, z;
	};
	
	class mat3{
	public:
		mat3();
		mat3(vec3,vec3,vec3);
		
		vec3 row1, row2, row3;
	};
}
const vectors::vec3 operator*(const vectors::vec3&, const vectors::mat3&);

