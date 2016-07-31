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

#define OP1() {stru[i+L/2][j+L/2]=data[kx]*data[kx]+data[kx+1]*data[kx+1]; \
		data[kx]*=data[kx]; \
		data[kx+1]*=data[kx+1]; \
		kx+=2;}
// data -> |data|^2

#define OP2() {corr[i+L/2][j+L/2]=data[kx]; kx+=2;}

void autocorrelation_FFT(double data[], double C[], double S[], double C0, double C1){

	double stru[L][L]; //structure factor as a function of wavevector
	double corr[L][L]; //correlation as a function of relative position vector
	unsigned int vol[(int)(L/2)]; //total number of sites counted for r
	int kx=0, r_index; //'data' index
	unsigned long nn[2]={L,L};

	for(int r=0; r<L/2; r++){ //initialization
		C[r]=S[r]=0.0;
		vol[r]=0;
	}

	fourn(data, nn, 2, 1);

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

	fourn(data, nn, 2, -1);

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

	S[0] = stru[0 +L/2][0 +L/2]; //origin
	C[0] = corr[0 +L/2][0 +L/2];
	vol[0]=1;

	for(int r=1; r<L/2; r++){ //on-axis
		S[r] += stru[0 +L/2][ r+L/2] + stru[ r+L/2][0 +L/2] 
			  + stru[0 +L/2][-r+L/2] + stru[-r+L/2][0 +L/2];
		C[r] += corr[0 +L/2][ r+L/2] + corr[ r+L/2][0 +L/2]
			  + corr[0 +L/2][-r+L/2] + corr[-r+L/2][0 +L/2];
		vol[r]+=4;
	}

	for(int i=1; i<L/2; i++) //off-axis
		for(int j=1; j<L/2; j++)
			if( (r_index=(int)(sqrt(i*i+j*j)-0.5)+1) < L/2){
				S[r_index] += stru[ i+L/2][j +L/2] + stru[ i+L/2][-j+L/2] 
							+ stru[-i+L/2][j +L/2] + stru[-i+L/2][-j+L/2];
				C[r_index] += corr[ i+L/2][j +L/2] + corr[ i+L/2][-j+L/2]
							+ corr[-i+L/2][j +L/2] + corr[-i+L/2][-j+L/2];
				vol[r_index]+=4;
			}

	for(int r=0; r<L/2; r++){ //normalizes w.r.t. number of points that were counted
		S[r]/=((double)vol[r]*L*L);
		C[r]/=((double)vol[r]);
	}

	for(int r=1; r<L/2; r++)
		C[r]/=C[0];
	C[0]=1;

	for(int r=0; r<L/2; r++)
		C[r]=(C0+C1)*C[r]-C1;
}
