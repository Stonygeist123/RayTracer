#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.hh"

struct HitRecord {
	Point3 p;
	Vec3 normal;
	float t = 0;
	bool front_face = false;

	inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class Hittable {
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

#endif