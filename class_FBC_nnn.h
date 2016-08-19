//N-fold square lattice header
//for the 2D Ising and Potts Models
//by Shane Carlson

void update_local_classes(int i, int j){

	if(i<L-1)
		calculate_class(i+1, j  );
	if(j>0)
		calculate_class(i  , j-1);
	if(i>0)
		calculate_class(i-1, j  );
	if(j<L-1)
		calculate_class(i  , j+1);

	if(i<L-1 && j<L-1)
		calculate_class(i+1, j+1);
	if(i>0 && j>0)
		calculate_class(i-1, j-1);

	if(i>0 && j<L-1)
		calculate_class(i-1, j+1);
	if(i<L-1 && j>0)
		calculate_class(i+1, j-1);

	calculate_class(i,j);
}
