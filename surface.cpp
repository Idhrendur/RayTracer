#include "surface.h"



/***************************************\
*****************************************
**													**
**					Surface						**
**													**
*****************************************
\***************************************/


surface::surface()
{
	color.set(0.5, 0.5, 0.5);
	type = nothing;
}


surface surface::operator=(surface& right)
{
	color = right.color;
	type = right.type;
	return *this;
}


surface::~surface()
{
	// nothing to do
}


bool surface::hit(Ray incoming, Interval length, surface& what, hit_info& info)
{
	return false;
}


surface_type surface::get_type()
{
	return type;
}



/***************************************\
*****************************************
**													**
**				Surface List					**
**													**
*****************************************
\***************************************/


surface_list::surface_list()
{
	surfaces.clear();
	type = s_list;
}


surface_list::surface_list(surface_list& right)
{
	type = s_list;
	vector<surface*>::iterator i;
	surface* new_surface;
	for (i = right.surfaces.begin(); i != right.surfaces.end(); ++i)
	{
		switch ((*i)->get_type())
		{
			case nothing:
				new_surface = new surface;
				*new_surface = **i;
				surfaces.push_back(new_surface);
				break;
			case s_list:
				new_surface = new surface_list;
				*(surface_list*)new_surface = *(surface_list*)*i;
				surfaces.push_back(new_surface);
				break;
			case s_sphere:
				new_surface = new sphere;
				*(sphere*)new_surface = *(sphere*)*i;
				surfaces.push_back(new_surface);
				break;
			case s_cube:
				new_surface = new cube;
				*(cube*)new_surface = *(cube*)*i;
				surfaces.push_back(new_surface);
				break;
			case s_cylinder:
				new_surface = new cylinder;
				*(cylinder*)new_surface = *(cylinder*)*i;
				surfaces.push_back(new_surface);
				break;
			case s_plane:
				new_surface = new plane;
				*(plane*)new_surface = *(plane*)*i;
				surfaces.push_back(new_surface);
				break;
			case s_triangle:
				new_surface = new triangle;
				*(triangle*)new_surface = *(triangle*)*i;
				surfaces.push_back(new_surface);
				break;
			default:
				break;
		};
	}
}


surface_list surface_list::operator=(surface_list& right)
{
	type = s_list;
	int size = right.surfaces.size();
	surfaces.resize(size);
	for (int i = 0; i < size; ++i)
	{
		switch (right.surfaces[i]->get_type())
		{
			case nothing:
				surfaces[i] = new surface;
				*surfaces[i] = *right.surfaces[i];
				break;
			case s_list:
				surfaces[i] = new surface_list;
				*(surface_list*)surfaces[i] = *(surface_list*)right.surfaces[i];
				break;
			case s_sphere:
				surfaces[i] = new sphere;
				*surfaces[i] = *(sphere*)right.surfaces[i];
				break;
			case s_cube:
				surfaces[i] = new cube;
				*(cube*)surfaces[i] = *(cube*)right.surfaces[i];
				break;
			case s_cylinder:
				surfaces[i] = new cylinder;
				*(cylinder*)surfaces[i] = *(cylinder*)right.surfaces[i];
				break;
			case s_plane:
				surfaces[i] = new plane;
				*(plane*)surfaces[i] = *(plane*)right.surfaces[i];
				break;
			case s_triangle:
				surfaces[i] = new triangle;
				*(triangle*)surfaces[i] = *(triangle*)right.surfaces[i];
				break;
			default:
				break;
		};
	}
	return *this;
}


surface_list::~surface_list()
{
	surfaces.clear();
}


void surface_list::add(surface* new_surface)
{
	int size = surfaces.size();
	surfaces.resize(size + 1);
	switch (new_surface->get_type())
	{
		case nothing:
			surfaces[size] = new surface;
			*surfaces[size] = *new_surface;
			break;
		case s_list:
			surfaces[size] = new surface_list;
			*(surface_list*)surfaces[size] = *(surface_list*)new_surface;
			break;
		case s_sphere:
			surfaces[size] = new sphere;
			*(sphere*)surfaces[size] = *(sphere*)new_surface;
			break;
		case s_cube:
			surfaces[size] = new cube;
			*(cube*)surfaces[size] = *(cube*)new_surface;
			break;
		case s_cylinder:
			surfaces[size] = new cylinder;
			*(cylinder*)surfaces[size] = *(cylinder*)new_surface;
			break;
		case s_plane:
			surfaces[size] = new plane;
			*(plane*)surfaces[size] = *(plane*)new_surface;
			break;
		case s_triangle:
			surfaces[size] = new triangle;
			*(triangle*)surfaces[size] = *(triangle*)new_surface;
			break;
		default:
			break;
	};
}


