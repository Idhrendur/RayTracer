#include "bases.h"



/***************************************\
*****************************************
**													**
**						RGB						**
**													**
*****************************************
\***************************************/


RGB::RGB()
{
	Red = 0;
	Green = 0;
	Blue = 0;
}


RGB::~RGB()
{
	// nothing to do
}


RGB::RGB(float R, float G, float B)
{
	Red = R;
	Green = G;
	Blue = B;
}


void RGB::set(float new_Red, float new_Green, float new_Blue)
{
	Red = new_Red;
	Green = new_Green;
	Blue = new_Blue;
}


RGB RGB::operator+()
{
	RGB return_me;
	return_me = *this;
	return return_me;
}


RGB RGB::operator-()
{
	RGB return_me;
	return_me.set(-Red, -Green, -Blue);
	return return_me;
}


RGB operator*(float k, RGB a)
{
	RGB return_me;
	return_me.set(k * a.Red, k * a.Green, k * a.Blue);
	return return_me;
}


RGB RGB::operator*(float k)
{
	RGB return_me;
	return_me.set(Red * k, Green * k, Blue * k);
	return return_me;
}


RGB RGB::operator/(float k)
{
	RGB return_me;
	return_me.set(Red / k, Green / k, Blue / k);
	return return_me;
}


RGB RGB::operator+(RGB& b)
{
	RGB return_me;
	return_me.set(Red + b.Red, Green + b.Green, Blue + b.Blue);
	return return_me;
}


RGB RGB::operator-(RGB& b)
{
	RGB return_me;
	return_me.set(Red - b.Red, Green - b.Green, Blue - b.Blue);
	return return_me;
}


RGB RGB::operator*(RGB& b)
{
	RGB return_me;
	return_me.set(Red * b.Red, Green * b.Green, Blue * b.Blue);
	return return_me;
}


RGB RGB::operator/(RGB& b)
{
	RGB return_me;
	return_me.set(Red / b.Red, Green / b.Green, Blue / b.Blue);
	return return_me;
}


float RGB::Get_Red()
{
	return Red;
}


float RGB::Get_Green()
{
	return Green;
}


float RGB::Get_Blue()
{
	return Blue;
}



/***************************************\
*****************************************
**													**
**						Image						**
**													**
*****************************************
\***************************************/


image::image()
{
	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT;
	pixels.resize(width * height);
}


image::image(int new_width, int new_height)
{
	width = new_width;
	height = new_height;
	pixels.resize(width * height);
}


image::~image()
{
	pixels.clear();
}


void image::change_size(int new_width, int new_height)
{
	width = new_width;
	height = new_height;
	pixels.resize(width * height);
}


void image::set(int x, int y, RGB color)
{
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > width - 1)
		x = width - 1;
	if (y > height - 1)
		y = height - 1;
	pixels[y * width + x] = color;
}


RGB image::check(int x, int y)
{
	RGB color;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > width - 1)
		x = width - 1;
	if (y > height - 1)
		y = height - 1;
	color = pixels[y * width + x];
	return color;
}


void image::save(std::string filename)
{
	bitmapfileheader fheader;
	bitmapinfoheader iheader;
	unsigned short bfType;

	bfType = 0x4D42;

	fheader.bfReserved1 = 0;
	fheader.bfReserved2 = 0;
	fheader.bfOffBits = 54;

	iheader.biSize = 40;
	iheader.biPlanes = 1;
	iheader.bitBitCount = 24;
	iheader.biCompression = 0;
	iheader.biXPelsPerMeter = 0;
	iheader.biYPelsPerMeter = 0;
	iheader.biClrUsed = 0;
	iheader.biClrImportant = 0;

	int output_width = width;
	if (width % 4 != 0)
		output_width += 4 - width % 4;
	iheader.biSizeImage = output_width * height * 3;
	iheader.biWidth = output_width;
	iheader.biHeight = height;
	fheader.bfSize = iheader.biSizeImage + 54;

	std::ofstream file;
	file.open(filename.c_str(), std::ios::binary);
	file.write(reinterpret_cast<const char*>(&bfType), sizeof(bfType));
	file.write(reinterpret_cast<const char*>(&fheader), sizeof(fheader));
	file.write(reinterpret_cast<const char*>(&iheader), sizeof(iheader));
	RGB pixel;
	unsigned char output;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < output_width; ++x)
		{
			pixel = check(x, y);
			output = static_cast<char>(255 * pixel.Get_Blue());
			file.write(reinterpret_cast<const char*>(&output), sizeof(output));
			output = static_cast<char>(255 * pixel.Get_Green());
			file.write(reinterpret_cast<const char*>(&output), sizeof(output));
			output = static_cast<char>(255 * pixel.Get_Red());
			file.write(reinterpret_cast<const char*>(&output), sizeof(output));
		}
	}
	file.close();
}



