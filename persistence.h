//header for the persistence lattice for 2D spin lattices
//by Shane Carlson

int p[L_max][L_max]; //persistance lattice (counts # times (i,j) has been flipped)

void reset_persistence_lattice(){

	for(int i=0; i<L; i++)
		for(int j=0; j<L; j++)
			p[i][j]=0;
}

int calculate_persistence(){
	int P=0;

	for(int i=0; i<L; i++)
		for(int j=0; j<L; j++)
			if(p[i][j]==0)
				P++;
	return P;
}
