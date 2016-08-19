//2D Ising Model Glauber standard Monte Carlo header for T=0
//by Shane Carlson

#include <stdbool.h>

bool blocked_state; //1 if state is blocked, 0 if not

void T0_step(){
	int i=L*drand48();
	int j=L*drand48();
	bool s0=s[i][j];
	int count[2]={0,0};

	nearest_neighbors(i, j, count);

	if( count[0] > count[1] )
		s[i][j]=0;
	else if( count[1] > count[0] )
		s[i][j]=1;
	else
		s[i][j] = drand48()<0.5 ? 0 : 1;
	if(s[i][j]!=s0)
		p[i][j]++;
}
