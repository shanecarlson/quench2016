//2D Potts Model heatbath n-fold header
//by Shane Carlson

#include <stdbool.h>

#define n_fold 9 //number of spin classes

int sc[L_max][L_max]; //array that stores spin class of s[i][j]
int dc[L_max][L_max]; //dominant colors in the neighborhood & degeneracy
int members[n_fold]; //stores the number of members of each class
double p_flip[n_fold]; //stores the transition probability of each class
bool blocked_state; //1 if state is blocked, 0 if not

void calculate_class(int i, int j){ //revamp in terms of "nearest_neighbors"
	int count[q]; //number of nn w color clr
	for(int clr=0; clr<q; clr++)
		count[clr]=0;
	int max_count=0, deg=0; //# of nn with top color, degeneracy of groups

	nearest_neighbors(i, j, count);

	for(int clr=0; clr<q; clr++)
		if(count[clr]>max_count)
			max_count=count[clr]; //finds max_count

	dc[i][j]=0;
	for(int clr=0; clr<q; clr++)
		if(count[clr]==max_count){
			deg++; //finds degeneracy at
			dc[i][j]+=1<<clr; //records local top colors in dc
		}
	dc[i][j]+=deg<<16; //records degeneracy in dc (keep q < ~16)

	if(count[s[i][j]] == max_count){
		if(deg == 1)
			sc[i][j]=0; //stuck
		else
			sc[i][j]=deg;
	}
	else //there is a more dominant color near i,j
		sc[i][j]=1; //must flip
}

void flip_spin(int i, int j){
	int stop;
	int count=0;
	int deg = dc[i][j]>>16;

	if(sc[i][j]==1) //not at min energy
		stop=(int)(drand48()*deg)+1; //integer 1 to degeneracy
	if(sc[i][j]>1) //at min, but there is degeneracy
		stop=(int)(drand48()*(deg-1))+1; //integer 1 to degeneracy-1 

	for(int clr=0; clr<q && count<stop; clr++){
		if( dc[i][j]&1<<clr && clr!=s[i][j] ){ // if clr is dominant && it's a new color
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