/***************************************\
*****************************************
**													**
**						Vector3					**
**													**
*****************************************
\***************************************/


vector3::vector3()
{
	coords.resize(3, 0.0);
}


vector3::~vector3()
{
	coords.clear();
}


vector3::vector3(float x, float y, float z)
{
	coords.resize(3, 0.0);
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;
}


void vector3::set(float x, float y, float z)
{
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;
}


void vector3::set(int element, float value)
{
	if (element < 3 && element > -1)
		coords[element] = value;
}


float vector3::get(int element)
{
	if (element <= 2 && element >= 0)
		return coords[element];
	else
		return 0;
}


float length(vector3 a)
{
	return sqrt(length_square(a));
}


float length_square(vector3 a)
{
	return (pow(a.coords[0], 2) + pow(a.coords[1], 2) + pow(a.coords[2], 2));
}


vector3 vector3::operator+()
{
	vector3 return_me;
	return_me = *this;
	return return_me;
}


vector3 vector3::operator-()
{
	vector3 return_me(-coords[0], -coords[1], -coords[2]);
	return return_me;
}


vector3 operator*(float k, vector3 a)
{
	vector3 return_me(k * a.coords[0], k * a.coords[1], k * a.coords[2]);
	return return_me;
}


vector3 vector3::operator*(float k)
{
	vector3 return_me(k * coords[0], k * coords[1], k * coords[2]);
	return return_me;
}


vector3 vector3::operator/(float k)
{
	vector3 return_me(coords[0] / k, coords[1] / k, coords[2] / k);
	return return_me;
}


vector3 vector3::operator+(vector3 b)
{
	vector3 return_me(coords[0] + b.get(0), coords[1] + b.get(1), coords[2] + b.get(2));
	return return_me;
}


vector3 vector3::operator-(vector3 b)
{
	vector3 return_me(coords[0] - b.get(0), coords[1] - b.get(1), coords[2] - b.get(2));
	return return_me;
}


float dot(vector3 a, vector3 b)
{
	float return_me;
	return_me = a.get(0) * b.get(0);
	return_me += a.get(1) * b.get(1);
	return_me += a.get(2) * b.get(2);
	return return_me;
}


vector3 cross(vector3 a, vector3 b)
{
	vector3 return_me;
	return_me.set(0, a.coords[1] * b.coords[2] - a.coords[2] * b.coords[1]);
	return_me.set(1, a.coords[2] * b.coords[0] - a.coords[0] * b.coords[2]);
	return_me.set(2, a.coords[0] * b.coords[1] - a.coords[1] * b.coords[0]);
	return return_me;
}



/***************************************\
*****************************************
**													**
**						Vector2					**
**													**
*****************************************
\***************************************/


vector2::vector2()
{
	coords.resize(2, 0.0);
}


vector2::~vector2()
{
	coords.clear();
}


vector2::vector2(float x, float y)
{
	coords.resize(2, 0.0);
	coords[0] = x;
	coords[1] = y;
}


void vector2::set(float x, float y)
{
	coords[0] = x;
	coords[1] = y;
}