void surface_list::clear()
{
	surfaces.clear();
}


bool surface_list::hit(Ray incoming, Interval length, surface& what, hit_info& info)
{
	Interval not_hit_yet;
	surface this_surface;
	hit_info current_info;
	bool any_hits;

	not_hit_yet = length;
	any_hits = false;

	for (std::vector<surface*>::iterator i = surfaces.begin(); i != surfaces.end(); ++i)
	{
		if ((*i)->hit(incoming, not_hit_yet, this_surface, current_info))
		{
			not_hit_yet.SetTop(current_info.inside.Get_Bottom());
			what = this_surface;
			info = current_info;
			any_hits = true;
		}
	}

	return any_hits;
}



/***************************************\
*****************************************
**													**
**					Sphere						**
**													**
*****************************************
\***************************************/


sphere::sphere()
{
	center.set(0.0, 0.0, 0.0);
	radius = 1.0;
	type = s_sphere;
}


sphere::sphere(RGB new_color, vector3 new_center, float new_radius)
{
	color = new_color;
	center = new_center;
	radius = new_radius;
	type = s_sphere;
}


sphere::sphere(sphere& right)
{
	center = right.center;
	color = right.color;
	radius = right.radius;
	type = s_sphere;
}


sphere sphere::operator=(sphere& right)
{
	center = right.center;
	color = right.color;
	radius = right.radius;
	type = s_sphere;
	return *this;
}


sphere::~sphere()
{
	// nothing to do
}


void sphere::set(RGB new_color, vector3 new_center, float new_radius)
{
	color = new_color;
	center = new_center;
	radius = new_radius;
}


bool sphere::hit(Ray incoming, Interval where, surface& what, hit_info& info)
{
	//	cout << "center: (" << center.get(0) << ", " << center.get(1) << ", " << center.get(2) << ")" << endl;
	//	cout << "radius: " << radius << endl;


	what = *this;
	info.color = color;

	vector3 o, d;
	o = incoming.get_o();
	d = incoming.get_d();

	float A = dot(d, d);
	vector3 offset = o - center;
	float B = dot(d, offset);
	float C = dot(offset, offset) - (radius * radius);

	float disc;
	disc = (B * B) - (A * C);


	if (disc >= epsilon)
	{
		float sqrtd = sqrt(disc);
		float first = (-B - sqrtd) / A;
		float second = (-B + sqrtd) / A;
		info.inside.SetBottom(std::min(first, second));
		info.inside.SetTop(std::max(first, second));
		info.normal = (o + std::min(first, second) * d) - center;
		info.normal = info.normal / length(info.normal);
		if (Overlap(info.inside, where))
			return true;
	}
	return false;
}



/***************************************\
*****************************************
**													**
**						Cube						**
**													**
*****************************************
\***************************************/


cube::cube()
{
	center.set(0.0, 0.0, 0.0);
	edge_length = 1.0;
	up.set(0.0, 1.0, 0.0);
	right.set(1.0, 0.0, 0.0);
	forward.set(0.0, 0.0, 1.0);
	type = s_cube;
}


cube::cube(RGB new_color,
	 vector3 new_center,
	 float new_edge_length,
	 vector3 new_up,
	 vector3 new_right,
	 vector3 new_forward)
{
	color = new_color;
	center = new_center;
	edge_length = new_edge_length;
	up = new_up / length(new_up);
	right = new_right / length(new_right);
	forward = new_forward / length(new_forward);
	type = s_cube;
}


cube::~cube()
{
	// nothing to do
}


void cube::set(RGB new_color,
	 vector3 new_center,
	 float new_edge_length,
	 vector3 new_up,
	 vector3 new_right,
	 vector3 new_forward)
{
	color = new_color;
	center = new_center;
	edge_length = new_edge_length;
	up = new_up / length(new_up);
	right = new_right / length(new_right);
	forward = new_forward / length(new_forward);
}


