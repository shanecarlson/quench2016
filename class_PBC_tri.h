//N-fold triangular lattice header
//for the 2D Ising and Potts Models
//by Shane Carlson

void update_local_classes(int i, int j){

	calculate_class(inc(i), j     );
	calculate_class(i     , dec(j));
	calculate_class(dec(i), j     );
	calculate_class(i     , inc(j));

	calculate_class(inc(i), inc(j));
	calculate_class(dec(i), dec(j));

	calculate_class(i     , j     );
}
