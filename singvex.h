#ifndef _SINGVEX_H_
#define _SINGVEX_H_
//#include<GL/glut.h>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#define PI 3.141593
#include"polygon.h"

class singvex{
	private:
		POINT3D simplex[14];
		polygon *polg[18];
		POINT3D sip_norm[14];
		static unsigned int polg_index;
	public:
		singvex();
		~singvex();
		singvex(const singvex&);
		singvex& operator = (const singvex&);
		void create_singvex();
		void create_polygon();
		void create_polnorm();
		void outer_product(float*,float*,float*);
		void rotate_matrix(float* ,const float&,const int&);
		inline float get_sp(const int& i,const int& j)const{ return simplex[i][j];}
		inline unsigned get_pg(const int& i, const int& j)const { return (*polg[i])[j];}
		inline float get_sm(const int& i,const int& j)const{ return sip_norm[i][j];}
		void shift_pos(const POINT3D);
		void print()const;
};
#endif
