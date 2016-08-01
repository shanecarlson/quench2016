//header for calculating and outputting the 2-pt correlation
//as a function of radius for 2D Ising lattice by Fast Fourier Transform
//by Shane Carlson

void record_correlation_fn(int par_sim, int par_pic){
	double m2=(double)calculate_magnetization()/((double)L*L); m2*=m2;
	double C[(int)(L/2)];
	double S[(int)(L/2)];
	int kx=0; //'data' index

	double* data = malloc( 2*L*L *sizeof(*data) ); //array that's transformed by FFT function 'fourn' 
	if(data==0){
		printf("allocation of 'data' failed\n");
		free(data);
		exit(1);
	}

	for(int j=0; j<L; j++){
		for(int i=0; i<L; i++){ //data is entered 'by row' (i indexes columns)
			data[kx] = s[i][j]==0 ? -1.0 : 1.0; //copying the spin lattice into 'data'
			data[kx+1]=0.0; //Im{data}=0 because data are real-valued
			kx+=2;
		}
	}

	autocorrelation_FFT(data, C, S);
	free(data); //free the memory used for the array 'data'

	char name[64]; //filename for output

	sprintf(name, "corr_raw_");
	spins_filename_instant_T0(name, L, par_sim, par_pic);
	FILE *a;
	a=fopen(name, "a");

	sprintf(name, "corr_sub_");
	spins_filename_instant_T0(name, L, par_sim, par_pic);
	FILE *b;
	b=fopen(name, "a");

	for(int r=0; r<L/2; r++){
			fprintf(a,"%d\t%.20f\n", r, C[r]);
			fprintf(b,"%d\t%.20f\n", r, (C[r]-m2)/(1.0-m2));
	}

	fprintf(a,"\n\n");
	fprintf(b,"\n\n");

	fclose(a);
	fclose(b);
}
