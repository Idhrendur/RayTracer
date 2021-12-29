#ifndef PARSER_H_
#define PARSER_H_


#include <fstream>
#include <string>
#include "surface.h"

using namespace std;


void		parse				(char[], surface_list&, light&);
vector3	get_vector		(ifstream&);
RGB		get_RGB			(ifstream&);
sphere	get_sphere		(ifstream&);
cube		get_cube			(ifstream&);
cylinder	get_cylinder	(ifstream&);
plane		get_plane		(ifstream&);
triangle	get_triangle	(ifstream&);
light		get_light		(ifstream&);


#endif