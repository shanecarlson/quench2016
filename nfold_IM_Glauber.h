//2D Ising Model Glauber n-fold header
//by Shane Carlson

#define n_fold 3 //number of spin classes

int sc[L_max][L_max]; //array that stores spin class of s[i][j]
int members[n_fold]; //stores the number of members of each class
double p_flip[n_fold]; //stores the transition probability of each class
bool blocked_state; //1 if state is blocked, 0 if not

static inline void flip_spin(int i, int j){ s[i][j]^=1; }

void calculate_class(int i, int j){

	energy_contribution(i, j);
	if(EC<0){ sc[i][j]=0; } //stuck
	if(EC==0){ sc[i][j]=1; } //equal energy
	if(EC>0){ sc[i][j]=2; } //must flip
}

void set_flip_probabilities(){
	p_flip[0]=0;
	p_flip[1]=0.5;
	p_flip[2]=1.0;
}
