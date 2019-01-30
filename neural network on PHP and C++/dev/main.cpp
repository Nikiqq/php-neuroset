#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <string>
#include "pure.h"				//  модуль решения без сети
#include "generation.h"			// модуль генерации

#define kol_enter 10			//количество входов


//значения весов, альфы и скорости по умолчанию (ВНИМАНИЕ: значения по умолчанию нужны для создания нейронов, значения скорости и весовых коэффициентов изменяются в модуле обучения learning, который описан ниже)
#define defaultW0 0.25 
#define defaultW 0.2
#define defaultalf 1
#define defaultV 1
void learning(int count_learn, double * mas[], int N, int M, int kol_neuron);
using namespace std;

class Neuron {                  // класс Нейрон
private:
    vector<long double> w;      // вектор весовых коэффициентов
    long double w0;             // единичный сдвиг
    double alf;                 // альфа 
    double sigm;                // невязка  
    double S;                   // состояние нейрона
    vector<double> x;           // входной вектор
    double y;                   // выход вектора
public:
                                // конструкторы   
    Neuron() {
        w0 = defaultW0;
        alf = defaultalf;
        for (int i = 0; i < kol_enter; i++) {
            w.push_back(defaultW);
        }
    };
    Neuron(int cX, long double cW0, double cAlf) {
        w0 = cW0;
        alf = cAlf;
        for (int i = 0; i < kol_enter; i++) {
            w.push_back(defaultW);
        }
    };
    Neuron(int count) {
        w0 = defaultW0;
        alf = defaultalf;
        for (int i = 0; i < count; i++) {
            w.push_back(defaultW);
        }
    };
 
    // методы получения и установления значений параетров    
    long double getw0() {
        return w0;
    }
    /*double getS() {
        return S;
    }*/
    void setw0(long double z) {
        w0 = z;
    }    
    /*double getX(int i) {
        return x[i];
    }*/
    void setX(vector<double> arrX) {
        x.assign(arrX.begin(), arrX.end());  
    }
    vector<long double> getW(vector<long double> arrX) {
        arrX.assign(w.begin(), w.end());  
        return arrX;
    }
    long double getW(int i) {
        return w[i];
    }
    void setW(vector<long double> arrX) {
        w.clear();
        w.assign(arrX.begin(), arrX.end());  
    }
    /*double getalf() {
        return alf;
    }
    void setalf(double z) {
        alf = z;
    }*/
        
    // Расчет состояния нейрона        
    void status() {
        S = 0;
        for (int i = 0; i < x.size(); i++) {
            S += w[i] * x[i];
        }
        S += w0;
    }
 
    // Активационная функция         
    void funk() {
        y = 1/ (exp(-alf*S) + 1);
    }
 
    //   Метод workNeuron - получение входных данных и возварт результата работа нейрона 
    double workNeuron(vector<double> arrX) {
        x.assign(arrX.begin(), arrX.end());  
        status();
        funk();
        return y;
    }
 
