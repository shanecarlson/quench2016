//Energies for the square, n.n. lattice with free boundary conditions
//for the 2D Ising, and Potts, and XY Models
//by Shane Carlson

void calculate_energy(){ 

	E=0;
	for(int i=0;i<L;i++){
		for(int j=0;j<L;j++){
			if(i<L-1)
				E += bond(s[i][j], s[i+1][j  ]);
			if(j<L-1)
				E += bond(s[i][j], s[i  ][j+1]);
		}
	}
}

void energy_contribution(int i, int j){

	EC=0;
	if(i<L-1)
		EC += bond(s[i][j], s[i+1][j  ]);
	if(i>0)
		EC += bond(s[i][j], s[i-1][j  ]);
	if(j<L-1)
		EC += bond(s[i][j], s[i  ][j+1]);
	if(j>0)
		EC += bond(s[i][j], s[i  ][j-1]);
}

void proposed_energy_contribution(int i, int j){

	EC=0;
	if(i<L-1)
		EC += bond(s_proposed, s[i+1][j  ]);
	if(i>0)
		EC += bond(s_proposed, s[i-1][j  ]);
	if(j<L-1)
		EC += bond(s_proposed, s[i  ][j+1]);
	if(j>0)
		EC += bond(s_proposed, s[i  ][j-1]);
}
