//2D Potts Model heatbath standard Monte Carlo header for T=0
//by Shane Carlson

#include <stdbool.h>

bool blocked_state; //1 if state is blocked, 0 if not

void T0_step(){
	int i=L*drand48();
	int j=L*drand48();
	int s0=s[i][j];
	int count[q]; //number of nn w color l
	for(int l=0; l<q; l++)
		count[l]=0;
	int max_count=0, deg=0, new; 

	nearest_neighbors(i, j, count);

	for(int l=0; l<q; l++)
		if(count[l]>max_count){
			max_count=count[l];
			new=l;
		}

	for(int l=0; l<q; l++)
		if(count[l]==max_count)
			deg++;

	if(deg==1)
		s[i][j]=new;
	else{
		new=(int)(drand48()*deg)+1; //random integer 1 to deg
		for(int l=0; new>0; l++){
			if(count[l]==max_count)
				new--;
			if(new==0)
				s[i][j]=l;
		}
	}
	if(s[i][j]!=s0)
		p[i][j]++;
}
