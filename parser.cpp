#include "parser.h"


void parse(char filename[], surface_list& surfaces, light& sun)
{
	ifstream input;
	input.open(filename);
	string line;

	while (!input.eof())
	{
		input >> line;
		if (line == "sphere")
		{
			sphere ball = get_sphere(input);
			surfaces.add(&ball);
		}
		else if (line == "cube")
		{
			cube box = get_cube(input);
			surfaces.add(&box);
		}
		else if (line == "cylinder")
		{
			cylinder pipe = get_cylinder(input);
			surfaces.add(&pipe);
		}
		else if (line == "plane")
		{
			plane sheet = get_plane(input);
			surfaces.add(&sheet);
		}
		else if (line == "triangle")
		{
			triangle tri = get_triangle(input);
			surfaces.add(&tri);
		}
		else if (line == "light")
		{
			sun = get_light(input);
		}
	}

	input.close();
}


vector3 get_vector(ifstream& input)
{
	float x, y, z;
	input >> x >> y >> z;
	vector3 the_vector(x, y, z);
	return the_vector;
}


RGB get_RGB(ifstream& input)
{
	float R, G, B;
	input >> R >> G >> B;
	RGB the_RGB(R, G, B);
	return the_RGB;
}


sphere get_sphere(ifstream& input)
{
	RGB color = get_RGB(input);
	vector3 center = get_vector(input);
	float radius;
	input >> radius;
	sphere the_sphere(color, center, radius);
	return the_sphere;
}


cube get_cube(ifstream& input)
{
	RGB color = get_RGB(input);
	vector3 center = get_vector(input);
	float edge_length;
	input >> edge_length;
	vector3 up = get_vector(input);
	vector3 right = get_vector(input);
	vector3 forward = get_vector(input);
	cube the_cube(color, center, edge_length, up, right, forward);
	return the_cube;
}


cylinder get_cylinder(ifstream& input)
{
	RGB color = get_RGB(input);
	vector3 center = get_vector(input);
	vector3 axis = get_vector(input);
	float height;
	input >> height;
	float radius;
	input >> radius;
	cylinder the_cylinder(color, center, axis, height, radius);
	return the_cylinder;
}


plane get_plane(ifstream& input)
{
	RGB color = get_RGB(input);
	vector3 point = get_vector(input);
	vector3 normal = get_vector(input);
	plane the_plane(color, point, normal);
	return the_plane;
}


triangle get_triangle(ifstream& input)
{
	RGB color = get_RGB(input);
	vector3 a = get_vector(input);
	vector3 b = get_vector(input);
	vector3 c = get_vector(input);
	triangle the_triangle(color, a, b, c);
	return the_triangle;
}


light get_light(ifstream& input)
{
	RGB color = get_RGB(input);
	vector3 direction = get_vector(input);
	light the_light;
	the_light.color = color;
	the_light.direction = direction;
	return the_light;
}