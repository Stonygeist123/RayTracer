#include "Camera.hh"
#include <fstream>
#include <sstream>

float hit_sphere(const Point3& center, float radius, const Ray& r) {
	Vec3 oc = r.origin() - center;
	float a = r.direction().length_squared();
	float half_b = dot(oc, r.direction());
	float c = oc.length_squared() - radius * radius;
	float discriminant = half_b * half_b - a * c;

	return discriminant < 0 ? -1.f : (-half_b - sqrt(discriminant)) / a;
}

Color ray_color(const Ray& r, const Hittable& world) {
	HitRecord rec;
	if (world.hit(r, 0, infinity, rec))
		return .5f * (rec.normal + Color(1, 1, 1));

	Vec3 unit_direction = unit_vector(r.direction());
	auto t = .5f * (unit_direction.y() + 1.f);
	return (1.f - t) * Color(1.f, 1.f, 1.f) + t * Color(.5f, .7f, 1.f);
}

int main() {
	/*
	 * Image
	 */
	constexpr float aspect_ratio = 16.0f / 9.0f;
	constexpr int image_width = 400;
	constexpr int image_height = static_cast<int>(image_width / aspect_ratio);
	constexpr int samples_per_pixel = 100;

	std::fstream img{ "..\\..\\..\\o.ppm" };
	if (!img.is_open()) {
		std::cout << "Could not opem file.";
		std::exit(0);
	}

	std::uniform_real_distribution<float> d(.0f, 1.f);
	std::mt19937 gen;

	/*
	 * World
	 */
	HittableList world;
	world.add(std::make_shared<Sphere>(Point3(0, 0, -1), .5f));
	world.add(std::make_shared<Sphere>(Point3(0, -10.5f, -1), 100));

	/*
	 * Camera
	 */
	Camera cam;

	/*
	 * Render
	 */
	std::stringstream ss{};
	ss << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rRemaining lines: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
			Color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				float u = (i + d(gen)) / (image_width - 1);
				float v = (j + d(gen)) / (image_height - 1);
				Ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world);
			}

			write_color(ss, pixel_color, samples_per_pixel);
		}
	}

	img << ss.str();
	std::cerr << "\nDone.\n";
}