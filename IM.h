//boolean lattice header
//for the 2D Ising Model
//by Shane Carlson

#include <stdbool.h>

double drand48();

bool s[L_max][L_max]; //array of spins s(x,y)
bool s_proposed; //proposed state for a flip

int E; //current energy
int EC; //energy contribution

static inline int inc(int k){
	return k<L-1 ? k+1 : 0;
}

static inline int dec(int k){
	return k>0 ? k-1 : L-1;
}

static inline int wrap(int k, int dk){

	if(dk>0){
		if(k+dk>L-1)
			return k+dk-L;
		else
			return k+dk;
	}
	if(dk<0){
		if(k+dk<0)
			return k+dk+L;
		else
			return k+dk;
	}
	else
		return k;
}


static inline int bond(bool spin1, bool spin2){
	return spin1==spin2 ? -1 : 1;
}

void initialize_lattice_up(){

	for(int i=0;i<=L-1;i++)
		for(int j=0;j<=L-1;j++)
			s[i][j]=1;
}

void initialize_lattice_up_w_prob(double p){

	for(int i=0;i<=L-1;i++)
		for(int j=0;j<=L-1;j++)
			s[i][j] = drand48()<p ? 1 : 0;
}

void initialize_lattice_random_5050(){
	int i, j;

	for(i=0;i<=L-1;i++)
		for(j=0;j<=L-1;j++)
			s[i][j]=0;

	for(int k=0; k<L*L/2; k++){
		do{
			i=(int)(drand48()*L);
			j=(int)(drand48()*L);
		}while(s[i][j]==1);
		s[i][j]=1;
	}
}

int calculate_magnetization(){
	int M=0;

	for(int i=0;i<L;i++)
		for(int j=0;j<L;j++)
			M += s[i][j]==0 ? -1 : 1;
	return M;
}
