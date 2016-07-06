//timeseries file naming header
//by Shane Carlson

#include <string.h>

void spins_filename_timeseries(char* name, int par_q, int par_L,
								int par_Nb, int par_nb,
								double par_B_start, double par_B_inc,
								int par_sim,
								int par_samples){
	char macro_str[16];

	if(q>2){
		sprintf(macro_str,"q%d", par_q);
		strcat(name, macro_str);
	}
	sprintf(macro_str,"L%d", par_L);
	strcat(name, macro_str);
	sprintf(macro_str,"Nb%d", par_Nb);
	strcat(name, macro_str);
	sprintf(macro_str,"nb%d", par_nb);
	strcat(name, macro_str);
	sprintf(macro_str,"Bs%d", (int)(1000*par_B_start));
	strcat(name, macro_str);
	sprintf(macro_str,"Bi%d", (int)(1000*par_B_inc));
	strcat(name, macro_str);
	sprintf(macro_str,"SIM%d", par_sim);
	strcat(name, macro_str);
	sprintf(macro_str,"OF%d", par_samples);
	strcat(name, macro_str);
	strcat(name, ".txt");
}

void spins_filename_combined(char* name, int par_q, int par_L,
								int par_Nb, int par_nb,
								double par_B_start, double par_B_inc,
								int par_samples){
	char macro_str[16];

	if(q>2){
		sprintf(macro_str,"q%d", par_q);
		strcat(name, macro_str);
	}
	sprintf(macro_str,"L%d", par_L);
	strcat(name, macro_str);
	sprintf(macro_str,"Nb%d", par_Nb);
	strcat(name, macro_str);
	sprintf(macro_str,"nb%d", par_nb);
	strcat(name, macro_str);
	sprintf(macro_str,"Bs%d", (int)(1000*par_B_start));
	strcat(name, macro_str);
	sprintf(macro_str,"Bi%d", (int)(1000*par_B_inc));
	strcat(name, macro_str);
	sprintf(macro_str,"m%d", par_samples);
	strcat(name, macro_str);
	strcat(name, ".txt");
}

void spins_filename_instant(char* name, 
								int par_q,
								int par_L,
								int par_N,
								double par_B,
								int par_sweep){
	char macro_str[16];
	if(q>2){
		sprintf(macro_str,"q%d", par_q);
		strcat(name, macro_str);
	}
	sprintf(macro_str,"L%d", par_L);
	strcat(name, macro_str);
	sprintf(macro_str,"N%d", par_N);
	strcat(name, macro_str);
	sprintf(macro_str,"B%d", (int)(1000*par_B));
	strcat(name, macro_str);
	sprintf(macro_str,"S%d", par_sweep);
	strcat(name, macro_str);
	strcat(name, ".txt");
}


void spins_filename_T0(char* name, int par_q, int par_L){
	char macro_str[16];

	strcat(name, headersID);
	if(q>2){
		sprintf(macro_str,"q%d", par_q);
		strcat(name, macro_str);
	}
	sprintf(macro_str,"L%d", par_L);
	strcat(name, macro_str);
	sprintf(macro_str,"smp%d", samples);
	strcat(name, macro_str);
	sprintf(macro_str,"ts%d", (int)(1000*tic_start));
	strcat(name, macro_str);
	sprintf(macro_str,"dt%d", (int)(1000*tic_mult));
	strcat(name, macro_str);
	sprintf(macro_str,"tf%d", max_time);
	strcat(name, macro_str);
	strcat(name, ".txt");
}


void spins_filename_instant_T0(char* name, 
								int par_q,
								int par_L,
								double par_pic_tic){
	char macro_str[16];

	strcat(name, headersID);
	if(q>2){
		sprintf(macro_str,"q%d", par_q);
		strcat(name, macro_str);
	}
	sprintf(macro_str,"L%d", par_L);
	strcat(name, macro_str);
	sprintf(macro_str,"smp%d", samples);
	strcat(name, macro_str);
	sprintf(macro_str,"tic%d", (int)par_pic_tic);
	strcat(name, macro_str);
	sprintf(macro_str,"tf%d", max_time);
	strcat(name, macro_str);
	strcat(name, ".txt");
}
