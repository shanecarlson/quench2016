//N-fold algorithms lattice header
//for the 2D Ising and Potts Models
//by Shane Carlson

void update_all_classes(){

	for(int i=0;i<L;i++)
		for(int j=0;j<L;j++)
			calculate_class(i, j);
}

void count_all_members(){

	for(int l=0;l<n_fold;l++)
		members[l]=0;
	for(int i=0;i<L;i++)
		for(int j=0;j<L;j++)
			members[sc[i][j]]++;
}


double calculate_QN(){
	double QN=0;

	for(int l=1; l<n_fold; l++)
		QN+=p_flip[l]*members[l];
	return QN;
}

int draw_class(double QN){
	int newclass;
	double tower=0;
	double threshold=QN*drand48(); //0 to QN

	for(int l=1; l<n_fold && tower<=threshold; l++){
		tower+=p_flip[l]*members[l];
		if(tower>threshold)
			newclass=l;
	}
	return newclass;
}

void draw_site(int* x, int* y, int l){
	int count=0;
	int stop=(int)(drand48()*members[l]+1); //1 to members

	for(int i=0;i<L && count<stop;i++){
		for(int j=0;j<L && count<stop;j++){
			if(sc[i][j]==l)
				count++;
			if(count==stop){
				*x=i;
				*y=j;
			}
		}
	}
}

void T0_nfold_step(double QN){
	int i, j;
	int sclass=draw_class(QN);

	draw_site(&i, &j, sclass);
	subtract_local_members(i, j);
	flip_spin(i, j);
	p[i][j]++; //updates persistence
	update_local_classes(i, j);
	add_local_members(i, j);
	blocked_state = members[0]==L*L? 1 : 0;
}
