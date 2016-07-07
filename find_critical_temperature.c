#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>

#include "parameters.h"

#include "IM.h" // !
#include "Wolff_IM_PBC_sq.h" // !
#include "energies_PBC_sq.h"

double log_sum(double logx, double logy){
	double larger = logx>logy ? logx : logy;
	double smaller = logx<=logy ? logx : logy;

	return log(exp(smaller-larger)+1)+larger;
}

static inline double log_diff(double logy, double logx){
	return log(1-exp(logx-logy))+logy;
}

double reweight_heat_capacity(double lH[], bool hitH[], int Emin, int Nbins, double binW, double B_input){
	double En, lZ, lE, lEn, ldE2, term, dE, Ea;

	lZ=lE=lEn=ldE2=-DBL_MAX; //~sets arg to zero

	for(int bin=0; bin<Nbins; bin++){
		if(hitH[bin] && (En=Emin+binW*(bin+0.5))!=0){
			term=(B_start-B_input)*En+lH[bin];
			lZ=log_sum(lZ, term);
			if(En<0)
				lEn=log_sum(lEn, term+log(-En));
			if(En>0)
				lE=log_sum(lE, term+log(En));
		}
	}

	if(lEn>lE){
		lEn=log_diff(lEn, lE);
		lEn-=lZ;
		Ea=-exp(lEn);
	}
	else{
		lE=log_diff(lE, lEn);
		lE-=lZ;
		Ea=exp(lE);
	}

	//printf("<E>(%.3f) = %.3f\n", B_input, Ea);

	for(int bin=0; bin<Nbins; bin++){
		if(hitH[bin] && (En=Emin+binW*(bin+0.5))!=0){ //if term is positive
			dE=En-Ea;
			term=(B_start-B_input)*En+log(dE*dE)+lH[bin];
			ldE2=log_sum(ldE2, term);
		}
	}
	ldE2-=lZ;

	return B_input*B_input*exp(ldE2);
}

int main(int argc, char* argv[]){

	int En, Emin, Emax, maxi, binW; 
	double C[5], beta[5];
	double Bmin=B_start*0.6;
	double Bmax=B_start*1.4;

	FILE *a;
	a=fopen("temp.txt", "w");

	P_add=1-exp(-2*B_start);
	initialize_lattice_up_w_prob(0.8); //!
	printf("\nthermalizing...\n");
	for(int swp=0; swp<therm; swp++) //thermalization
		wolff_step();
	printf("simulating...\n");
	for(int swp=0; swp<N; swp++){
		wolff_step();
		calculate_energy();
		fprintf(a, "%d\n", E);
	}

	printf("calculating histograms...\n");

	fclose(a);

	a=fopen("temp.txt", "r");

	fscanf(a, "%d", &En); //sweep 1
	Emin=Emax=En;

	for(int swp=1; swp<N; swp++){
		fscanf(a, "%d", &En);
		if(Emax<En)
			Emax=En;
		if(Emin>En)
			Emin=En;
	}
	printf("Emax-Emin = %d\n", Emax-Emin);

	rewind(a);

	printf("determining bin width...\n");

	binW=(int)((Emax-Emin+1.0)/100000.0); //denominator is ~desired number of bins
	if(binW<2)
		binW=2;
	printf("bin width = %d\n", binW);

	const int Nbins=(int)((double)(Emax-Emin)/binW+1.0);

	printf("declaring histogram array...\n");
	double lH[Nbins]; //number histograms
	bool hitH[Nbins]; 

	printf("initializing histogram array...\n");
	for(int bin=0; bin<Nbins; bin++){
		lH[bin]=0;
		hitH[bin]=0;
	}

	printf("calculating histograms from series...\n");
	for(int swp=0; swp<N; swp++){
		fscanf(a, "%d", &En);
		lH[(int)((double)(En-Emin)/binW)]++; //<<<<<<
		hitH[(int)((double)(En-Emin)/binW)]=1;
	}
	fclose(a);
	
	printf("taking log of histograms...\n");
	for(int bin=0; bin<Nbins; bin++)
		lH[bin]=log(lH[bin]);

	printf("initializing heat capacity bracketing points...\n");
	for(int i=0; i<5; i++){
		beta[i]=Bmin+i*(Bmax-Bmin)/4.0;
		C[i]=reweight_heat_capacity(lH, hitH, Emin, Nbins, binW, beta[i]);
	}
	printf("maximizing C:\n\n");

	printf("B =\t %f\n", beta[2]);
	while(beta[4]-beta[0]>0.0000000001){ //fixed-point iteration loop
		maxi=0;
		for(int i=0; i<5; i++)
			if(C[i]>C[maxi])
				maxi=i;
		if(maxi==0 || maxi==4){
			printf("maximizer lost\n");
			break;
		}
		beta[0]=beta[maxi-1];
		beta[4]=beta[maxi+1];
		beta[2]=beta[maxi];
		C[0]=C[maxi-1];
		C[4]=C[maxi+1];
		C[2]=C[maxi];
		beta[1]=(beta[0]+beta[2])/2.0;
		beta[3]=(beta[2]+beta[4])/2.0;
		C[1]=reweight_heat_capacity(lH, hitH, Emin, Nbins, binW, beta[1]);
		C[3]=reweight_heat_capacity(lH, hitH, Emin, Nbins, binW, beta[3]);
		printf("\t %.20f\n", beta[2]);
	}
	printf("B_c =\t %.20f\n", beta[2]);
	a=fopen("critical_temperatures.h", "a");
	fprintf(a, "#define Bc_%s_q%dL%d %.20f\n", headersID, q, L, beta[2]);
	fclose(a);

	return 0;
}
