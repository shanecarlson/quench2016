//2D Potts Model heatbath n-fold header
//by Shane Carlson

#include <stdbool.h>

#define n_fold 9 //number of spin classes

int sc[L_max][L_max]; //array that stores spin class of s[i][j]
int dc[L_max][L_max]; //dominant colors in the neighborhood & degeneracy
int members[n_fold]; //stores the number of members of each class
double p_flip[n_fold]; //stores the transition probability of each class
bool blocked_state; //1 if state is blocked, 0 if not

void calculate_class(int i, int j){
	int EC_of[q_max]; //proposed energy contribution for color s[i][j]=clr
	int ECmin=0; //minimum possible energy contr.
	int degeneracy=0; //number of colors with ECmin

	for(s_proposed=0; s_proposed<q; s_proposed++){
		proposed_energy_contribution(i, j);
		EC_of[s_proposed]=EC;
		if(EC<ECmin)
			ECmin=EC;
	}

	dc[i][j]=0;
	for(int clr=0; clr<q; clr++){
		if(EC_of[clr] == ECmin){
			degeneracy++;
			dc[i][j]+=1<<clr;
		}
	}
	dc[i][j]+=degeneracy<<16; //therefore q should be kept less than ~16

	if(EC_of[s[i][j]] == ECmin){
		if(degeneracy == 1)
			sc[i][j]=0; //stuck
		else
			sc[i][j]=degeneracy;
	}
	else //(EC_of[s[i][j]] > ECmin)
		sc[i][j]=1; //must flip
}

void flip_spin(int i, int j){ 
	int stop;
	int count=0;
	int degeneracy = dc[i][j]>>16;

	if(sc[i][j]==1) //not at min energy
		stop=(int)(drand48()*degeneracy)+1; //integer 1 to degeneracy
	if(sc[i][j]>1) //at min, but there is degeneracy
		stop=(int)(drand48()*(degeneracy-1))+1; //integer 1 to degeneracy-1 

	for(int clr=0; clr<q && count<stop; clr++){
		if( dc[i][j]&1<<clr && clr!=s[i][j] ){
			count++;
			if(count==stop)
				s[i][j]=clr;
		}
	}
}

void set_flip_probabilities(){
	p_flip[0]=0;
	p_flip[1]=1.0;
	for(int l=2; l<n_fold; l++)
		p_flip[l]=1.0-1.0/l; //probability to flip at all
}