bool cube::hit(Ray incoming, Interval length, surface& what, hit_info& info)
{
	vector3 a;
	vector3 n;
	float denominator;
	float numerator;
	float first;
	float second;

	what = *this;
	info.color = color;

	// find interval for top/bottom
	Interval tb;
	vector3 tb_normal;
	n = up;
	a = center + edge_length * n / 2;
	denominator = dot(incoming.get_d(), n);
	numerator = dot(a - incoming.get_o(), n);
	if (denominator != 0)
	{
		first = numerator / denominator;
	}
	n = -up;
	a = center + edge_length * n / 2;
	denominator = dot(incoming.get_d(), n);
	numerator = dot(a - incoming.get_o(), n);
	if (denominator == 0)
	{
		if (abs(dot(incoming.get_o() - center, n)) <= (edge_length / 2))
		{
			tb.SetInfinite();
		}
		else
		{
			tb.SetNan();
		}
	}
	else
	{
		second = numerator / denominator;
		tb.SetBottom(std::min(first, second));
		tb.SetTop(std::max(first, second));
		if (first < second)
		{
			tb_normal = up;
		}
		else
		{
			tb_normal = -up;
		}
	}

	// find interval for left/right
	Interval lr;
	vector3 lr_normal;
	n = right;
	a = center + edge_length * n / 2;
	denominator = dot(incoming.get_d(), n);
	numerator = dot(a - incoming.get_o(), n);
	if (denominator != 0)
	{
		first = numerator / denominator;
	}
	n = -right;
	a = center + edge_length * n / 2;
	denominator = dot(incoming.get_d(), n);
	numerator = dot(a - incoming.get_o(), n);
	if (denominator == 0)
	{
		if (abs(dot(incoming.get_o() - center, n)) <= (edge_length / 2))
		{
			lr.SetInfinite();
		}
		else
		{
			lr.SetNan();
		}
	}
	else
	{
		second = numerator / denominator;
		lr.SetBottom(std::min(first, second));
		lr.SetTop(std::max(first, second));
		if (first < second)
		{
			lr_normal = right;
		}
		else
		{
			lr_normal = -right;
		}
	}

	// find interval for front/back
	Interval fb;
	vector3 fb_normal;
	n = forward;
	a = center + edge_length * n / 2;
	denominator = dot(incoming.get_d(), n);
	numerator = dot(a - incoming.get_o(), n);
	if (denominator != 0)
	{
		first = numerator / denominator;
	}
	n = -forward;
	a = center + edge_length * n / 2;
	denominator = dot(incoming.get_d(), n);
	numerator = dot(a - incoming.get_o(), n);
	if (denominator == 0)
	{
		if (abs(dot(incoming.get_o() - center, n)) <= (edge_length / 2))
		{
			fb.SetInfinite();
		}
		else
		{
			fb.SetNan();
		}
	}
	else
	{
		second = numerator / denominator;
		fb.SetBottom(std::min(first, second));
		fb.SetTop(std::max(first, second));
		if (first < second)
		{
			fb_normal = forward;
		}
		else
		{
			fb_normal = -forward;
		}
	}

	// find the overlap of the intervals
	Interval inside;
	inside = OverlapInterval(tb, lr);
	inside = OverlapInterval(inside, fb);

	// determine normal vector
	if (tb.BottomInfinite())
	{
		if (lr.BottomInfinite())
		{
			info.normal = fb_normal;
		}
		else if (fb.BottomInfinite())
		{
			info.normal = lr_normal;
		}
		else if (lr.Get_Bottom() > fb.Get_Bottom())
		{
			info.normal = lr_normal;
		}
		else
		{
			info.normal = fb_normal;
		}
	}
	else if (lr.BottomInfinite())
	{
		if (tb.BottomInfinite())
		{
			info.normal = fb_normal;
		}
		else if (fb.BottomInfinite())
		{
			info.normal = tb_normal;
		}
		else if (tb.Get_Bottom() > fb.Get_Bottom())
		{
			info.normal = tb_normal;
		}
		else
		{
			info.normal = fb_normal;
		}
	}
	else if (fb.BottomInfinite())
	{
		if (lr.BottomInfinite())
		{
			info.normal = tb_normal;
		}
		else if (tb.BottomInfinite())
		{
			info.normal = lr_normal;
		}
		else if (lr.Get_Bottom() > tb.Get_Bottom())
		{
			info.normal = lr_normal;
		}
		else
		{
			info.normal = tb_normal;
		}
	}
	else if ((tb.Get_Bottom() > lr.Get_Bottom()) && (tb.Get_Bottom() > fb.Get_Bottom()))
	{
		info.normal = tb_normal;
	}
	else if ((lr.Get_Bottom() > fb.Get_Bottom()))
	{
		info.normal = lr_normal;
	}
	else
	{
		info.normal = fb_normal;
	}

	// determine if hit
	info.inside = inside;
	return Overlap(inside, length);
}



