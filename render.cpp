#include "render.h"


surface_list	surfaces;
light				sun;
image				rendered;


image render(int width, int height, surface_list new_surfaces, light new_light) {
	surfaces	= new_surfaces;
	sun		= new_light;

	rendered.change_size(width, height);

	vector3 d;
	d.set(0, 0, -1);
	vector3 o;

	Ray sighting;

	for (int i = 0; i <= width; ++i) {
		for (int j = 0; j <= height; ++j) {
			o.set(float(i), float(j), 0);
			sighting.Set(o, d);
			rendered.set(i, j, color(sighting));
		}
	}
	return rendered;
}



RGB color(Ray sighting) {
	RGB		black(0.0, 0.0, 0.0);
	RGB		color;
	surface	what;
	hit_info	info;
	Interval	forever;

	forever.SetBottom(0);
	forever.SetTopInfinite();

	if (!surfaces.hit(sighting, forever, what, info)) {
		return black;
	}
	else {
		color = 0.25 * info.color;
		if (!shadow(sighting.PointAt(info.inside.Get_Bottom()))) {
			float modifier;
			sun.direction = sun.direction / length(sun.direction);
			modifier = dot(info.normal, -sun.direction);
			if (modifier < 0) {
				modifier = -modifier;
			}
			RGB L;
			L = info.color * sun.color * modifier;
			color = color + 0.75 * L;
		}
		return color;
	}
}


bool shadow(vector3 point) {
	Ray shadow_ray;
	shadow_ray.Set(point, -sun.direction);

	Interval always;
	always.SetBottom(epsilon);
	always.SetTopInfinite();
	surface blah;
	hit_info info;
	return (surfaces.hit(shadow_ray, always, blah, info));
}