    //    Метод training  - обучение нейрона. trX - вектор входных данных обучающего примера , trY  - значение ответа обучающего примера, trV - скорость обучения  
    double training(vector<double> trX, double trY, double trV) {
        double outY;
        double dlt;
        outY = workNeuron(trX);
        dlt = trY - outY;
        sigm =  dlt * alf * outY * (1-outY);
        return sigm; 
    }
    void training(vector<double> trX, double trV, double sigma_last, long double Wpre) {
		double outY;
        outY = workNeuron(trX);
        sigm = sigma_last * Wpre * alf * outY * (1 - outY);
		// std::cout << sigm << Wpre << endl;
        for (int i = 0; i < w.size(); i++) {
            w[i] = w[i] + trV*sigm*x[i];
        }
        w0 = w0 + trV*sigm;
    }
	void change_w_for_last(vector<double> trX, double sigma_last, double trV) { 
		double outY; 
		outY = workNeuron(trX); 
		for (int i = 0; i < w.size(); i++) { 
			w[i] = w[i] + trV*sigma_last*x[i]; 
		} 
		w0 = w0 + trV*sigma_last; 
		}
};
int main() {
	setlocale(LC_ALL, "Russian");
	srand ( time(NULL) );
	int  kol_neuron = 15;		//количество нейронов
	int N = 900;				// количество примеров для обучения
	int count_learn = 20000;	//количество обучающих эпох
	int const step = 5;			// выборка составляет 5 пар координат + альфа
	int const M = kol_enter + 1;// количество столбцов в матрице
	bool learn = false;			// переменная обучения
	bool test = true;			// переменная теста
	int T = N/5;				// количество примеров для теста
	/*------------МЕНЮ-------------------*/
	string Control;
	char bool_temp = ' '; 
	int _temp = 0;
	Control = "^_^";
	std::cout.setf(ios::boolalpha);
	while (!(Control == "Start" || Control == "start")){
		if (Control == "1"){
			std::cout <<"\nОбучение сети, параметры по умолчанию:";
			Control = "show";
		}
		if (Control == "2"){
reask:
			std::cout <<"\nТестирование сети. \nПроверить с помощью сгенерированной тестовой выборки? [Y/N] ";
			std::cout << "\n>";std::cin >> bool_temp;
			if(bool_temp == 'Y' || bool_temp == 'y') test = true;
			else if (bool_temp == 'N' || bool_temp == 'n') test = false;
			else {std::cout << "Не понял ответа\n"; goto reask;}
			Control = "show";
		}
		if (Control == "neuron" && _temp != 0){
			std::cout <<"Новое значание количества нейровнов = ";std::cin >> kol_neuron;
			Control = "show";
		}
		if (Control == "N" && _temp == 1){
			std::cout <<"Новое значание количества примеров = ";std::cin >> N;
			Control = "show";
		}
		if (Control == "T" && _temp == 2 &&  test){
			std::cout <<"Новое значание количества примеров = ";std::cin >> T;
			Control = "show";
		}
		if (Control == "count" && _temp != 0){
			std::cout <<"Новое значание количества обучающих эпох = ";std::cin >> count_learn;
			Control = "show";
		}
		if ((Control == "Show" || Control == "show") && _temp != 0)	{
			std::cout << "\n--------------------------------------------------\n"
				<<"Количество нейронов ( 'neuron' ) = " <<  kol_neuron <<endl
				<<"Количество обучающих эпох ( 'count' ) = " << count_learn <<endl;
			if (_temp == 1) {
				std::cout
					<<"Количество примеров для обучения ( 'N' ) = " << N <<endl
					<< "Режим: обучение нейронной сети";
			}else{
				if (_temp == 2 && test) {
					std::cout 
						<<"Количество примеров для тестирования ( 'T' ) = " << T <<endl
						<< "Режим: тестирование нейронной сети (сгенерированная выборка)";
				}else{
					std::cout << "Режим: тестирование нейронной сети (одиночный пример)";
				}
			}
			std::cout <<"\n--------------------------------------------------\n";

		}
		if (Control == "3" || Control == "help")	
		std::cout 
			<<"\n                       * Справка *\n"
			<<"\nПосле выбора режима, будут выведены соответствующие праметры"
			<<"\nДля изменения того или иного парметра введите его имя из (' ')"
			<<"\nДля отоборожения текущего состояния всех параметорв 'Show'"
			<<"\nЕсли вас устраивают все параметры введите 'Start'"
			<<"\n\n:::::::::::::::::::::::::Внимание!::::::::::::::::::::::::::::\n"
			<<"\n\t1)Имя файла для подгрузки коэффициентов: 'weight_for_program.txt' "<<endl
			<<"\n\t2) Для тестовой выборки с весовыми из файла убедитесь, "<<endl
			<<"\tчто количество нейронов равно количеству нейронов, "<<endl
			<<"\tкоторые были установленны при получении файла."<<endl
			<<"\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
		if (Control == "^_^")			//-------------------------------------------------------------приветсвие
		std::cout << "\n--------------Нейронная сеть ( Обратное распространение ошибки )---------------\n"
			<<"Выбирите режим:" <<endl
			<<"1 - Обучение сети" <<endl
			<<"2 - Проверка сети (тестовая выборка/тестовый пример)" <<endl
			<<"3 - Справка" <<endl;
		Control = "";
		std::cout << "\n>";std::cin >> Control; //-----------------------------------------------------команда
		if (Control == "1")  {
			_temp = 1;
			learn = true;
		}
		if (Control == "2"){
			learn = false;
			_temp = 2;
		}
		if ((Control == "Start" || Control == "start") && _temp == 0)  Control = "^_^"; //------------закоментить, если нужен запуск с параметрами по умолчанию
	}
	/*------------Окончание МЕНЮ-------------------*/


	if(learn) {
		double**enter = new double *[N];	// массив примеров
        for (int i = 0; i < N; i++) {
		   enter[i] = new double [M];		// выделение памяти под обучающие примеры
		}
		generation(&enter[0], N, M);
		/*for (int i = 0; i < N; i ++){
			for(int j = 0; j < M; j ++){
				cout << enter[i][j] << " | " ;
			}
			cout << endl;
		}*/
		learning(count_learn, &enter[0], N, M, kol_neuron);
	}
	else {
		Neuron *first_layer = new Neuron [kol_neuron];		// нейроны 1 слоя
		Neuron last(kol_neuron);
		ifstream fwin("weight_for_program.txt"); // заполнение из файла
		long double temp;
		vector<long double> temp_w;
		if (fwin.is_open()){
			for(int i = 0; i < kol_neuron; i++){
				fwin >> temp;
				first_layer[i].setw0(temp);
				for (int j = 0; j < kol_enter; j++){
					fwin >> temp;
					temp_w.push_back(temp);
				}
				first_layer[i].setW(temp_w);
				temp_w.clear();
			}
			temp_w.clear();
			fwin >> temp;
			last.setw0(temp);
			for (int i = 0; i < kol_neuron; i++) {
				fwin >> temp;
				temp_w.push_back(temp);
			}
			last.setW(temp_w);
		}
		else{
			std::cout << "Невозможно открыть файл" << endl;
			fwin.close();
			return 0;
		}
		fwin.close();
		if(test) {
			double**test = new double *[T];		// массив примеров
			for (int i = 0; i < T; i++) {
			   test[i] = new double [M];		// выделение памяти под тестовые примеры
			}
			generation(&test[0], T, M);
			vector<double> X_Alf_enter, Y_first_exit;		// вектор входов, выходов 1 слоя
			double error = 0.0, Yras = 0.0, error_d = 0.0;
			int count_err = 0;
			for(int i = 0; i < T; i++){
				X_Alf_enter.clear();
				Y_first_exit.clear();
				for(int j = 0; j < M - 1; j += 2){
					X_Alf_enter.push_back((test[i][j] + 10)/20); // формируем вектор входов нормализованных X и степеней принадлежности
					X_Alf_enter.push_back(test[i][j + 1] ); 
				}
				for (int k = 0; k < kol_neuron; k++){
					Y_first_exit.push_back(first_layer[k].workNeuron(X_Alf_enter)); // получаем выходы 1 слоя
					//cout << "выходы 1 слоя: " << Y_first_exit[k]<< endl;
				}
				Yras = last.workNeuron(Y_first_exit);
				error += ((test[i][M-1] + 10)/20 - Yras)*((test[i][M-1] + 10)/20 - Yras);
				error_d += (test[i][M-1] - (Yras*20-10)) *(test[i][M-1] - (Yras*20-10));
				count_err++;
				std::cout << "Нормализованные выходы сети - реальный: " << Yras  << " --- " << (test[i][M-1] + 10)/20 << endl;
				std::cout << "Денормализованные выходы сети - реальный: " << Yras*20-10  << " --- " << test[i][M-1] << endl << endl;
			}
			std::cout << "\nНормализованная ошибка = " << sqrt(error/count_err) << endl;
			std::cout << "\nДенормализованная ошибка = " << sqrt(error_d/count_err) << endl;
		}
		else{
			double*test = new double [M];
			/*------------МЕНЮ-------------------*/	
			Control = "^_^";
			while (Control != "N" && Control != "n"){
				if (Control == "Y" || Control == "y" || Control == "^_^") {
					std::cout << "\nВедите Х и Alpha соотвественно (каждую пару на новой строчке) \n";
					for (int i = 0; i < M-1; i+=2) {
						cin >> test[i] >> test[i+1];
					}
					test[M-1] = pure_search(test,M-1);
					vector<double> X_Alf_enter, Y_first_exit;		// вектор входов, выходов 1 слоя
					double Yras = 0.0;
					X_Alf_enter.clear();
					Y_first_exit.clear();
					for(int j = 0; j < M - 1; j += 2){
						X_Alf_enter.push_back((test[j] + 10)/20); // формируем вектор входов нормализованных X и степеней принадлежности
						X_Alf_enter.push_back(test[j + 1] ); 
					}
					for (int k = 0; k < kol_neuron; k++){
						Y_first_exit.push_back(first_layer[k].workNeuron(X_Alf_enter)); // получаем выходы 1 слоя
					}
					Yras = last.workNeuron(Y_first_exit);
					std::cout << "Для матрицы значений:\nX";
					for(int j = 0; j < M - 1; j += 2){
						std::cout << "\t"<<test[j];
					}
					std::cout << "\nAlpha";
					for(int j = 1; j < M - 1; j += 2){
						std::cout << "\t"<<test[j];
					}

					std::cout << "\nНормализованные выходы сети - реальный: " << Yras  << " --- " << (test[M-1] + 10)/20 << endl;
					std::cout << "Денормализованные выходы сети - реальный: " << Yras*20-10  << " --- " << test[M-1] << endl << endl;
				}
				std::cout << "Ещё пример? [Y/N]";
				std::cout << "\n>";std::cin >> Control;
			}
			/*------------МЕНЮ-------------------*/	
			delete [] test;
		}
	}
	_getch();
    return 0;
}

