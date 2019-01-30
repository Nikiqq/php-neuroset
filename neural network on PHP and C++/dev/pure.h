double pure_search(double mas[], int N) {
	setlocale(LC_ALL, "Russian");
	int count_choose= N/2;
    double **enter;// Создаем матрицу введенной размерности
	enter = new double *[count_choose]; // через массив указателей
    for (int i = 0; i < count_choose; i++) {
       enter[i] = new double [2];
    }
	double *Sq;
	Sq = new double[count_choose-1];

	for (int i = 0; i < count_choose; i++) {
		enter[i][0] = mas[2*i];
		enter[i][1] = mas[2*i +1];
	}
	double temp1, temp2, S,treug;
	S  = 0;
	for ( int i = 0; i < count_choose-1; i++ ){
		if (enter[i][1] > 0.5 &&  enter[i+1][1] > 0.5){
			treug = 0.5*0.5*(enter[i+1][0] - enter[i][0]);
			temp1 =( ((1-enter[i][1])* (enter[i+1][0] - enter[i][0])) +(enter[i+1][0] - enter[i][0]) )* enter[i][1]/2; 
			temp2 = ( ((1-enter[i+1][1])* (enter[i+1][0] - enter[i][0])) +(enter[i+1][0] - enter[i][0]) )* enter[i+1][1]/2;
			S =  S + temp1+temp2 - treug;
			Sq[i] = S;
		}else {
			if (enter[i][1] <= 0.5 && enter[i][1] < enter[i+1][1] ){
				temp2 = ( ((1-enter[i+1][1])* (enter[i+1][0] - enter[i][0])) +(enter[i+1][0] - enter[i][0]) )* enter[i+1][1]/2;
				temp1 =  (enter[i][1]* (enter[i+1][0] - enter[i][0]))*0.5*enter[i][1];
				S= S+ temp1 +temp2;
				Sq[i] = S;

			}else {
				temp1 =( ((1-enter[i][1])* (enter[i+1][0] - enter[i][0])) +(enter[i+1][0] - enter[i][0]) )* enter[i][1]/2;
				temp2 =  ((enter[i+1][1])* (enter[i+1][0] - enter[i][0]))*0.5*enter[i+1][1];
				S = S + temp1 +temp2;
				Sq[i] = S;
			}
		}
	}
	double Sq_mid = S/2;
	double Sq_mid_dif;
	int ind = 0;
	double x = 0, h = 0.0001;								//Точность расчётов ( h = е-03 -> точность = е-02)
	while (Sq_mid > Sq[ind] && ind < count_choose)
		ind++;	
	if (ind != 0) {Sq_mid_dif = Sq_mid - Sq[ind-1];} else  {Sq_mid_dif = Sq_mid;}
	temp1 = 0;
	while (temp1 < Sq_mid_dif){
		x = x+ h;
		if (enter[ind][1] > 0.5 &&  enter[ind+1][1] > 0.5){
			if (x <= (1-enter[ind][1])*(enter[ind+1][0]-enter[ind][0])) S =  h * enter[ind][1]; 
			if (x > (1-enter[ind][1])*(enter[ind+1][0]-enter[ind][0]) && x <= (enter[ind+1][0]-enter[ind][0])/2) S = h *0.5* ( (((enter[ind+1][0]-enter[ind][0]) -x+h)/(enter[ind+1][0]-enter[ind][0])) + (((enter[ind+1][0]-enter[ind][0])  -x)/(enter[ind+1][0]-enter[ind][0])) ) ;
			if (x > (enter[ind+1][0]-enter[ind][0])/2 && x <= enter[ind+1][1]*(enter[ind+1][0]-enter[ind][0]) ) S = h *0.5* ( ((x+h)/(enter[ind+1][0]-enter[ind][0])) + ((x)/(enter[ind+1][0]-enter[ind][0])) ) ;
			if (x > (1-enter[ind][1])*(enter[ind+1][0]-enter[ind][0]) && x <= enter[ind+1][0] ) S =  h * enter[ind+1][1]; 
		}else{

			if (enter[ind][1] <= enter[ind+1][1] ){
				if (x <= (enter[ind][1])*(enter[ind+1][0]-enter[ind][0])) S =  h * enter[ind][1]; 
				if (x > (enter[ind][1])*(enter[ind+1][0]-enter[ind][0]) && x <= (enter[ind+1][1])*(enter[ind+1][0]-enter[ind][0])) S = h *0.5* ( ((x+h)/(enter[ind+1][0]-enter[ind][0])) + ((x)/(enter[ind+1][0]-enter[ind][0])) ) ;
				if (x > (enter[ind+1][1])*(enter[ind+1][0]-enter[ind][0]) && x <= enter[ind+1][0]) S =  h * enter[ind+1][1]; 
			}
			if (enter[ind][1] >  enter[ind+1][1]){
				if (x <= (1-enter[ind][1])*(enter[ind+1][0]-enter[ind][0])) S =  h * enter[ind][1]; 
				if (x > (1-enter[ind][1])*(enter[ind+1][0]-enter[ind][0]) && x <= (1-enter[ind+1][1])*(enter[ind+1][0]-enter[ind][0])) S = h *0.5* ( (((enter[ind+1][0]-enter[ind][0]) - x+h)/(enter[ind+1][0]-enter[ind][0])) + (((enter[ind+1][0]-enter[ind][0])  -x)/(enter[ind+1][0]-enter[ind][0])) ) ;
				if (x > (1-enter[ind+1][1])*(enter[ind+1][0]-enter[ind][0]) && x <= enter[ind+1][0] ) S =  h * enter[ind+1][1]; 
			}
		}
		temp1 = temp1 + S;
	}
	Fuck:
	//------Delete
	x= enter[ind][0] + x;
	for ( int i = 0; i < count_choose; i++ )
	{
		delete [] enter[ i ];
	}
	delete [] enter; 
	delete [] Sq;
	return x;
}