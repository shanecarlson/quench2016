//header for calculating and outputting the 2-pt correlation
//function of radius for 2D Ising lattice
//by Shane Carlson

void persistence_mass_contribution(int i, int j, int PM[]){

	for(int di=0; di<=L/2; di++) //spins lying in a line to the right
		if(p[wrap(i,di)][j]==0)
			PM[di]++;

	for(int di=-L/2; di<=L/2; di++)
		for(int dj=1; dj<=L/2; dj++) //all spins above
			if(di*di+dj*dj<=L*L/4)
				if(p[wrap(i,di)][wrap(j,dj)]==0)
					PM[(int)sqrt(di*di+dj*dj)]++;
}

void record_persistence_mass(int par_sim, int par_pic){
	int PM[(int)(L/2)+1]; //r ranges from 0 to L^2/4
	double PMsum=0;
	int P=0;

	for(int r=0; r<=(int)(L/2); r++)
		PM[r]=0;
	for(int i=0; i<L; i++)
		for(int j=0; j<L; j++)
			if(p[i][j]==0){
				persistence_mass_contribution(i, j, PM);
				P++;
			}

	char name[64]; //filename for output

	sprintf(name, "mass_");
	spins_filename_instant_T0(name, L, par_sim, par_pic);
	FILE *a;
	a=fopen(name, "a");

	for(int r=0; r<=L/2; r++)
		if(PM[r]>0){
			PMsum+=PM[r];
			fprintf(a,"%d\t%f\t%.20f\n", r, 2.0*PMsum/P);
		}

	fprintf(a,"\n\n");
	fclose(a);
}
