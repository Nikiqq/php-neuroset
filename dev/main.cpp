#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <string>
#include "pure.h"				//  ������ ������� ��� ����
#include "generation.h"			// ������ ���������

#define kol_enter 10			//���������� ������


//�������� �����, ����� � �������� �� ��������� (��������: �������� �� ��������� ����� ��� �������� ��������, �������� �������� � ������� ������������� ���������� � ������ �������� learning, ������� ������ ����)
#define defaultW0 0.25 
#define defaultW 0.2
#define defaultalf 1
#define defaultV 1
void learning(int count_learn, double * mas[], int N, int M, int kol_neuron);
using namespace std;

class Neuron {                  // ����� ������
private:
    vector<long double> w;      // ������ ������� �������������
    long double w0;             // ��������� �����
    double alf;                 // ����� 
    double sigm;                // �������  
    double S;                   // ��������� �������
    vector<double> x;           // ������� ������
    double y;                   // ����� �������
public:
                                // ������������   
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
 
    // ������ ��������� � ������������ �������� ���������    
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
        
    // ������ ��������� �������        
    void status() {
        S = 0;
        for (int i = 0; i < x.size(); i++) {
            S += w[i] * x[i];
        }
        S += w0;
    }
 
    // ������������� �������         
    void funk() {
        y = 1/ (exp(-alf*S) + 1);
    }
 
    //   ����� workNeuron - ��������� ������� ������ � ������� ���������� ������ ������� 
    double workNeuron(vector<double> arrX) {
        x.assign(arrX.begin(), arrX.end());  
        status();
        funk();
        return y;
    }
 
    //    ����� training  - �������� �������. trX - ������ ������� ������ ���������� ������� , trY  - �������� ������ ���������� �������, trV - �������� ��������  
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
	int  kol_neuron = 15;		//���������� ��������
	int N = 900;				// ���������� �������� ��� ��������
	int count_learn = 20000;	//���������� ��������� ����
	int const step = 5;			// ������� ���������� 5 ��� ��������� + �����
	int const M = kol_enter + 1;// ���������� �������� � �������
	bool learn = false;			// ���������� ��������
	bool test = true;			// ���������� �����
	int T = N/5;				// ���������� �������� ��� �����
	/*------------����-------------------*/
	string Control;
	char bool_temp = ' '; 
	int _temp = 0;
	Control = "^_^";
	std::cout.setf(ios::boolalpha);
	while (!(Control == "Start" || Control == "start")){
		if (Control == "1"){
			std::cout <<"\n�������� ����, ��������� �� ���������:";
			Control = "show";
		}
		if (Control == "2"){
reask:
			std::cout <<"\n������������ ����. \n��������� � ������� ��������������� �������� �������? [Y/N] ";
			std::cout << "\n>";std::cin >> bool_temp;
			if(bool_temp == 'Y' || bool_temp == 'y') test = true;
			else if (bool_temp == 'N' || bool_temp == 'n') test = false;
			else {std::cout << "�� ����� ������\n"; goto reask;}
			Control = "show";
		}
		if (Control == "neuron" && _temp != 0){
			std::cout <<"����� �������� ���������� ��������� = ";std::cin >> kol_neuron;
			Control = "show";
		}
		if (Control == "N" && _temp == 1){
			std::cout <<"����� �������� ���������� �������� = ";std::cin >> N;
			Control = "show";
		}
		if (Control == "T" && _temp == 2 &&  test){
			std::cout <<"����� �������� ���������� �������� = ";std::cin >> T;
			Control = "show";
		}
		if (Control == "count" && _temp != 0){
			std::cout <<"����� �������� ���������� ��������� ���� = ";std::cin >> count_learn;
			Control = "show";
		}
		if ((Control == "Show" || Control == "show") && _temp != 0)	{
			std::cout << "\n--------------------------------------------------\n"
				<<"���������� �������� ( 'neuron' ) = " <<  kol_neuron <<endl
				<<"���������� ��������� ���� ( 'count' ) = " << count_learn <<endl;
			if (_temp == 1) {
				std::cout
					<<"���������� �������� ��� �������� ( 'N' ) = " << N <<endl
					<< "�����: �������� ��������� ����";
			}else{
				if (_temp == 2 && test) {
					std::cout 
						<<"���������� �������� ��� ������������ ( 'T' ) = " << T <<endl
						<< "�����: ������������ ��������� ���� (��������������� �������)";
				}else{
					std::cout << "�����: ������������ ��������� ���� (��������� ������)";
				}
			}
			std::cout <<"\n--------------------------------------------------\n";

		}
		if (Control == "3" || Control == "help")	
		std::cout 
			<<"\n                       * ������� *\n"
			<<"\n����� ������ ������, ����� �������� ��������������� ��������"
			<<"\n��� ��������� ���� ��� ����� �������� ������� ��� ��� �� (' ')"
			<<"\n��� ������������ �������� ��������� ���� ���������� 'Show'"
			<<"\n���� ��� ���������� ��� ��������� ������� 'Start'"
			<<"\n\n:::::::::::::::::::::::::��������!::::::::::::::::::::::::::::\n"
			<<"\n\t1)��� ����� ��� ��������� �������������: 'weight_for_program.txt' "<<endl
			<<"\n\t2) ��� �������� ������� � �������� �� ����� ���������, "<<endl
			<<"\t��� ���������� �������� ����� ���������� ��������, "<<endl
			<<"\t������� ���� ������������ ��� ��������� �����."<<endl
			<<"\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
		if (Control == "^_^")			//-------------------------------------------------------------����������
		std::cout << "\n--------------��������� ���� ( �������� ��������������� ������ )---------------\n"
			<<"�������� �����:" <<endl
			<<"1 - �������� ����" <<endl
			<<"2 - �������� ���� (�������� �������/�������� ������)" <<endl
			<<"3 - �������" <<endl;
		Control = "";
		std::cout << "\n>";std::cin >> Control; //-----------------------------------------------------�������
		if (Control == "1")  {
			_temp = 1;
			learn = true;
		}
		if (Control == "2"){
			learn = false;
			_temp = 2;
		}
		if ((Control == "Start" || Control == "start") && _temp == 0)  Control = "^_^"; //------------�����������, ���� ����� ������ � ����������� �� ���������
	}
	/*------------��������� ����-------------------*/


