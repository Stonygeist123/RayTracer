#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.hh"
#include "Vec3.hh"

class Sphere : public Hittable {
public:
	Point3 center;
	float radius;
	Sphere() : radius(0) {}
	Sphere(Point3 cen, float r) : center(cen), radius(r){};

	virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
};

bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
	Vec3 oc = r.origin() - center;
	float a = r.direction().length_squared();
	float half_b = dot(oc, r.direction());
	float c = oc.length_squared() - radius * radius;

	float discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return false;

	float sqrtd = sqrt(discriminant);
	float root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	rec.normal = (rec.p - center) / radius;
	Vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	return true;
}

#endif