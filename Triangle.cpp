#include "Triangle.h"

Triangle::Triangle(vectors::vec3 a, vectors::vec3 b, vectors::vec3 c) : 
	WorldObject((a+b+c).scale(1/3)), 
	vertices({a,b,c}), 
	normal((a-b).cross(b-c).normalize()){}

double Triangle::rayTouching(Ray r){
	vectors::vec3 e1 = vertices[1] - vertices[0];
	vectors::vec3 e2 = vertices[2] - vertices[0];
	// Calculate planes normal vector
	vectors::vec3 pvec = r.direction.cross(e2);
	double det = e1.dot(pvec);

    // Ray is parallel to plane
    if (det < 1e-8 && det > -1e-8) {
        return 0;
    }

	double inv_det = 1 / det;
    vectors::vec3 tvec = r.pos - vertices[0];
    double u = tvec.dot(pvec) * inv_det;
    if (u < 0 || u > 1) {
        return 0;
    }

	vectors::vec3 qvec = tvec.cross(e1);
    double v = r.direction.dot(qvec) * inv_det;
    if (v < 0 || u + v > 1) {
        return 0;
    }
    return e2.dot(qvec) * inv_det;
}

vectors::vec3 Triangle::getNormal() const{
	return normal;
}
