//N-fold triangular lattice header
//for the 2D Ising and Potts Models
//by Shane Carlson

void subtract_local_members(int i, int j){

	members[ sc[inc(i)][j     ] ]--; 
	members[ sc[i     ][dec(j)] ]--; 
	members[ sc[dec(i)][j     ] ]--;
	members[ sc[i     ][inc(j)] ]--;

	members[ sc[inc(i)][inc(j)] ]--;
	members[ sc[dec(i)][dec(j)] ]--;

	members[ sc[i     ][j     ] ]--;
}

void add_local_members(int i, int j){

	members[ sc[inc(i)][j     ] ]++; 
	members[ sc[i     ][dec(j)] ]++; 
	members[ sc[dec(i)][j     ] ]++;
	members[ sc[i     ][inc(j)] ]++;

	members[ sc[inc(i)][inc(j)] ]++;
	members[ sc[dec(i)][dec(j)] ]++;

	members[ sc[i     ][j     ] ]++;
}
