#ifndef MAIN_H
#define MAIN_H

#include <limits>
#include <memory>
#include <numbers>
#include <random>

// Constants

const float infinity = std::numeric_limits<float>::infinity();

// Utility Functions

inline float degrees_to_radians(float degrees) { return degrees * std::numbers::pi_v<float> / 18.f; }

// Common Headers

#include "Color.hh"
#include "HittableList.hh"
#include "Ray.hh"
#include "Sphere.hh"
#include "Vec3.hh"

#endif