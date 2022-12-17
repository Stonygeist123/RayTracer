#ifndef COLOR_H
#define COLOR_H

#include "Vec3.hh"

#include <iostream>

void write_color(std::ostream& out, Color pixel_color, int samples_per_pixel) {
	float r = pixel_color.x();
	float g = pixel_color.y();
	float b = pixel_color.z();

	float scale = 1.f / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;

	out << static_cast<int>(256 * std::clamp(r, .0f, .999f)) << ' ' << static_cast<int>(256 * std::clamp(g, .0f, .999f))
		<< ' ' << static_cast<int>(256 * std::clamp(b, .0f, .999f)) << '\n';
}

#endif