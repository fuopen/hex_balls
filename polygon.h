#ifndef polygon_H_
#define polygon_H_
#include<cstdio>
#include<cstdlib>
#include<cstring>

typedef float POINT3D[3];
typedef float* FP;
typedef unsigned* UIP;
typedef int* IP;

class polygon{
	private:
		UIP p_vtx;
		int size;
	public:
		polygon():p_vtx(NULL){}
		polygon(const int& len):size(len),p_vtx((UIP)malloc(sizeof(unsigned)*len)){
			memset(p_vtx,0,sizeof(unsigned)*len);
		}
		~polygon(){
			if(p_vtx!=NULL)free(p_vtx);
		}
		polygon& operator =(const polygon& cp_p){
			if(this==&cp_p) return *this;
			else{
				if(p_vtx!=NULL) free(p_vtx);
				p_vtx = (UIP)malloc(sizeof(unsigned)*cp_p.size);
				memcpy(p_vtx,cp_p.p_vtx,sizeof(unsigned)*cp_p.size);
				size = cp_p.size;
			}
			return *this;
		}
		unsigned& operator [](const unsigned& index){
			return p_vtx[index];
		}
		unsigned  operator [](const unsigned& index)const{
			return p_vtx[index];
		}
		int get_size()const{
			return size;
		}
};

#endif
