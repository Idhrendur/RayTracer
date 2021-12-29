#ifndef RENDER_H_
#define RENDER_H_


#include "surface.h"
#include <iostream>

using namespace std;



image render(int width, int height, surface_list surfaces, light sun);
RGB color(Ray sighting);
bool shadow(vector3 point);

#endif