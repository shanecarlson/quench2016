#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>

#include "parameters.h"
#include "filenames_T0.h"

int main(int argc, char* argv[]){

	int chooser;
	char type_name[64];
	int starting_pic;

	printf("Enter 'c' for correlation length, 'm' for persistence mass: ");
	chooser=getchar();
	if(chooser=='m'){
		sprintf(type_name, "mass_");
		starting_pic=1;
	}
	else if(chooser=='c'){
		sprintf(type_name, "corr_");
		starting_pic=0;
	}
	else{
		printf("invalid entry, try again\n");
		return 0;
	}

	const int rmax=L/2+1; //max radius plus 1
	const int num_pics;

	char name[64]="dir_";

	spins_foldername_T0(name, q, L);
	if(chdir(name)==-1){
		printf("there were issues changing to the directory \'%s\'\n; stopping combine process\n", name);
		return 0;
	}

	FILE *a;
	a=fopen("num_pics.txt", "r");
	fscanf(a, "%d", &num_pics);
	fclose(a);

	double O[num_pics][rmax]; //recorded observable
	double vO[num_pics][rmax]; //variance of the above observable
	int trials[num_pics][rmax]; //number of data that are combined
	bool data_here[rmax];

	int r; //distance
	double iO; //input variable

	for(r=0; r<rmax; r++){
		data_here[r]=0;
		for(int pic=0; pic<num_pics; pic++){
			O[pic][r]=vO[pic][r]=0.0;
			trials[pic][r]=0;
		}
	}

	for(int pic=starting_pic; pic<num_pics; pic++){
		sprintf(name, "%s", type_name);
		spins_filename_instant_T0(name, L, samples, pic);
		FILE *a;
		a=fopen(name, "r");

		while(fscanf(a, "%d", &r)==1){
			if(fscanf(a, "%lf", &iO)==1){
				trials[pic][r]++;
				O[pic][r]+=iO;
			}
			else
				printf("problem fetching data in loop 1\n");
		}

		for(r=0; r<rmax; r++)
			if(trials[pic][r]>0){
				data_here[r]=1;
				O[pic][r]/=(double)trials[pic][r]; //normalizes quantity
			}

		rewind(a);

		while(fscanf(a, "%d", &r)==1){
			if(fscanf(a, "%lf", &iO)==1)
				vO[pic][r]+=(O[pic][r]-iO)*(O[pic][r]-iO); //calculate variance
			else
				printf("problem fetching data in loop 2\n");
		}

		for(r=0; r<rmax; r++)
			if(trials[pic][r]>1)
				vO[pic][r]/=(double)trials[pic][r]-1.0; //normalizes quantity's variance

		fclose(a);
	}

	sprintf(name, "%s", type_name);
	strcat(name, "avg.txt");
	FILE *w;
	w=fopen(name, "w"); //combined timeseries

	r=0;
	while(r<rmax){
		fprintf(w, "%d\t", r);
		for(int pic=starting_pic; pic<num_pics; pic++)
			fprintf(w, "%.8f\t%.8f\t", O[pic][r], sqrt(vO[pic][r]));
		fprintf(w, "\n");
		
		do{
			r++;
		}while(!data_here[r]);
	}
	fclose(w);

	return 0;
}
