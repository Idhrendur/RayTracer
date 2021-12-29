#ifndef BASES_H_
#define BASES_H_


#include <fstream>
#include <math.h>
#include <string>
#include <vector>


#define DEFAULT_WIDTH 320
#define DEFAULT_HEIGHT 240

#undef RGB



class RGB
{
  public:
	RGB();
	~RGB();
	RGB(float, float, float);
	void set(float, float, float);
	RGB operator+();
	RGB operator-();
	friend RGB operator*(float, RGB);
	RGB operator*(float);
	RGB operator/(float);
	RGB operator+(RGB&);
	RGB operator-(RGB&);
	RGB operator*(RGB&);
	RGB operator/(RGB&);
	float Get_Red();
	float Get_Green();
	float Get_Blue();

  private:
	float Red;
	float Green;
	float Blue;
};



class image
{
  public:
	image();
	image(int, int);
	~image();
	void change_size(int, int);
	void set(int, int, RGB);
	RGB check(int, int);
	void save(std::string);

  private:
	std::vector<RGB> pixels;
	int width;
	int height;
};



struct bitmapfileheader
{
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
};



struct bitmapinfoheader
{
	unsigned int biSize;
	unsigned int biWidth;
	unsigned int biHeight;
	unsigned short biPlanes;
	unsigned short bitBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	unsigned int biXPelsPerMeter;
	unsigned int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
};



class vector3
{
  public:
	vector3();
	~vector3();
	vector3(float, float, float);
	void set(float, float, float);
	void set(int, float);
	float get(int);
	friend float length(vector3);
	friend float length_square(vector3);
	vector3 operator+();
	vector3 operator-();
	friend vector3 operator*(float, vector3);
	vector3 operator*(float);
	vector3 operator/(float);
	vector3 operator+(vector3);
	vector3 operator-(vector3);
	friend float dot(vector3, vector3);
	friend vector3 cross(vector3, vector3);

  private:
	std::vector<float> coords;
};


class vector2
{
  public:
	vector2();
	~vector2();
	vector2(float, float);
	void set(float, float);
	void set(int, float);
	float get(int);
	friend float length(vector2);
	friend float length_square(vector2);
	vector2 operator+();
	vector2 operator-();
	friend vector2 operator*(float, vector2);
	vector2 operator*(float);
	vector2 operator/(float);
	vector2 operator+(vector2);
	vector2 operator-(vector2);
	friend float dot(vector2, vector2);
	// friend vector2 cross		(vector2, vector2);
  private:
	std::vector<float> coords;
};


class Ray
{
  public:
	Ray();
	~Ray();
	Ray(vector3, vector3);
	void Set(vector3, vector3);
	vector3 PointAt(float);
	vector3 get_o();
	vector3 get_d();

  private:
	vector3 o;
	vector3 d;
};


class Interval
{
  public:
	Interval();
	~Interval();
	void Set(float, float);
	void SetInfinite();
	void SetNan();
	void SetBottom(float);
	void SetBottomInfinite();
	void SetTop(float);
	void SetTopInfinite();
	float Get_Top();
	float Get_Bottom();
	bool BottomInfinite();
	bool TopInfinite();
	bool InInterval(float);
	bool Valid();
	friend bool Overlap(Interval, Interval);
	friend Interval OverlapInterval(Interval, Interval);

  private:
	float bottom;
	bool bottom_valid;
	bool bottom_infinite;
	float top;
	bool top_valid;
	bool top_infinite;
};


class ONB
{
  public:
	ONB();
	~ONB();
	void construct_from_uv(vector3, vector3);
	void construct_from_uw(vector3, vector3);
	void construct_from_vu(vector3, vector3);
	void construct_from_vw(vector3, vector3);
	void construct_from_wu(vector3, vector3);
	void construct_from_wv(vector3, vector3);
	void construct_from_w(vector3);
	vector3 get_u();
	vector3 get_v();
	vector3 get_w();
	vector3 convert_to_canon(vector3);
	vector3 convert_from_canon(vector3);

  private:
	vector3 u;
	vector3 v;
	vector3 w;
};


class Frame
{
  public:
	Frame();
	Frame(ONB, vector3);
	~Frame();
	void construct(ONB, vector3);
	vector3 get_origin();
	ONB get_ONB();

  private:
	vector3 origin;
	ONB coord_system;
};


class Trans_Matrix
{
  public:
	Trans_Matrix();
	~Trans_Matrix();
	void Identity();
	void Translate(vector3);
	void Scale(float, float, float);
	void Rotate_x(float);
	void Rotate_y(float);
	void Rotate_z(float);
	vector3 point(vector3);
	vector3 reverse_point(vector3);
	vector3 vector(vector3);
	vector3 reverse_vector(vector3);
	vector3 normal(vector3);
	vector3 reverse_normal(vector3);

  private:
	float M[4][4];
	float N[4][4];
};


struct light
{
	vector3 direction;
	RGB color;
};



#endif // BASES_H_
