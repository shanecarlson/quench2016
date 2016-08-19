//Local state count for the next nearest neighbor square lattice with periodic boundary conditions
//for the 2D Potts Model
//by Shane Carlson

void nearest_neighbors(int i, int j, int* count){

	count[ s[inc(i)][j     ] ]++;
	count[ s[dec(i)][j     ] ]++;
	count[ s[i     ][inc(j)] ]++;
	count[ s[i     ][dec(j)] ]++;
	count[ s[dec(i)][dec(j)] ]++;
	count[ s[inc(i)][inc(j)] ]++;
	count[ s[dec(i)][inc(j)] ]++;
	count[ s[inc(i)][dec(j)] ]++;
}
