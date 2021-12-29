#ifndef SURFACE_H_
#define SURFACE_H_


#include <algorithm>
#include <list>
#include <iostream>
#include "bases.h"

using namespace std;


const double epsilon = 0.01;


struct hit_info {
	Interval inside;
	RGB		color;
	vector3	normal;
};


enum surface_type {
	nothing,
	s_list,
	s_sphere,
	s_cube,
	s_cylinder,
	s_plane,
	s_triangle
};


class surface {
	public:
		surface();
		surface operator =(surface&);
		virtual ~surface	();
		virtual bool hit	(Ray, Interval, surface&, hit_info&);
		surface_type		get_type();
	protected:
		surface_type	type;
		RGB				color;
};


class surface_list: public surface {
	public:
		surface_list			();
		surface_list			(surface_list&);
		surface_list operator = (surface_list&);
		~surface_list			();
		void add					(surface*);
		void clear				();
		bool hit					(Ray, Interval, surface&, hit_info&);
	private:
		std::vector<surface*>	surfaces;
};


class sphere: public surface {
	public:
		sphere	();
		sphere	(RGB, vector3, float);
		sphere	(sphere&);
		sphere operator = (sphere&);
		~sphere	();
		void set	(RGB, vector3, float);
		bool hit	(Ray, Interval, surface&, hit_info&);
	private:
		vector3	center;
		float		radius;
};


class cube: public surface {
	public:
		cube		();
		cube		(RGB, vector3, float, vector3, vector3, vector3);
		~cube		();
		void set	(RGB, vector3, float, vector3, vector3, vector3);
		bool hit	(Ray, Interval, surface&, hit_info&);
	private:
		vector3	center;
		float		edge_length;
		vector3	up;
		vector3	right;
		vector3	forward;
};


class cylinder: public surface {
	public:
		cylinder		();
		cylinder		(RGB, vector3, vector3, float, float);
		~cylinder	();
		void set		(RGB, vector3, vector3, float, float);
		bool hit		(Ray, Interval, surface&, hit_info&);
	private:
		vector3		center;
		vector3		axis;
		float			height;
		float			radius;
};


class plane: public surface {
	public:
		plane			();
		plane			(RGB, vector3, vector3);
		~plane		();
		void set		(RGB, vector3, vector3);
		bool hit		(Ray, Interval, surface&, hit_info&);
	private:
		vector3		point;
		vector3		normal;
};


class triangle: public surface {
	public:
		triangle		();
		triangle		(RGB, vector3, vector3, vector3);
		triangle		(triangle&);
		triangle operator = (triangle&);		
		~triangle	();
		void set		(RGB, vector3, vector3, vector3);
		bool hit		(Ray, Interval, surface&, hit_info&);
	private:
		vector3		a;
		vector3		b;
		vector3		c;
};



#endif