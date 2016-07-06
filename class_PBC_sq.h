//N-fold square lattice header
//for the 2D Ising and Potts Models
//by Shane Carlson

void update_local_classes(int i, int j){

	calculate_class(inc(i), j     );
	calculate_class(i     , dec(j));
	calculate_class(dec(i), j     );
	calculate_class(i     , inc(j));

	calculate_class(i     , j     );
}

void subtract_local_members(int i, int j){

	members[ sc[inc(i)][j     ] ]--; 
	members[ sc[i     ][dec(j)] ]--; 
	members[ sc[dec(i)][j     ] ]--;
	members[ sc[i     ][inc(j)] ]--;

	members[ sc[i     ][j     ] ]--;
}

void add_local_members(int i, int j){

	members[ sc[inc(i)][j     ] ]++; 
	members[ sc[i     ][dec(j)] ]++; 
	members[ sc[dec(i)][j     ] ]++;
	members[ sc[i     ][inc(j)] ]++;

	members[ sc[i     ][j     ] ]++;
}
