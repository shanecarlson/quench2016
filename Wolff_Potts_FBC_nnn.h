//single-cluster (a.k.a. Wolff) Monte Carlo simulation header 
//for the 2D Potts Model - next-nearest neighbor with free boundary conditions
//by Shane Carlson

#define P_add_c_Potts (1.0-1.0/(1.0+sqrt(q)));//$P_{add,c}$ for Potts model

int cluster_size; //number of spins currently in cluster
double P_add;
int color0;
int new_color;

void cluster(int i, int j, int from){

	if(s[i][j]==color0){
		if(from==8 || drand48()<P_add){
			s[i][j]=new_color;
			cluster_size++;
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
			if(from!=6 && i<L-1 && j>0)
				cluster(i+1, j-1, 7);
			if(from!=7 && i>0 && j<L-1)
				cluster(i-1, j+1, 6);
		}
	}
}

void wolff_step(){
	int x = (int)(drand48()*L); // rand. int. 0 through L-1
	int y = (int)(drand48()*L);
	color0 = s[x][y];
	do{
		new_color = (int)(drand48()*q);
	}while(new_color==color0);
	cluster_size=0;
	cluster(x, y, 8);
}
