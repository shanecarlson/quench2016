//Potts model lattice header
//for the 2D Potts Model
//by Shane Carlson

double drand48();

int s[L_max][L_max]; //array of spins s(x,y)
int s_proposed; //proposed color for a flip

int E; //current energy
int EC; //energy contribution

static inline int inc(int k){
	return k<L-1 ? k+1 : 0;
}

static inline int dec(int k){
	return k>0 ? k-1 : L-1;
}

static inline int wrap(int k, int dk){

	if(dk>0){
		if(k+dk>L-1)
			return k+dk-L;
		else
			return k+dk;
	}
	if(dk<0){
		if(k+dk<0)
			return k+dk+L;
		else
			return k+dk;
	}
	else
		return k;
}

static inline int bond(int spin1, int spin2){
	return spin1==spin2 ? -1 : 0;
}

void initialize_lattice_to_middle(){
	int color=(int)((float)q/2.0);

	for(int i=0;i<L;i++)
		for(int j=0;j<L;j++)
			s[i][j]=color;
}

void initialize_lattice_random_m0(){
	int startpop=(int)(L*L/(float)q);
	int pop[q], i, j;

	for(int clr=0; clr<q; clr++)
		pop[clr]=startpop;

	for(int clr=0; clr<q && startpop*q+clr+1<L*L; clr++)
		pop[clr]++;

	for(i=0;i<L;i++)
		for(j=0;j<L;j++)
			s[i][j]=0;

	for(int clr=1; clr<q; clr++){
		for(int k=0; k<pop[clr]; k++){
			do{
				i=(int)(drand48()*L);
				j=(int)(drand48()*L);
			}while(s[i][j]!=0);
			s[i][j]=clr;
		}
	}
}

void initialize_lattice_random(){

	for(int i=0;i<L;i++)
		for(int j=0;j<L;j++)
			s[i][j] = (int)(drand48()*q); //random int from 0 to q
}

int first_top_color(){
	int count[q];
	int max_count=0;
	int top=-1;

	for(int col=0; col<q; col++)
		count[col]=0;

	for(int i=0;i<L;i++)
		for(int j=0;j<L;j++)
			count[s[i][j]]++;

	for(int col=0; col<q; col++)
		if(count[col]>max_count)
			max_count=count[col];

	for(int col=0; col<q && top==-1; col++)
		if(count[col]==max_count)
			top=col;

	return top;
}


int calculate_magnetization(int resp_color){
	int M=0;

	for(int i=0;i<L;i++)
		for(int j=0;j<L;j++)
			M += s[i][j]==resp_color ? 1 : -1;
	return M;
}

int color_count_spread(){
	int count[q];
	int max_count=0;
	int min_count=L*L;

	for(int col=0; col<q; col++)
		count[col]=0;

	for(int i=0;i<L;i++)
		for(int j=0;j<L;j++)
			count[s[i][j]]++;

	for(int col=0; col<q; col++){
		if(count[col]>max_count)
			max_count=count[col];
		if(count[col]<min_count)
			min_count=count[col];
	}

	return max_count-min_count;
}