/***************************************\
*****************************************
**													**
**					Cylinder						**
**													**
*****************************************
\***************************************/



cylinder::cylinder()
{
	center.set(0.0, 0.0, 0.0);
	axis.set(0.0, 1.0, 0.0);
	height = 1.0;
	radius = 0.25;
	type = s_cylinder;
}


cylinder::cylinder(RGB new_color, vector3 new_center, vector3 new_axis, float new_height, float new_radius)
{
	color = new_color;
	center = new_center;
	axis = new_axis / length(new_axis);
	height = new_height;
	radius = new_radius;
	type = s_cylinder;
}


cylinder::~cylinder()
{
	// nothing to do
}


void cylinder::set(RGB new_color, vector3 new_center, vector3 new_axis, float new_height, float new_radius)
{
	color = new_color;
	center = new_center;
	axis = new_axis / length(new_axis);
	height = new_height;
	radius = new_radius;
}


bool cylinder::hit(Ray incoming, Interval where, surface& what, hit_info& info)
{
	what = *this;
	info.color = color;

	// find a plane perpendicular to the axis (o is the origin)
	vector3 x;
	vector3 y;
	if ((axis.get(0) < axis.get(1)) && (axis.get(0) < axis.get(2)))
	{
		x.set(0.0, axis.get(2), -axis.get(1));
	}
	else if (axis.get(1) < axis.get(2))
	{
		x.set(axis.get(2), 0.0, -axis.get(0));
	}
	else
	{
		x.set(axis.get(1), -axis.get(0), 0.0);
	}
	x = x / length(x);
	y = cross(x, axis);
	y = y / length(y);

	// project d and center onto the plane
	vector2 d2;
	vector2 c2;
	d2.set(dot(x, incoming.get_d()), dot(y, incoming.get_d()));
	c2.set(dot(x, center - incoming.get_o()), dot(y, center - incoming.get_o()));

	// find the intersection of the projected vector and the projected circle
	float A = dot(d2, d2);
	float B = dot(d2, -c2);
	float C = dot(-c2, -c2) - (radius * radius);
	float desc = (B * B) - (A * C);
	if (desc < epsilon)
	{
		info.inside.SetNan();
		return false;
	}
	float sqrtd = sqrt(desc);
	float first = (-B - sqrtd) / A;
	float second = (-B + sqrtd) / A;

	vector2 circle_normal;
	circle_normal = (d2 * first) - c2;

	// adjust back into 3d space
	Interval circle;
	if (length(d2) == 0)
	{
		if (length(c2) <= radius)
		{
			circle.SetInfinite();
		}
		else
		{
			circle.SetNan();
		}
	}
	else
	{
		circle.Set(std::min(first, second), std::max(first, second));
	}
	vector3 cyl_normal;
	cyl_normal = (x * circle_normal.get(0)) + (y * circle_normal.get(1));

	// find the intersection with the infinite slab
	Interval tb;
	vector3 n;
	vector3 a;
	float numerator;
	float denominator;
	n = axis;
	a = center + height * n / 2;
	denominator = dot(incoming.get_d(), n);
	numerator = dot(a - incoming.get_o(), n);
	if (denominator != 0)
	{
		first = numerator / denominator;
	}
	n = -axis;
	a = center + height * n / 2;
	denominator = dot(incoming.get_d(), n);
	numerator = dot(a - incoming.get_o(), n);
	if (denominator == 0)
	{
		if (abs(dot(incoming.get_o() - center, n)) <= (height / 2))
		{
			tb.SetInfinite();
		}
		else
		{
			tb.SetNan();
		}
	}
	else
	{
		second = numerator / denominator;
		tb.SetBottom(std::min(first, second));
		tb.SetTop(std::max(first, second));
	}
	vector3 slab_normal;
	if (first < second)
	{
		slab_normal = axis;
	}
	else
	{
		slab_normal = -axis;
	}

	// intersect the intersections
	info.inside = OverlapInterval(circle, tb);

	// get the normal
	if (circle.BottomInfinite())
	{
		info.normal = slab_normal;
	}
	else if (tb.BottomInfinite())
	{
		info.normal = cyl_normal;
	}
	else if (circle.Get_Bottom() > tb.Get_Bottom())
	{
		info.normal = cyl_normal;
	}
	else
	{
		info.normal = slab_normal;
	}

	info.normal = info.normal / length(info.normal);

	return Overlap(info.inside, where);
}



