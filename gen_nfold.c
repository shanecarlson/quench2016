#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "parameters.h"
#include "filenames_T0.h"

#include "Potts.h" // Potts/Ising
//#include "Wolff_Potts_PBC_sq.h" // Potts/Ising
#include "energies_PBC_sq.h"
#include "domain_size_PBC_sq.h"

#include "persistence.h"

#include "fourn.h"
#include "autocorrelation_by_FFT.h"
#include "persistence_corr_FFT.h"
//#include "correlation_IM_FFT.h" // Potts/Ising

#include "nfold_Potts_heatbath.h" // Potts/Ising
#include "class_PBC_sq.h"
#include "nfold.h"

#include "print_lattice_T0.h"

int main(int argc, char* argv[]){

	time_t start = time(NULL);
	time_t pstart; //process start time
	time_t ticstart; //tic start time
	char name[64]="dir_";

	spins_foldername_T0(name, q, L);
	if(mkdir(name, S_IRWXU)==-1){
		printf("there were issues making the directory \'%s\', try again\n", name);
		return 0;
	}
	if(chdir(name)==-1){
		printf("there were issues changing to the directory \'%s\'\n", name);
		return 0;
	}

	// /*

	FILE *terminal;
	terminal=fopen("terminal.txt", "w");

	FILE *tmr; //for timing tics

	int M; //magnetization
	double QN; //Q_N - see the original "nfold" paper by Bortz et al

	unsigned long long step_count; //steps taken in a tic
	double t; //time
	double tic; //time where data (persistence, domain size) is gathered
	int t_ind; //indexes the tics

	double pic_tic; //actual time when the lattice shots are taken
	int pic, max_pics=0; //indexes the lattice shots for file handling
	double pic_tic_mult=4; //multiplier for pics

	FILE *rts;
	rts=fopen("rts.txt", "w"); //raw timeseries

	// */

	FILE *tts;
	tts=fopen("therm.txt", "w");

	srand48(lrand48());

	set_flip_probabilities();

	for(int sim=0; sim<samples; sim++){

		printf("sim %d of %d\n", sim+1, samples);
		fprintf(terminal, "sim %d of %d\n", sim+1, samples);

		initialize_lattice_random_m0(); /*

		initialize_lattice_up_w_prob(0.75); // Potts/Ising
		P_add=1-exp(-2*B_c_ising); // Potts/Ising
		for(int swp=0; swp<therm || calculate_magnetization()!=0; swp++){ // Potts/Ising
			wolff_step();
			if(sim==0){
				calculate_energy();
				fprintf(tts, "%d\t%f\n", E, calculate_avg_domain_size());
			}
		}

		printf("thermalization complete\n");
		fprintf(terminal, "thermalization complete\n");
		// */

		//record_correlation_fn(samples, 0);

		if(sim==0)
			plot_int_lattice(s, L, 0, 0); // Potts/Ising

		reset_persistence_lattice();
		update_all_classes();
		count_all_members();
		//create_chains(); // !*

		blocked_state=0;
		t=0.0;
		tic=tic_start;
		t_ind=0;
		pic_tic=1;
		pic=1;
		step_count=0;

		ticstart=time(NULL);
		while(tic<max_time && !blocked_state){
			QN=calculate_QN();
			t -= log(drand48())/QN; //time update for FOLLOWING step
			if(t > tic){
				//printf("tic %d took %f seconds and %llu steps\n", t_ind, (double)(time(NULL) - ticstart), step_count); //process timer

				tmr=fopen("tictimer.txt", "a"); //---
				fprintf(tmr, "tic %d took %f seconds and %llu steps\n", t_ind, (double)(time(NULL) - ticstart), step_count); //process timer
				fclose(tmr); //---

				while(t > tic*tic_mult){
					printf("tic at %f skipped\n", tic);
					fprintf(terminal, "tic at %f skipped\n", tic);
					tic*=tic_mult;
					t_ind++;
				}
				tmr=fopen("tictimer.txt", "a"); //---
				pstart=time(NULL); //process timer
				calculate_energy();
				fprintf(rts, "%d\t%.20f\t%d\t%.20f\t%.20f\t%.20f\t%.20f\n",
					t_ind,
					tic,
					E,
					calculate_avg_domain_size(),
					(double)calculate_persistence()/(L*L),
					(double)members[0]/(L*L),
					(double)calculate_magnetization( first_top_color() )/(L*L) // Potts/Ising
				); //timeseries
				fprintf(tmr, "\ttic print: %f seconds\n", (double)(time(NULL) - pstart)); //process timer
				fclose(tmr); //---

				tic*=tic_mult;
				t_ind++;
				step_count=0;
				ticstart=time(NULL);
			}
			if(t > pic_tic){
				if(sim==0){
					tmr=fopen("tictimer.txt", "a"); //---
					pstart=time(NULL); //process timer
					plot_int_lattice(s, L, sim, pic); // Potts/Ising
					plot_int_lattice(p, L, sim, pic);
					plot_int_lattice_01(p, L, sim, pic);
					fprintf(tmr, "\tlat plots: %f seconds\n", (double)(time(NULL) - pstart)); //process timer
					fclose(tmr); //---
				}
				tmr=fopen("tictimer.txt", "a"); //---
				//record_correlation_fn(samples, pic);
				record_persistence_corr(samples, pic);
				fprintf(tmr, "\tcorrelations: %f seconds\n", (double)(time(NULL) - pstart)); //process timer
				fclose(tmr); //---
				pic_tic*=pic_tic_mult;
				pic++;
			}
			T0_nfold_step(QN);
			step_count++;
		}

		if(blocked_state){
			M=calculate_magnetization( first_top_color() ); // Potts/Ising
			if(M==L*L || M==-L*L){
				printf("ended at a global minimum at t = %.2f\n", t);
				fprintf(terminal, "ended at a global minimum at t = %.2f\n", t);
			}
			else{
				printf("ended in a blocked state at t = %.2f\n", t);
				fprintf(terminal, "ended in a blocked state at t = %.2f\n", t);
			}
		}
		else{
			printf("ended after max time at t = %.2f\n", t);
			fprintf(terminal, "ended after max time at t = %.2f\n", t);
		}

		fprintf(rts, "\n\n");

		if(sim==0){
			plot_int_lattice(s, L, sim, pic); // Potts/Ising
			plot_int_lattice(p, L, sim, pic);
			plot_int_lattice_01(p, L, sim, pic);
		}
		if(pic>max_pics)
			max_pics=pic;
	// */
	}

	FILE *numpicsfile;
	numpicsfile=fopen("num_pics.txt", "w");
	fprintf(numpicsfile, "%d\n", max_pics);
	fclose(numpicsfile);

	FILE *ticsfile;
	ticsfile=fopen("tics_key.txt", "w");
	pic=1;
	pic_tic=1;
	while(pic<max_pics){
		fprintf(ticsfile, "%d\t%.20f\n", pic, pic_tic);
		pic_tic*=pic_tic_mult;
		pic++;
	}

	fclose(ticsfile);

	printf("process took %.2f seconds\n", (double)(time(NULL) - start));
	fprintf(terminal, "process took %.2f seconds\n", (double)(time(NULL) - start));

	fclose(rts);
	fclose(tts);
	fclose(terminal);

	return 0;
}
