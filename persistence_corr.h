//header for calculating and outputting the 2-pt correlation
//function of radius for 2D Ising lattice
//by Shane Carlson

void persistence_corr(int i, int j, long int D[], long int vol[]){
	int r_index;

	for(int di=1; di<L/2; di++){ //spins lying in a line to the right
		if(p[wrap(i,di)][j]==0) //if persistent
			D[di]++;
		vol[di]++;
	}

	for(int di=-L/2+1; di<L/2; di++)
		for(int dj=1; dj<L/2; dj++) //all spins above
			if(di*di+dj*dj<L*L/4){
				r_index=(int)(sqrt(di*di+dj*dj)-0.5)+1;
				if(p[wrap(i,di)][wrap(j,dj)]==0) //if persistent
					D[r_index]++;
				vol[r_index]++;
			}
}

void record_persistence_corr(int par_sim, int par_pic){
	long int D[(int)(L/2)+1]; //persistence correlation fn D
	long int vol[(int)(L/2)+1]; //total number of sites counted for r
	double P=0; //persistence

	for(int r=0; r<=(int)(L/2); r++)
		D[r]=vol[r]=0;

	for(int i=0; i<L; i++)
		for(int j=0; j<L; j++)
			if(p[i][j]==0){
				persistence_corr(i, j, D, vol); //note: now vol ~ P
				P++;
			}

	P/=L*L;

	char name1[64];
	char name2[64]; //filenames for output

	sprintf(name1, "pcorr_");
	spins_filename_instant_T0(name1, L, par_sim, par_pic);
	FILE *a;
	a=fopen(name1, "a");

	sprintf(name2, "f_");
	spins_filename_instant_T0(name2, L, par_sim, par_pic);
	FILE *b;
	b=fopen(name2, "a");

	fprintf(a,"%d\t%d\n", 0, 1);
	fprintf(b,"%d\t%.20f\n", 0, 1.0/P);
	for(int r=1; r<=L/2; r++){
		fprintf(a,"%d\t%.20f\n", r, (double)D[r]/vol[r]);
		fprintf(b,"%d\t%.20f\n", r, (double)D[r]/(P*vol[r]));
	}

	fprintf(a,"\n\n");
	fprintf(b,"\n\n");
	fclose(a);
	fclose(b);
}
