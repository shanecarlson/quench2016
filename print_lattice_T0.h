//lattice printing/plotting functions for square lattices
//for integer/boolean lattices in 2D
//by Shane Carlson

void plot_bool_lattice(bool latt[L_max][L_max], int par_L, double par_sim, double par_pic){
	char name[64]; //filename for output

	sprintf(name, "lat_bool_");
	spins_filename_instant_T0(name, par_L, par_sim, par_pic);
	FILE *a;
	a=fopen(name, "w");

	for(int i=0;i<par_L;i++)
		for(int j=0;j<par_L;j++)
			if(latt[i][j]==0)
				fprintf(a,"%d\t%d\n", i, j);

	fprintf(a,"\n\n");
	fclose(a);
}

void plot_int_lattice_01(int latt[L_max][L_max], int par_L, double par_sim, double par_pic){
	char name[64]; //filename for output

	if(latt==sc)
		sprintf(name, "lat_stuck_01_");
	if(latt==p)
		sprintf(name, "lat_pers_01_");

	spins_filename_instant_T0(name, par_L, par_sim, par_pic);
	FILE *a;
	a=fopen(name, "w");

	for(int i=0;i<par_L;i++)
		for(int j=0;j<par_L;j++)
			if(latt[i][j]==0)
				fprintf(a,"%d\t%d\n", i, j);

	fprintf(a,"\n\n");
	fclose(a);
}

void plot_int_lattice(int latt[L_max][L_max], int par_L, double par_sim, double par_pic){
	char name[64]; //filename for output

	if(latt==s)
		sprintf(name, "lat_spins_");
	if(latt==p)
		sprintf(name, "lat_pers_");
	spins_filename_instant_T0(name, par_L, par_sim, par_pic);
	FILE *a;
	a=fopen(name, "w");

	for(int i=0;i<par_L;i++)
		for(int j=0;j<par_L;j++)
			fprintf(a,"%d\t%d\t%d\n", i, j, latt[i][j]);

	fprintf(a,"\n\n");
	fclose(a);
}