void learning(int count_learn, double * mas[], int N, int M, int kol_neuron) {
	int*q = new int[N];
	for(int i = 0; i < N; i++) {
		q[i] = i;
	}
	Neuron *first_layer = new Neuron [kol_neuron];		// нейроны 1 слоя
    Neuron last(kol_neuron);			// выходной нейрон
	vector<long double> begin;			// инициализация весовых коэффициентов малыми случайными велечинами
	for (int i = 0; i < kol_neuron; i++){
		begin.clear();
		long double w0 = 0.25 - double(rand()%10)/100;
		//cout << "w0 = " << w0 << endl;
		for (int j = 0; j < kol_enter; j++){
			begin.push_back(0.4 - double(rand()%35)/100);
			//cout << "w = " << begin[j] << endl;
		}
		first_layer[i].setw0(w0);
		first_layer[i].setW(begin);
	}
	double V = 0.3, dV = 0.2, Yras = 0.0, sigma_last;
	vector<double> X_Alf_enter, Y_first_exit;	// вектор входов, выходов 1 слоя
	for(int period = 0; period < count_learn; period++){
		/*if(period != 0 && period % 20000 == 0){
			V -= 0.01;
		}*/
		double error = 0.0;
		int count_err = 0;
		/*for(int i = 0; i < 10; i++){
			std::cout << q[i] << " ";
		}
		std::cout << endl;*/
		for(int i = 0; i < N; i++){
			X_Alf_enter.clear();
			Y_first_exit.clear();
			for(int j = 0; j < M - 1; j += 2){
				X_Alf_enter.push_back((mas[q[i]][j] + 10)/20); // формируем вектор входов нормализованных X и степеней принадлежности
				X_Alf_enter.push_back(mas[q[i]][j + 1] ); 
			}
			for (int k = 0; k < kol_neuron; k++){
				Y_first_exit.push_back(first_layer[k].workNeuron(X_Alf_enter)); // получаем выходы 1 слоя
				//cout << "выходы 1 слоя: " << Y_first_exit[k]<< endl;
			}
			sigma_last = last.training(Y_first_exit, (mas[q[i]][M-1] + 10)/20, V); // сигма последнего нейрона
			//cout << "Невязка выходного слоя: " << sigma_last << endl;
			for (int k = 0; k < kol_neuron; k++){ 
				first_layer[k].training(X_Alf_enter, V, sigma_last, last.getW(k)); // вычисляем невязка 1 слоя и меняем весовые коэффициенты
			}
			for (int k = 0; k < kol_neuron; k++){
				last.change_w_for_last(Y_first_exit, sigma_last, V); // пересчитываем весовые коэффициенты для последнего нейрона
			}
			Yras = last.workNeuron(Y_first_exit);
			//cout << "Выход 2 слоя: " << Yras << endl;
			error += ((mas[q[i]][M-1] + 10)/20 - Yras)*((mas[q[i]][M-1] + 10)/20 - Yras);
            count_err++;
		}
		std::cout << "\nОшибка = " << sqrt(error/count_err) << " ------ "<< period << endl;
		random_shuffle(q, q + N );
	}
	ofstream fwout("weight_for_program.txt");
	for(int i = 0; i < kol_neuron; i++){
		//fwout << i + 1 << "нейрон" << endl ;  
		fwout << first_layer[i].getw0() << "\n";
		for (int j = 0; j < kol_enter; j++){
			fwout << first_layer[i].getW(j) << "\n";
		}
	}
	//fwout << "выходной нейрон" << endl ;
	fwout << last.getw0() << "\n" ;
	for(int i = 0; i < kol_neuron; i++){
		fwout << last.getW(i) << "\n";
	}
	

	std::cout << "\nvse ok";
	fwout.close();
}