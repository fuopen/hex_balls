#include"singvex.h"

unsigned int singvex::polg_index=0;

singvex::singvex(){
	for(unsigned i=0;i<18;i++)
		polg[i] = NULL;
	for(int i=0;i<14;i++){
		for(int j=0;j<3;j++){
			simplex[i][j] = 0.0;
			sip_norm[i][j]= 0.0;
		}
	}
	polg_index += 18;
	create_singvex();
}

singvex::~singvex(){
	(polg_index>0)? polg_index -=18:0;
	for(int i=0;i<18;i++) if(polg[i]!=NULL) delete polg[i];
}

singvex::singvex(const singvex& cp_svx){
	polg_index +=18;
	for(int i=0;i<14;i++)
		for(int j=0;j<3;j++)
			simplex[i][j] = cp_svx.simplex[i][j];		
	for(int i=0;i<18;i++){
		for(int j=0;j<(cp_svx.polg[i])->get_size();j++)
			(*polg[i])[j] = (*cp_svx.polg[i])[j]+polg_index;
	}
}

singvex& singvex::operator =(const singvex& eq_svx){
	if(this == &eq_svx) return *this;
	else{
		for(int i=0;i<14;i++)
		for(int j=0;j<3;j++)
		simplex[i][j] = eq_svx.simplex[i][j];	
	}
	return *this;
}

void singvex::rotate_matrix(float* vec,const float& angle,const int& loop){
	float rot[3][3];
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			rot[i][j]=0.0;
	
	rot[0][0] = rot[2][2]=cos(angle*loop);
	rot[0][2] = -(rot[2][0]=sin(angle*loop));
	rot[1][1] = 1.0;

	float tmp[3]={0.0,0.0,0.0};
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			tmp[i] += rot[i][j]*vec[j];

	for(int i=0;i<3;i++)
		vec[i] = tmp[i];
}
void singvex::create_singvex(){
	float ini_p[3]={1.0,0.0,0.0};
	float theta = PI/3.0;
	for(int i=0;i<14;i++){
		if(i%13==0){
			simplex[13][1]=-(simplex[0][1]=sqrt(2.0));
		}
		else if((i-1)/6==0){
				simplex[i][0]= 4.0/3.0;
				simplex[i][1]= sqrt(2.0)/3.0;
				rotate_matrix(simplex[i],PI/3.0,(i-1)%6);
			}
			else{
				simplex[i][0]= 4.0/3.0;
				simplex[i][1]= -sqrt(2.0)/3.0;
				rotate_matrix(simplex[i],PI/3.0,(i-1)%6);
			}
	}	
	create_polygon();
	create_polnorm();
}
void singvex::create_polygon(){
	for(unsigned i=0;i<18;i++){
		if(i/6==0||i/6==2){
			polg[i] = new polygon(3);
			if(i/6==0){
				if(i<=4){
					(*polg[i])[0]=0;
					(*polg[i])[1]=(i+1)%6;
					(*polg[i])[2]=((i+2)/6)*6+(i+2)%6;
				}
				else{
					(*polg[i])[0]=0;
					(*polg[i])[1]=((i+1)/6)*6+(i+1)%6;
					(*polg[i])[2]=(i+2)%6;
				}
			}
			if(i/6==2){
				if(i<=16){
					(*polg[i])[0]=13;
					(*polg[i])[1]=6*((i+2)/6-1)+(i+2)%6;
					(*polg[i])[2]=6+(i+1)%6;
				}
				else{
					(*polg[i])[0]=13;
					(*polg[i])[1]=6+(i+2)%6;
					(*polg[i])[2]=6*((i+1)/6-1)+(i+1)%6;
				}
			}
		}
		else{
			polg[i] = new polygon(4);
			if(i<=10){
				(*polg[i])[0]=(i+1)%6+6*((i+1)/6-1);
				(*polg[i])[1]=(i+1)%6+6*((i+1)/6);
				(*polg[i])[2]=(i+2)%6+6*((i+2)/6);
				(*polg[i])[3]=(i+2)%6+6*((i+2)/6-1);
			}
			else{
				(*polg[i])[0]=(i+1)%6+6*((i+1)/6-1);
				(*polg[i])[1]=(i+1)%6+6*((i+1)/6);
				(*polg[i])[2]=(i+2)%6+6*((i+2)/6-1);
				(*polg[i])[3]=(i+2)%6+6*((i+2)/6-2);
			}
		}
	}
}

void singvex::outer_product(float* a,float* b,float* result){
	result[0] = a[1]*b[2]-a[2]*b[1];
	result[1] = b[0]*a[2]-b[2]*a[0];
	result[2] = a[0]*b[1]-a[1]*b[0];
	float sum = result[0]*result[0]+result[1]*result[1]+result[2]*result[2];
	for(int i=0;i<3;i++)
		result[i] /= sqrt(sum);
}

void singvex::create_polnorm(){
}

void singvex::print()const{
	for(int i=0;i<14;i++){
		for(int j=0;j<3;j++){
			printf("%f ",simplex[i][j]);
		}
		printf("\n");
	}
	for(int i=0;i<18;i++){
		if(i/6==0||i/6==2){
			for(int j=0;j<3;j++)
				printf("%d ",(*polg[i])[j]);
		}
		else{
			for(int j=0;j<4;j++)
				printf("%d ",(*polg[i])[j]);
		}
		printf("\n");
	}
}

void singvex::shift_pos(const POINT3D vec){
	for(unsigned i=0;i<14;i++){
		for(unsigned j=0;j<3;j++){
			simplex[i][j]+=vec[j];
		}
	}
}
singvex sigvx;
