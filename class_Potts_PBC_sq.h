//Smart N-fold square lattice header
//for the 2D Pott Models
//by Shane Carlson

void update_local_classes(int i, int j){

	if( dc[inc(i)][j]&(1<<s[i][j]) ){ //if s[i][j] is newly a color that was dominant at inc(i),j
		dc[inc(i)][j] = (1<<s[i][j]) + (1<<16); //s[i][j] now the sole dominant color at inc(i),j
		sc[inc(i)][j] = s[i][j]==s[inc(i)][j] ? 0 : 1; //sc[inc(i)][j] either "stuck" or "must flip"
	}
	else
		calculate_class(inc(i), j     );

	if( dc[i][dec(j)]&(1<<s[i][j]) ){
		dc[i][dec(j)] = (1<<s[i][j]) + (1<<16);
		sc[i][dec(j)] = s[i][j]==s[i][dec(j)] ? 0 : 1;
	}
	else
		calculate_class(i     , dec(j));

	if( dc[dec(i)][j]&(1<<s[i][j]) ){
		dc[dec(i)][j] = (1<<s[i][j]) + (1<<16);
		sc[dec(i)][j] = s[i][j]==s[dec(i)][j] ? 0 : 1;
	}
	else
		calculate_class(dec(i), j     );

	if( dc[i][inc(j)]&(1<<s[i][j]) ){
		dc[i][inc(j)] = (1<<s[i][j]) + (1<<16);
		sc[i][inc(j)] = s[i][j]==s[i][inc(j)] ? 0 : 1;
	}
	else
		calculate_class(i     , inc(j));

	if(sc[i][j]==1)
		sc[i][j]=0;
	else
		calculate_class(i     , j     );
}
