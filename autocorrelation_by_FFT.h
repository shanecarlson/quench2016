//header for calculating and outputting the 2-pt correlation
//as a function of radius for 2D lattices by Fast Fourier Transform
//by Shane Carlson

/* The FFT algorithm "fourn" used in this file is an adaptation of
 * an algorithm found on page 629 of
 * 
 * Numerical Recipes - The Art of Scientific Computing - Third Edition
 * 
 * by
 * 
 * W.H. Press,
 * S.A. Teukolsky,
 * W.T. Vetterling,
 * and
 * B.P. Flannery
 * 
 * Cambridge University Press (2007)
 * 
 * 'fourn' is stored in the header 'fourn.h', which is included in the 
 * main program, but not in the github repository quench2016.
 * 
 * Those wishing to implement this function will need to obtain or write
 * their own copy.
 */

#define OP1() {data[kx] = data[kx]*data[kx]+data[kx+1]*data[kx+1]; \
		data[kx+1]=0.0; \
		kx+=2;}
// data -> |data|^2

#define OP2() {corr[(i+L/2)+(j+L/2)*L]=data[kx]; kx+=2;}

void autocorrelation_FFT(double* data, double* C){
	unsigned int vol[(int)(L/2)]; //total number of sites counted for r
	int kx=0; //'data' index
	int r_index;
	unsigned int nn[2]={L,L};

	for(int r=0; r<L/2; r++){ //initialization
		C[r]=0.0;
		vol[r]=0;
	}

	fourn(data, nn, 2, 1); //forward FFT of 'data'

	double* corr_loc = malloc( L*L*sizeof(*corr_loc));  //correlation as a function of relative position vector
	if(corr_loc==0){
		printf("allocation of 'corr' failed\n");
		free(corr_loc);
		exit(1);
	}
	double* corr=corr_loc; //to prevent memory leaks

	for(int j=0; j<L/2; j++){
		for(int i=0; i<L/2; i++)
			OP1() //data entered by row, shifted such that (0,0) is in the middle
		for(int i=-L/2; i<0; i++)
			OP1()
	}
	for(int j=-L/2; j<0; j++){
		for(int i=0; i<L/2; i++)
			OP1()
		for(int i=-L/2; i<0; i++)
			OP1()
	}

	fourn(data, nn, 2, -1); //inverse FFT of 'data'

	kx=0;
	for(int j=0; j<L/2; j++){
		for(int i=0; i<L/2; i++)
			OP2()
		for(int i=-L/2; i<0; i++)
			OP2()
	}
	for(int j=-L/2; j<0; j++){
		for(int i=0; i<L/2; i++)
			OP2()
		for(int i=-L/2; i<0; i++)
			OP2()
	}

	C[0] = corr[(0 +L/2)+(0 +L/2)*L]; //origin
	vol[0]=1;

	for(int r=1; r<L/2; r++){ //on-axis
		C[r] += corr[(0 +L/2)+( r+L/2)*L] + corr[( r+L/2)+(0 +L/2)*L]
			  + corr[(0 +L/2)+(-r+L/2)*L] + corr[(-r+L/2)+(0 +L/2)*L];
		vol[r]+=4;
	}

	for(int i=1; i<L/2; i++) //off-axis
		for(int j=1; j<L/2; j++)
			if( (r_index=(int)(sqrt(i*i+j*j)-0.5)+1) < L/2){
				C[r_index] += corr[( i+L/2)+(j +L/2)*L] + corr[( i+L/2)+(-j+L/2)*L]
							+ corr[(-i+L/2)+(j +L/2)*L] + corr[(-i+L/2)+(-j+L/2)*L];
				vol[r_index]+=4;
			}

	free(corr_loc);

	for(int r=0; r<L/2; r++){ //normalizes w.r.t. number of points that were counted
		C[r]/=((double)vol[r]*L*L);
	}

	for(int r=1; r<L/2; r++) //normalizes such that C(0)=1
		C[r]/=C[0];
	C[0]=1;
}