void vector2::set(int element, float value)
{
	if (element < 2 && element > -1)
		coords[element] = value;
}


float vector2::get(int element)
{
	if (element < 2 && element >= 0)
		return coords[element];
	else
		return 0;
}


float length(vector2 a)
{
	return sqrt(length_square(a));
}


float length_square(vector2 a)
{
	return (pow(a.coords[0], 2) + pow(a.coords[1], 2));
}


vector2 vector2::operator+()
{
	vector2 return_me;
	return_me = *this;
	return return_me;
}


vector2 vector2::operator-()
{
	vector2 return_me(-coords[0], -coords[1]);
	return return_me;
}


vector2 operator*(float k, vector2 a)
{
	vector2 return_me(k * a.coords[0], k * a.coords[1]);
	return return_me;
}


vector2 vector2::operator*(float k)
{
	vector2 return_me(k * coords[0], k * coords[1]);
	return return_me;
}


vector2 vector2::operator/(float k)
{
	vector2 return_me(coords[0] / k, coords[1] / k);
	return return_me;
}


vector2 vector2::operator+(vector2 b)
{
	vector2 return_me(coords[0] + b.get(0), coords[1] + b.get(1));
	return return_me;
}


vector2 vector2::operator-(vector2 b)
{
	vector2 return_me(coords[0] - b.get(0), coords[1] - b.get(1));
	return return_me;
}


float dot(vector2 a, vector2 b)
{
	float return_me;
	return_me = a.get(0) * b.get(0);
	return_me += a.get(1) * b.get(1);
	return return_me;
}


vector2 cross(vector2 a)
{
	vector2 return_me;
	return_me.set(0, -a.get(1));
	return_me.set(1, a.get(0));
	return return_me;
}



/***************************************\
*****************************************
**													**
**						Ray						**
**													**
*****************************************
\***************************************/


Ray::Ray()
{
	o.set(0.0f, 0.0f, 0.0f);
	d.set(0.0f, 0.0f, 0.0f);
}


Ray::~Ray()
{
	// nothing to do
}


Ray::Ray(vector3 new_o, vector3 new_d)
{
	o = new_o;
	d = new_d;
}


void Ray::Set(vector3 new_o, vector3 new_d)
{
	o = new_o;
	d = new_d;
}


vector3 Ray::PointAt(float t)
{
	return o + t * d;
}


vector3 Ray::get_o()
{
	return o;
}


vector3 Ray::get_d()
{
	return d;
}



/***************************************\
*****************************************
**													**
**					Interval						**
**													**
*****************************************
\***************************************/


Interval::Interval()
{
	bottom = 0.0;
	bottom_valid = false;
	bottom_infinite = false;
	top = 0.0;
	top_valid = false;
	top_infinite = false;
}


Interval::~Interval()
{
	// nothing to do
}


void Interval::Set(float new_bottom, float new_top)
{
	if (new_bottom <= new_top)
	{
		bottom = new_bottom;
		bottom_valid = true;
		bottom_infinite = false;
		top = new_top;
		top_valid = true;
		top_infinite = false;
	}
	else
	{
		bottom_valid = false;
		top_valid = false;
	}
}


void Interval::SetInfinite()
{
	bottom_valid = true;
	bottom_infinite = true;
	top_valid = true;
	top_infinite = true;
}


void Interval::SetNan()
{
	bottom_valid = false;
	top_valid = false;
}


void Interval::SetBottom(float new_bottom)
{
	bottom = new_bottom;
	bottom_valid = true;
	bottom_infinite = false;
}


void Interval::SetBottomInfinite()
{
	bottom_infinite = true;
	bottom_valid = true;
}


void Interval::SetTop(float new_top)
{
	top = new_top;
	top_valid = true;
	top_infinite = false;
}


void Interval::SetTopInfinite()
{
	top_infinite = true;
	top_valid = true;
}


float Interval::Get_Bottom()
{
	return bottom;
}


float Interval::Get_Top()
{
	return top;
}


