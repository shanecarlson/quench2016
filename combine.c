#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>

#include "parameters.h"
#include "filenames_T0.h"

static inline bool match(double known_t, double file_t){
	double diff=(known_t-file_t)/known_t;
	double tol=0.0001;

	if(diff<tol && diff>-tol)
		return 1;
	return 0;
}

int find_num_datapoints(){
	int N_pts=0;
	double tic=tic_start;

	while(tic<max_time){
		tic*=tic_mult;
		N_pts++;
	}
	return N_pts;
}

double find_instant_exponent(double O[], double time[], int index0, int nn, int N_pts){
	double x_=0.0, y_=0.0, xy_=0.0, xx_=0.0, lx, ly;
	int norm=0;

	for(int t_ind=index0-nn; t_ind<=index0+nn; t_ind++)
		if(t_ind>=0 && t_ind<N_pts){
			lx=log(time[t_ind]);
			ly=log(O[t_ind]);
			x_+=lx;
			y_+=ly;
			xy_+=lx*ly;
			xx_+=lx*lx;
			norm++;
		}
	return (x_*y_-xy_*norm)/(x_*x_-xx_*norm);
}

int main(int argc, char* argv[]){

	const int N_pts=find_num_datapoints();

	char name[64]="dir_";

	spins_foldername_T0(name, q, L);
	if(chdir(name)==-1){
		printf("there were issues changing to the directory \'%s\'; stopping combine process\n", name);
		return 0;
	}

	double time[N_pts];
	double l[N_pts];
	double vl[N_pts];
	double P[N_pts];
	double vP[N_pts];
	int trials[N_pts];

	const int nn_max=1; //max number of neighboring points used to find instantaneous exponents
	double ie[N_pts]; //instantaneous exponent
	double vie[N_pts]; //variance of instantaneous exponent
	double ia;

	int t_ind;
	double il, iP, it;
	double tic=tic_start;

	for(t_ind=0; t_ind<N_pts; t_ind++){
		l[t_ind]=vl[t_ind]=P[t_ind]=vP[t_ind]=trials[t_ind]=0;
		time[t_ind]=tic;
		tic*=tic_mult;
	}

	FILE *t;
	t=fopen("rts.txt", "r"); //raw timeseries

	while(fscanf(t, "%d", &t_ind)==1){
		if(fscanf(t, "%lf%*d%lf%lf%*f%*f", &it, &il, &iP)==3){
			if(!match(time[t_ind], it))
				printf("non-matching times\n");
			trials[t_ind]++;
			l[t_ind]+=il;
			P[t_ind]+=iP;
		}
		else
			printf("problem fetching data in loop 1\n");
	}

	for(t_ind=0; t_ind<N_pts; t_ind++){
		l[t_ind]/=trials[t_ind];
		P[t_ind]/=trials[t_ind];
	}

	rewind(t);

	while(fscanf(t, "%d", &t_ind)==1){
		if(fscanf(t, "%*f%*d%lf%lf%*f%*f", &il, &iP)==2){
			vl[t_ind]+=(l[t_ind]-il)*(l[t_ind]-il);
			vP[t_ind]+=(P[t_ind]-iP)*(P[t_ind]-iP);
		}
		else
			printf("problem fetching data in loop 2\n");
	}

	fclose(t);

	for(t_ind=0; t_ind<N_pts; t_ind++){
		vl[t_ind]/=(trials[t_ind]-1);
		vP[t_ind]/=(trials[t_ind]-1);
	}

	for(t_ind=0; t_ind<N_pts; t_ind++){
		ie[t_ind]=0.0;
		for(int nn=1; nn<=nn_max; nn++){
			ie[t_ind]+=find_instant_exponent(l, time, t_ind, nn, N_pts);
		}
		ie[t_ind]/=nn_max;
	}

	for(t_ind=0; t_ind<N_pts; t_ind++){
		vie[t_ind]=0.0;
		for(int nn=1; nn<=nn_max; nn++){
			ia=find_instant_exponent(l, time, t_ind, nn, N_pts);
			vie[t_ind]+=(ia-ie[t_ind])*(ia-ie[t_ind]);
		}
		vie[t_ind]/=(nn_max-1);
	}

	FILE *w;
	w=fopen("alpha.txt", "w"); //combined timeseries
	for(t_ind=0; t_ind<N_pts; t_ind++)
		fprintf(w, "%f\t%f\t%f\n",
			time[t_ind],
			ie[t_ind],
			sqrt(vie[t_ind])
			);
	fclose(w);

	for(t_ind=0; t_ind<N_pts; t_ind++){
		ie[t_ind]=0.0;
		for(int nn=1; nn<=nn_max; nn++){
			ie[t_ind]-=find_instant_exponent(P, time, t_ind, nn, N_pts);
		}
		ie[t_ind]/=nn_max;
	}

	for(t_ind=0; t_ind<N_pts; t_ind++){
		vie[t_ind]=0.0;
		for(int nn=1; nn<=nn_max; nn++){
			ia=-find_instant_exponent(P, time, t_ind, nn, N_pts);
			vie[t_ind]+=(ia-ie[t_ind])*(ia-ie[t_ind]);
		}
		vie[t_ind]/=(nn_max-1);
	}

	w=fopen("theta.txt", "w"); //combined timeseries
	for(t_ind=0; t_ind<N_pts; t_ind++)
		fprintf(w, "%f\t%f\t%f\n",
			time[t_ind],
			ie[t_ind],
			sqrt(vie[t_ind])
			);
	fclose(w);

	w=fopen("cts.txt", "w"); //combined timeseries

	for(t_ind=0; t_ind<N_pts; t_ind++)
		fprintf(w, "%f\t%f\t%f\t%f\t%f\n",
			time[t_ind],
			l[t_ind],
			sqrt(vl[t_ind]),
			P[t_ind],
			sqrt(vP[t_ind])
			);
	fclose(w);

	return 0;
}
