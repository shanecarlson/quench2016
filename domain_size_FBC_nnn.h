//domain size of next nearest neighbor square lattice
//for the 2D Potts or Ising Models with free boundary conditions
//by Shane Carlson

double calculate_avg_domain_size(){
	int domains=2*L + 2*(2*L-3); //counts the total number of domains

	for(int i=0;i<L;i++){
		for(int j=0;j<L;j++){
			if(i<L-1)
				domains += s[i][j]==s[i+1][j  ] ? 0 : 1;
			if(j<L-1)
				domains += s[i][j]==s[i  ][j+1] ? 0 : 1;
			if(j<L-1 && i<L-1)
				domains += s[i][j]==s[i+1][j+1] ? 0 : 1;
			if(j<L-1) && i>0)
				domains += s[i][j]==s[i-1][j+1] ? 0 : 1;
		}
	}
	return (double)( 2*L*(L-1) + 2*(L-1)*(L-1) ) / (double)domains;
}
