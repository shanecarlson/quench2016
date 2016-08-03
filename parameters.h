#define q_max 2 //MAX number of states of the Potts model
int q=q_max; //number of states of the Potts model
#define L_max 512 //MAX number of spins along a side; for array init
int L=L_max; //number of spins along a side
#define Nb 1000 //number of "blocking" blocks
#define nb 1000 //blocking block-length
#define N (Nb*nb) //number of sweeps
#define samples 20 //number of temperatures we simulate over
#define therm 10000 //thermalization (in sweeps)

#define B_c_potts (log(1+sqrt(q))) //$\beta_c$ for Potts model
#define B_c_ising 0.4406867935 //$\beta_c$ for Ising model
#define B_start B_c_ising //$\beta_{start}$
#define B_inc 0.2 //$\beta_{inc}$
//double B=B_start; //$\beta$

#define tic_start 0.1 //first time where quench data is recorded
#define tic_mult 1.2 //tic multiplier: tic$_{i+1}=$ tic$_{i}\cdot$ tic_mult
#define max_time 50000 //maximum time

char headersID[8]="PSGI"; //<BOUNDARY><LATTICE><ALG><T_i>_
