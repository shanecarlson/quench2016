//Smart N-fold square lattice header
//for the 2D Pott Models
//by Shane Carlson

void update_local_classes(int i, int j){
	int s1=s[i][j]; //the new spin state at i,j

	if( dc[inc(i)][j]&(1<<s1) ){ //if s[i][j] is newly a color that was dominant at inc(i),j
		dc[inc(i)][j] = (1<<s1) + (1<<16); //s[i][j] now the sole dominant color at inc(i),j
		sc[inc(i)][j] = s1==s[inc(i)][j] ? 0 : 1; //sc[inc(i)][j] either "stuck" or "must flip"
	}
	else
		calculate_class(inc(i), j     );

	if( dc[i][dec(j)]&(1<<s1) ){
		dc[i][dec(j)] = (1<<s1) + (1<<16);
		sc[i][dec(j)] = s1==s[i][dec(j)] ? 0 : 1;
	}
	else
		calculate_class(i     , dec(j));

	if( dc[dec(i)][j]&(1<<s1) ){
		dc[dec(i)][j] = (1<<s1) + (1<<16);
		sc[dec(i)][j] = s1==s[dec(i)][j] ? 0 : 1;
	}
	else
		calculate_class(dec(i), j     );

	if( dc[i][inc(j)]&(1<<s1) ){
		dc[i][inc(j)] = (1<<s1) + (1<<16);
		sc[i][inc(j)] = s1==s[i][inc(j)] ? 0 : 1;
	}
	else
		calculate_class(i     , inc(j));

	if(sc[i][j]==1)
		sc[i][j]=0;
	else
		calculate_class(i     , j     );
}