bool Interval::BottomInfinite()
{
	return bottom_infinite;
}


bool Interval::TopInfinite()
{
	return top_infinite;
}


bool Interval::InInterval(float value)
{
	if (!top_valid || !bottom_valid)
	{
		return false;
	}
	if (top_infinite && bottom_infinite)
	{
		return true;
	}
	if (top_infinite && (value >= bottom))
	{
		return true;
	}
	if (bottom_infinite && (value <= top))
	{
		return true;
	}
	if ((value >= bottom) && (value <= top))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Interval::Valid()
{
	if (top_valid && bottom_valid)
		return true;
	else
		return false;
}


bool Overlap(Interval first, Interval second)
{
	if (!first.bottom_valid || !first.top_valid || !second.bottom_valid || !second.top_valid)
	{
		return false;
	}
	if ((first.bottom_infinite && first.top_infinite) || (second.top_infinite && second.bottom_infinite))
	{
		return true;
	}
	if (first.bottom_infinite && (second.bottom <= first.top))
	{
		return true;
	}
	if (second.bottom_infinite && (first.bottom <= second.top))
	{
		return true;
	}
	if (first.top_infinite && (second.top >= first.bottom))
	{
		return true;
	}
	if (second.top_infinite && (first.top >= second.bottom))
	{
		return true;
	}
	if (second.bottom < first.bottom)
	{
		if (first.bottom < second.top)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (second.bottom < first.top)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}


Interval OverlapInterval(Interval first, Interval second)
{
	Interval return_me;
	if (!Overlap(first, second))
	{
		return_me.SetNan();
	}
	else
	{
		if (first.bottom_infinite && second.bottom_infinite)
		{
			return_me.SetBottomInfinite();
		}
		if (first.top_infinite && second.top_infinite)
		{
			return_me.SetTopInfinite();
		}
		if (first.bottom_infinite && !second.bottom_infinite)
		{
			return_me.SetBottom(second.bottom);
		}
		if (second.bottom_infinite && !first.bottom_infinite)
		{
			return_me.SetBottom(first.bottom);
		}
		if (first.top_infinite && !second.top_infinite)
		{
			return_me.SetTop(second.top);
		}
		if (second.top_infinite && !first.top_infinite)
		{
			return_me.SetTop(first.top);
		}
		if (!first.bottom_infinite && !first.top_infinite && !second.top_infinite && !second.bottom_infinite)
		{
			if (second.bottom < first.bottom)
			{
				return_me.SetBottom(first.bottom);
			}
			else
			{
				return_me.SetBottom(second.bottom);
			}
			if (second.top < first.top)
			{
				return_me.SetTop(second.top);
			}
			else
			{
				return_me.SetTop(first.top);
			}
		}
	}
	return return_me;
}



/***************************************\
*****************************************
**													**
**						ONB						**
**													**
*****************************************
\***************************************/


ONB::ONB()
{
	u.set(1.0, 0.0, 0.0);
	v.set(0.0, 1.0, 0.0);
	w.set(0.0, 0.0, 1.0);
}


ONB::~ONB()
{
	// nothing to do
}


void ONB::construct_from_uv(vector3 a, vector3 b)
{
	u = a / length(a);
	w = cross(a, b) / length(cross(a, b));
	v = cross(w, u);
}


void ONB::construct_from_uw(vector3 a, vector3 b)
{
	u = a / length(a);
	v = cross(a, b) / length(cross(a, b));
	w = cross(w, u);
}


void ONB::construct_from_vu(vector3 a, vector3 b)
{
	v = a / length(a);
	w = cross(a, b) / length(cross(a, b));
	u = cross(w, u);
}


void ONB::construct_from_vw(vector3 a, vector3 b)
{
	v = a / length(a);
	u = cross(a, b) / length(cross(a, b));
	w = cross(w, u);
}


void ONB::construct_from_wu(vector3 a, vector3 b)
{
	w = a / length(a);
	v = cross(a, b) / length(cross(a, b));
	u = cross(w, u);
}


void ONB::construct_from_wv(vector3 a, vector3 b)
{
	w = a / length(a);
	u = cross(a, b) / length(cross(a, b));
	v = cross(w, u);
}


void ONB::construct_from_w(vector3 a)
{
	w = a / length(a);
	if (a.get(0) < a.get(1) && a.get(0) < a.get(2))
	{
		v.set(0.0, w.get(2), -w.get(1));
		v = v / length(v);
	}
	else if (a.get(1) < a.get(2))
	{
		v.set(w.get(2), 0.0, -w.get(0));
		v = v / length(v);
	}
	else
	{
		v.set(w.get(1), -w.get(0), 0.0);
		v = v / length(v);
	}
	u = cross(v, w);
}


vector3 ONB::convert_from_canon(vector3 a)
{
	vector3 return_me;
	return_me.set(0, dot(a, u));
	return_me.set(1, dot(a, v));
	return_me.set(2, dot(a, w));
	return return_me;
}


vector3 ONB::convert_to_canon(vector3 a)
{
	vector3 return_me;
	return_me = a.get(0) * u + a.get(1) * v + a.get(2) * w;
	return return_me;
}



/***************************************\
*****************************************
**													**
**						Frame						**
**													**
*****************************************
\***************************************/


Frame::Frame()
{
	// default constructors for the components do the work
}


Frame::Frame(ONB new_coords, vector3 new_origin)
{
	coord_system = new_coords;
	origin = new_origin;
}


Frame::~Frame()
{
	// nothing to do
}


void Frame::construct(ONB new_coords, vector3 new_origin)
{
	coord_system = new_coords;
	origin = new_origin;
}


vector3 Frame::get_origin()
{
	return origin;
}


ONB Frame::get_ONB()
{
	return coord_system;
}



/***************************************\
*****************************************
**													**
**					Trans Matrix				**
**													**
*****************************************
\***************************************/


Trans_Matrix::Trans_Matrix()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			M[i][j] = 0;
			N[i][j] = 0;
		}
	}
}