	if(learn) {
		double**enter = new double *[N];	// ������ ��������
        for (int i = 0; i < N; i++) {
		   enter[i] = new double [M];		// ��������� ������ ��� ��������� �������
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
		Neuron *first_layer = new Neuron [kol_neuron];		// ������� 1 ����
		Neuron last(kol_neuron);
		ifstream fwin("weight_for_program.txt"); // ���������� �� �����
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
			std::cout << "���������� ������� ����" << endl;
			fwin.close();
			return 0;
		}
		fwin.close();
		if(test) {
			double**test = new double *[T];		// ������ ��������
			for (int i = 0; i < T; i++) {
			   test[i] = new double [M];		// ��������� ������ ��� �������� �������
			}
			generation(&test[0], T, M);
			vector<double> X_Alf_enter, Y_first_exit;		// ������ ������, ������� 1 ����
			double error = 0.0, Yras = 0.0, error_d = 0.0;
			int count_err = 0;
			for(int i = 0; i < T; i++){
				X_Alf_enter.clear();
				Y_first_exit.clear();
				for(int j = 0; j < M - 1; j += 2){
					X_Alf_enter.push_back((test[i][j] + 10)/20); // ��������� ������ ������ ��������������� X � �������� ��������������
					X_Alf_enter.push_back(test[i][j + 1] ); 
				}
				for (int k = 0; k < kol_neuron; k++){
					Y_first_exit.push_back(first_layer[k].workNeuron(X_Alf_enter)); // �������� ������ 1 ����
					//cout << "������ 1 ����: " << Y_first_exit[k]<< endl;
				}
				Yras = last.workNeuron(Y_first_exit);
				error += ((test[i][M-1] + 10)/20 - Yras)*((test[i][M-1] + 10)/20 - Yras);
				error_d += (test[i][M-1] - (Yras*20-10)) *(test[i][M-1] - (Yras*20-10));
				count_err++;
				std::cout << "��������������� ������ ���� - ��������: " << Yras  << " --- " << (test[i][M-1] + 10)/20 << endl;
				std::cout << "����������������� ������ ���� - ��������: " << Yras*20-10  << " --- " << test[i][M-1] << endl << endl;
			}
			std::cout << "\n��������������� ������ = " << sqrt(error/count_err) << endl;
			std::cout << "\n����������������� ������ = " << sqrt(error_d/count_err) << endl;
		}
		else{
			double*test = new double [M];
			/*------------����-------------------*/	
			Control = "^_^";
			while (Control != "N" && Control != "n"){
				if (Control == "Y" || Control == "y" || Control == "^_^") {
					std::cout << "\n������ � � Alpha ������������� (������ ���� �� ����� �������) \n";
					for (int i = 0; i < M-1; i+=2) {
						cin >> test[i] >> test[i+1];
					}
					test[M-1] = pure_search(test,M-1);
					vector<double> X_Alf_enter, Y_first_exit;		// ������ ������, ������� 1 ����
					double Yras = 0.0;
					X_Alf_enter.clear();
					Y_first_exit.clear();
					for(int j = 0; j < M - 1; j += 2){
						X_Alf_enter.push_back((test[j] + 10)/20); // ��������� ������ ������ ��������������� X � �������� ��������������
						X_Alf_enter.push_back(test[j + 1] ); 
					}
					for (int k = 0; k < kol_neuron; k++){
						Y_first_exit.push_back(first_layer[k].workNeuron(X_Alf_enter)); // �������� ������ 1 ����
					}
					Yras = last.workNeuron(Y_first_exit);
					std::cout << "��� ������� ��������:\nX";
					for(int j = 0; j < M - 1; j += 2){
						std::cout << "\t"<<test[j];
					}
					std::cout << "\nAlpha";
					for(int j = 1; j < M - 1; j += 2){
						std::cout << "\t"<<test[j];
					}

					std::cout << "\n��������������� ������ ���� - ��������: " << Yras  << " --- " << (test[M-1] + 10)/20 << endl;
					std::cout << "����������������� ������ ���� - ��������: " << Yras*20-10  << " --- " << test[M-1] << endl << endl;
				}
				std::cout << "��� ������? [Y/N]";
				std::cout << "\n>";std::cin >> Control;
			}
			/*------------����-------------------*/	
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
	Neuron *first_layer = new Neuron [kol_neuron];		// ������� 1 ����
    Neuron last(kol_neuron);			// �������� ������
	vector<long double> begin;			// ������������� ������� ������������� ������ ���������� ����������
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
	vector<double> X_Alf_enter, Y_first_exit;	// ������ ������, ������� 1 ����
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
				X_Alf_enter.push_back((mas[q[i]][j] + 10)/20); // ��������� ������ ������ ��������������� X � �������� ��������������
				X_Alf_enter.push_back(mas[q[i]][j + 1] ); 
			}
			for (int k = 0; k < kol_neuron; k++){
				Y_first_exit.push_back(first_layer[k].workNeuron(X_Alf_enter)); // �������� ������ 1 ����
				//cout << "������ 1 ����: " << Y_first_exit[k]<< endl;
			}
			sigma_last = last.training(Y_first_exit, (mas[q[i]][M-1] + 10)/20, V); // ����� ���������� �������
			//cout << "������� ��������� ����: " << sigma_last << endl;
			for (int k = 0; k < kol_neuron; k++){ 
				first_layer[k].training(X_Alf_enter, V, sigma_last, last.getW(k)); // ��������� ������� 1 ���� � ������ ������� ������������
			}
			for (int k = 0; k < kol_neuron; k++){
				last.change_w_for_last(Y_first_exit, sigma_last, V); // ������������� ������� ������������ ��� ���������� �������
			}
			Yras = last.workNeuron(Y_first_exit);
			//cout << "����� 2 ����: " << Yras << endl;
			error += ((mas[q[i]][M-1] + 10)/20 - Yras)*((mas[q[i]][M-1] + 10)/20 - Yras);
            count_err++;
		}
		std::cout << "\n������ = " << sqrt(error/count_err) << " ------ "<< period << endl;
		random_shuffle(q, q + N );
	}
	ofstream fwout("weight_for_program.txt");
	for(int i = 0; i < kol_neuron; i++){
		//fwout << i + 1 << "������" << endl ;  
		fwout << first_layer[i].getw0() << "\n";
		for (int j = 0; j < kol_enter; j++){
			fwout << first_layer[i].getW(j) << "\n";
		}
	}
	//fwout << "�������� ������" << endl ;
	fwout << last.getw0() << "\n" ;
	for(int i = 0; i < kol_neuron; i++){
		fwout << last.getW(i) << "\n";
	}
	

	std::cout << "\nvse ok";
	fwout.close();
}