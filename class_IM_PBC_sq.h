//Smart N-fold square lattice header
//for the 2D Ising Model
//by Shane Carlson

void update_local_classes(int i, int j){

	if( !( (sc[inc(i)][j]==0 && s[i][j]==s[inc(i)][j]) || (sc[inc(i)][j]==2 && s[i][j]!=s[inc(i)][j]) ) )
		calculate_class(inc(i), j     );
	if( !( (sc[i][dec(j)]==0 && s[i][j]==s[i][dec(j)]) || (sc[i][dec(j)]==2 && s[i][j]!=s[i][dec(j)]) ) )
		calculate_class(i     , dec(j));
	if( !( (sc[dec(i)][j]==0 && s[i][j]==s[dec(i)][j]) || (sc[dec(i)][j]==2 && s[i][j]!=s[dec(i)][j]) ) )
		calculate_class(dec(i), j     );
	if( !( (sc[i][inc(j)]==0 && s[i][j]==s[i][inc(j)]) || (sc[i][inc(j)]==2 && s[i][j]!=s[i][inc(j)]) ) )
		calculate_class(i     , inc(j));

	if(sc[i][j]==2)
		sc[i][j]=0;
	else if(sc[i][j]==0)
		sc[i][j]=2;
	else
		sc[i][j]=1;
}
