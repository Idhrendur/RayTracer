#include <cstdlib>
#include <iostream>
//#include "bases.h"
#include "surface.h"
#include "render.h"
#include "parser.h"

using namespace std;

int main(int argc, char *argv[]) {
	surface_list surfaces;
	light sun;
	parse("surfaces.txt", surfaces, sun);
	/*vector3 center(50.0, -80.0, -1000);
	RGB gray(0.5, 0.5, 0.5);
	sphere big(gray, center, 100);
	center.set(50.0, 50.0, -950);
	sphere small(gray, center, 30);
	surfaces.add(&big);
	surfaces.add(&small);
*/
	image rendered;

//	light sun;
//	sun.color.set(1.0, 1.0, 1.0);
//	sun.direction.set(0.0, -1.0, 0.0);*/

	rendered = render(100, 100, surfaces, sun);
	rendered.save("yes.bmp");

	return EXIT_SUCCESS;
}
