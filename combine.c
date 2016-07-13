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

	FILE *w;
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
