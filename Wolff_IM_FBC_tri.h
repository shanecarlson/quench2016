//single-cluster (a.k.a. Wolff) Monte Carlo simulation header 
//for the 2D Ising Model - triangular with free boundary conditions
//by Shane Carlson

#define P_add_c_IM (1.0/(1.0+1.0/sqrt(2))); //$P_{add,c}$ for Ising model

bool cluster_state; //original cluster state
int cluster_size; //number of spins currently in cluster
double P_add; //$P_{add}$=1-e$^{-2\beta}$


void cluster(int i, int j, int from){

	if(s[i][j]==cluster_state){
		if(from==8 || drand48()<P_add){
			cluster_size++;
			s[i][j] ^= 1; //flips the spin
			if(from!=0 && i<L-1) //right
				cluster(i+1, j  , 2);
			if(from!=1 && j>0) //down
				cluster(i  , j-1, 3);
			if(from!=2 && i>0) //left
				cluster(i-1, j  , 0);
			if(from!=3 && j<L-1) //up
				cluster(i  , j+1, 1);
			if(from!=4 && i<L-1 && j<L-1)
				cluster(i+1, j+1, 5);
			if(from!=5 && i>0 && j>0)
				cluster(i-1, j-1, 4);
		}
	}
}

void wolff_step(){

	cluster_size=0;
	int x = (int)(drand48()*L); // rand. int. 0 through L-1
	int y = (int)(drand48()*L);
	cluster_state=s[x][y];
	cluster(x, y, 8);
}
