void generation(double * mas[], int N, int M) { 
	for(int i = 0; i < N ; i++){
		int count = 0;
		int kol_zak =  1 + rand()%3; // количество активных подзаключений
		int pos = rand()%(6-kol_zak); // коэффициент позиции для рандома
		for(int j = 1; j < M - 1; j += 2){ // заполняем степени принадлежности
			if( (j-1)/2 >= pos && count < kol_zak){
				mas[i][j] = double(rand()%10)/10 + 0.1;
				count++;
			}
			else {
				mas[i][j] = 0;
			}		
		}
		for(int j = 0; j < M - 2; j +=2) { // заполняем координаты
			mas[i][j] = -10 + 4 * j/2 + double(rand()%41)/10;
		}
		mas[i][M - 1] = pure_search(mas[i], M - 1); 
		 
	}
}