//Energies for the triangular lattice with periodic boundary conditions
//for the 2D Ising, and Potts, and XY Models
//by Shane Carlson

void calculate_energy(){ 

	E=0;
	for(int i=0;i<L;i++){
		for(int j=0;j<L;j++){
			E += bond(s[i][j], s[inc(i)][j     ]);
			E += bond(s[i][j], s[i     ][inc(j)]);
			E += bond(s[i][j], s[inc(i)][inc(j)]);
		}
	}
}

void energy_contribution(int i, int j){

	EC=0;
	EC += bond(s[i][j], s[inc(i)][j     ]);
	EC += bond(s[i][j], s[dec(i)][j     ]);
	EC += bond(s[i][j], s[i     ][inc(j)]);
	EC += bond(s[i][j], s[i     ][dec(j)]);
	EC += bond(s[i][j], s[dec(i)][dec(j)]);
	EC += bond(s[i][j], s[inc(i)][inc(j)]);
}

void proposed_energy_contribution(int i, int j){

	EC=0;
	EC += bond(s_proposed, s[inc(i)][j     ]);
	EC += bond(s_proposed, s[dec(i)][j     ]);
	EC += bond(s_proposed, s[i     ][inc(j)]);
	EC += bond(s_proposed, s[i     ][dec(j)]);
	EC += bond(s_proposed, s[dec(i)][dec(j)]);
	EC += bond(s_proposed, s[inc(i)][inc(j)]);
}