/***************************************\
*****************************************
**													**
**						Plane						**
**													**
*****************************************
\***************************************/


plane::plane()
{
	point.set(0.0, 0.0, 0.0);
	normal.set(0.0, 1.0, 0.0);
	type = s_plane;
}


plane::plane(RGB new_color, vector3 new_point, vector3 new_normal)
{
	color = new_color;
	point = new_point;
	normal = new_normal;
	type = s_plane;
}


plane::~plane()
{
	// nothing to do
}


void plane::set(RGB new_color, vector3 new_point, vector3 new_normal)
{
	color = new_color;
	point = new_point;
	normal = new_normal;
}


bool plane::hit(Ray incoming, Interval length, surface& what, hit_info& info)
{
	what = *this;
	info.color = color;
	info.normal = normal;

	float denominator;
	denominator = dot(incoming.get_d(), normal);
	if (denominator == 0)
	{
		return false;
	}
	float t;
	t = dot(point - incoming.get_o(), normal) / denominator;
	info.inside.Set(t, t);

	return Overlap(info.inside, length);
}



/***************************************\
*****************************************
**													**
**					Triangle						**
**													**
*****************************************
\***************************************/


triangle::triangle()
{
	a.set(1.0, 0.0, 0.0);
	b.set(0.0, 1.0, 0.0);
	c.set(0.0, 0.0, 1.0);
	type = s_triangle;
}


triangle::triangle(RGB new_color, vector3 new_a, vector3 new_b, vector3 new_c)
{
	color = new_color;
	a = new_a;
	b = new_b;
	c = new_c;
	type = s_triangle;
}


triangle::triangle(triangle& right)
{
	color = right.color;
	a = right.a;
	b = right.b;
	c = right.c;
	type = s_triangle;
}


triangle triangle::operator=(triangle& right)
{
	color = right.color;
	a = right.a;
	b = right.b;
	c = right.c;
	type = s_triangle;
	return *this;
}


triangle::~triangle()
{
	// nothing to do
}


void triangle::set(RGB new_color, vector3 new_a, vector3 new_b, vector3 new_c)
{
	color = new_color;
	a = new_a;
	b = new_b;
	c = new_c;
}


bool triangle::hit(Ray incoming, Interval where, surface& what, hit_info& info)
{
	what = *this;
	info.color = color;
	info.normal = cross(a - b, a - c);
	info.normal = info.normal / length(info.normal);


	vector3 d = incoming.get_d();
	vector3 o = incoming.get_o();

	float ei_minus_hf = ((a.get(1) - c.get(1)) * d.get(2)) - (d.get(1) * (a.get(2) - c.get(2)));
	float gf_minus_di = (d.get(0) * (a.get(2) - c.get(2))) - ((a.get(0) - c.get(0)) * d.get(2));
	float dh_minus_eg = ((a.get(0) - c.get(0)) * d.get(1)) - ((a.get(1) - c.get(1)) * d.get(0));
	float ak_minus_jb =
		 ((a.get(0) - b.get(0)) * (a.get(1) - o.get(1))) - ((a.get(0) - o.get(0)) * (a.get(1) - b.get(1)));
	float jc_minus_al =
		 ((a.get(0) - o.get(0)) * (a.get(2) - b.get(2))) - ((a.get(0) - b.get(0)) * (a.get(2) - o.get(2)));
	float bl_minus_kc =
		 ((a.get(1) - b.get(1)) * (a.get(2) - o.get(2))) - ((a.get(1) - o.get(1)) * (a.get(2) - b.get(2)));

	float M = ((a.get(0) - b.get(0)) * ei_minus_hf) + ((a.get(1) - b.get(1)) * gf_minus_di) +
				 ((a.get(2) - b.get(2)) * dh_minus_eg);
	float beta = (((a.get(0) - o.get(0)) * ei_minus_hf) + ((a.get(1) - o.get(1)) * gf_minus_di) +
						  ((a.get(2) - o.get(2)) * dh_minus_eg)) /
					 M;
	float gamma = ((d.get(2) * ak_minus_jb) + (d.get(1) * jc_minus_al) + (d.get(0) * bl_minus_kc)) / M;
	float t = (((a.get(2) - c.get(2)) * ak_minus_jb) + ((a.get(1) - c.get(1)) * jc_minus_al) +
					  ((a.get(0) - c.get(0)) * bl_minus_kc)) /
				 M;
	if ((beta > epsilon) && (gamma > epsilon) && (1 - beta - gamma > epsilon))
	{
		return true;
	}
	else
	{
		return false;
	}
}