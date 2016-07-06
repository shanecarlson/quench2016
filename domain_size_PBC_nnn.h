//domain size of next nearest neighbor square lattice
//for the 2D Potts or Ising Models with periodic boundary conditions
//by Shane Carlson

double calculate_avg_domain_size(){
	int domains=0; //counts the total number of domains
	int interfaces; //the total number of domain interfaces in a line

	for(int i=0; i<L; i++){ //lines in the y-direction
		interfaces=0;
		for(int j=0;j<L;j++)
			if(s[i][j]!=s[i][inc(j)]) //if(there is a domain interface)
				interfaces++;
		if(interfaces==0) //there is always at least 1 domain
			domains++;
		else if(interfaces>1) //this reflects PBC
			domains+=interfaces;
		else //if there is exactly 1 domain, then there is a problem
			printf("\ndomain size error\n");
	}

	for(int j=0; j<L; j++){ //lines in the x-direction
		interfaces=0;
		for(int i=0;i<L;i++)
			if(s[i][j]!=s[inc(i)][j])
				interfaces++;
		if(interfaces==0)
			domains++;
		else if(interfaces>1)
			domains+=interfaces;
		else
			printf("\ndomain size error\n");
	}

	for(int i0=0; i0<L; i0++){ //lines in the xy-direction
		int i=i0;
		int j=0;
		interfaces=0;

		for(int k=0;k<L;k++){
			if(s[i][j]!=s[inc(i)][inc(j)])
				interfaces++;
			i=inc(i);
			j=inc(j);
		}
		if(interfaces==0)
			domains++;
		else if(interfaces>1)
			domains+=interfaces;
		else
			printf("\ndomain size error\n");
	}

	for(int i0=0; i0<L; i0++){ //lines in the (-x)y-direction
		int i=i0;
		int j=0;
		interfaces=0;

		for(int k=0;k<L;k++){
			if(s[i][j]!=s[dec(i)][inc(j)])
				interfaces++;
			i=dec(i);
			j=inc(j);
		}
		if(interfaces==0)
			domains++;
		else if(interfaces>1)
			domains+=interfaces;
		else
			printf("\ndomain size error\n");
	}

	return (double)(4*L*L)/(double)domains; //4$L^2$ is the total length of all domains
}