Trans_Matrix::~Trans_Matrix()
{
	// nothing to do
}


void Trans_Matrix::Identity()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == j)
			{
				M[i][j] = 1;
				N[i][j] = 1;
			}
			else
			{
				M[i][j] = 0;
				N[i][j] = 0;
			}
		}
	}
}


void Trans_Matrix::Translate(vector3 t)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (i == j)
			{
				M[i][j] = 1;
				N[i][j] = 1;
			}
			else
			{
				M[i][j] = 0;
				N[i][j] = 0;
			}
		}
	}
	M[0][3] = t.get(0);
	N[0][3] = -t.get(0);
	M[1][3] = t.get(1);
	N[1][3] = -t.get(1);
	M[2][3] = t.get(2);
	N[2][3] = -t.get(2);
	M[3][3] = 1;
	N[3][3] = 1;
}


void Trans_Matrix::Scale(float x, float y, float z)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == j)
			{
				switch (i)
				{
					case 0:
						M[i][j] = x;
						N[i][j] = 1 / x;
						break;
					case 1:
						M[i][j] = y;
						N[i][j] = 1 / y;
						break;
					case 2:
						M[i][j] = z;
						N[i][j] = 1 / z;
						break;
					default:
						M[i][j] = 1;
						N[i][j] = 1;
				}
			}
			else
			{
				M[i][j] = 0;
				N[i][j] = 0;
			}
		}
	}
}


void Trans_Matrix::Rotate_x(float theta)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == j)
			{
				M[i][j] = 1;
				N[i][j] = 1;
			}
			else
			{
				M[i][j] = 0;
				N[i][j] = 0;
			}
		}
	}
	M[1][1] = M[2][2] = N[1][1] = N[2][2] = cos(theta);
	M[2][1] = N[1][2] = sin(theta);
	M[1][2] = N[2][1] = -sin(theta);
}


