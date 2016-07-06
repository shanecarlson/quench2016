//timeseries file naming header for quenching procedure
//by Shane Carlson

#include <string.h>

void spins_foldername_T0(char* name, int par_q, int par_L){
	char macro_str[16];

	strcat(name, headersID);
	if(q>2){
		sprintf(macro_str,"_q%d", par_q);
		strcat(name, macro_str);
	}
	sprintf(macro_str,"_L%d", par_L);
	strcat(name, macro_str);
	sprintf(macro_str,"smp%d", samples);
	strcat(name, macro_str);
	sprintf(macro_str,"thm%d", therm);
	strcat(name, macro_str);
	sprintf(macro_str,"ts%d", (int)(1000*tic_start));
	strcat(name, macro_str);
	sprintf(macro_str,"dt%d", (int)(1000*tic_mult));
	strcat(name, macro_str);
	sprintf(macro_str,"tf%d", max_time);
	strcat(name, macro_str);
}

void spins_filename_instant_T0(char* name, int par_L, int par_sim, int par_pic){
	char macro_str[16];

	sprintf(macro_str,"L%d_", par_L);
	strcat(name, macro_str);
	sprintf(macro_str,"sim%d_", par_sim);
	strcat(name, macro_str);
	sprintf(macro_str,"num%d", par_pic);
	strcat(name, macro_str);
	strcat(name, ".txt");
}
