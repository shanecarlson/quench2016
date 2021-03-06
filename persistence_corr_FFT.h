//header for calculating and outputting the 2-pt correlation as a
//function of radius the 2D persistence lattice by Fast Fourier Transform
//by Shane Carlson

void record_persistence_corr(int par_sim, int par_pic){
	double P=(double)calculate_persistence()/((double)L*L);
	double C[(int)(L/2)]; //persistence correlation fn C(r)
	//double S[(int)(L/2)]; //structure factor of persistence lattice S(r)
	int kx=0; //'data' index

	double* data_loc = malloc( 2*L*L*sizeof(*data_loc) ); //array that's transformed by FFT function 'fourn' 
	if(data_loc==0){
		printf("allocation of 'data' failed\n");
		free(data_loc);
		exit(1);
	}
	double* data=data_loc;

	for(int j=0; j<L; j++){
		for(int i=0; i<L; i++){ //data is entered 'by row' (i indexes columns)
			data[kx] = p[i][j]==0 ? 1.0 : 0.0; //the persistence lattice is copied into 'data'
			data[kx+1]=0.0; //Im{data}=0 because data are real-valued
			kx+=2;
		}
	}

	autocorrelation_FFT(data, C);

	free(data_loc); //free the memory used for the array 'data'

	char name[64]; //filename for output

	sprintf(name, "pcorr_"); //persistence correlation
	spins_filename_instant_T0(name, L, par_sim, par_pic);
	FILE *a;
	a=fopen(name, "a");

	sprintf(name, "f_"); //persistence correlation over persistence
	spins_filename_instant_T0(name, L, par_sim, par_pic);
	FILE *b;
	b=fopen(name, "a");

	/*sprintf(name, "stru_"); //structure factor
	spins_filename_instant_T0(name, L, par_sim, par_pic);
	FILE *c;
	c=fopen(name, "a");*/

	for(int r=0; r<L/2; r++){
		fprintf(a, "%d\t%.20f\n", r, C[r]);
		fprintf(b,"%d\t%.20f\n", r, C[r]/P);
		//fprintf(c,"%.20f\t%.20f\n", 2*M_PI*r, S[r]);
	}

	fprintf(a,"\n\n");
	fprintf(b,"\n\n");
	//fprintf(c,"\n\n");
	fclose(a);
	fclose(b);
	//fclose(c);
}