void Trans_Matrix::Rotate_y(float theta)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == j)
			{
				M[i][j] = 1;
				N[i][j] = 1;
			}
			else
			{
				M[i][j] = 0;
				N[i][j] = 0;
			}
		}
	}
	M[0][0] = M[2][2] = N[0][0] = N[2][2] = cos(theta);
	M[0][2] = N[2][0] = sin(theta);
	M[2][0] = N[0][2] = -sin(theta);
}
void Trans_Matrix::Rotate_z(float theta)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == j)
			{
				M[i][j] = 1;
				N[i][j] = 1;
			}
			else
			{
				M[i][j] = 0;
				N[i][j] = 0;
			}
		}
	}
	M[0][0] = M[1][1] = N[0][0] = N[1][1] = cos(theta);
	M[1][0] = N[0][1] = sin(theta);
	M[0][1] = N[1][0] = -sin(theta);
}


vector3 Trans_Matrix::point(vector3 p)
{
	vector3 return_me;
	return_me.set(0, M[0][0] * p.get(0) + M[0][1] * p.get(1) + M[0][2] * p.get(2) + M[0][3]);
	return_me.set(1, M[1][0] * p.get(0) + M[1][1] * p.get(1) + M[1][2] * p.get(2) + M[1][3]);
	return_me.set(2, M[2][0] * p.get(0) + M[2][1] * p.get(1) + M[2][2] * p.get(2) + M[2][3]);
	return return_me;
}


vector3 Trans_Matrix::reverse_point(vector3 p)
{
	vector3 return_me;
	return_me.set(0, N[0][0] * p.get(0) + N[0][1] * p.get(1) + N[0][2] * p.get(2) + N[0][3]);
	return_me.set(1, N[1][0] * p.get(0) + N[1][1] * p.get(1) + N[1][2] * p.get(2) + N[1][3]);
	return_me.set(2, N[2][0] * p.get(0) + N[2][1] * p.get(1) + N[2][2] * p.get(2) + N[2][3]);
	return return_me;
}


vector3 Trans_Matrix::vector(vector3 v)
{
	vector3 return_me;
	return_me.set(0, M[0][0] * v.get(0) + M[0][1] * v.get(1) + M[0][2] * v.get(2));
	return_me.set(1, M[1][0] * v.get(0) + M[1][1] * v.get(1) + M[1][2] * v.get(2));
	return_me.set(2, M[2][0] * v.get(0) + M[2][1] * v.get(1) + M[2][2] * v.get(2));
	return return_me;
}


vector3 Trans_Matrix::reverse_vector(vector3 v)
{
	vector3 return_me;
	return_me.set(0, N[0][0] * v.get(0) + N[0][1] * v.get(1) + N[0][2] * v.get(2));
	return_me.set(1, N[1][0] * v.get(0) + N[1][1] * v.get(1) + N[1][2] * v.get(2));
	return_me.set(2, N[2][0] * v.get(0) + N[2][1] * v.get(1) + N[2][2] * v.get(2));
	return return_me;
}


vector3 Trans_Matrix::normal(vector3 n)
{
	vector3 return_me;
	return_me.set(0, N[0][0] * n.get(0) + N[0][1] * n.get(1) + N[0][2] * n.get(2));
	return_me.set(1, N[1][0] * n.get(0) + N[1][1] * n.get(1) + N[1][2] * n.get(2));
	return_me.set(2, N[2][0] * n.get(0) + N[2][1] * n.get(1) + N[2][2] * n.get(2));
	return return_me;
}


vector3 Trans_Matrix::reverse_normal(vector3 n)
{
	vector3 return_me;
	return_me.set(0, M[0][0] * n.get(0) + M[0][1] * n.get(1) + M[0][2] * n.get(2));
	return_me.set(1, M[1][0] * n.get(0) + M[1][1] * n.get(1) + M[1][2] * n.get(2));
	return_me.set(2, M[2][0] * n.get(0) + M[2][1] * n.get(1) + M[2][2] * n.get(2));
	return return_me;
};
