#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <fstream>
 
using namespace std;
const int k = 5;
 
int main() {
    clock_t time;
    
    string * str;
    int kolvo_num, kolvo_str = 0, i = 0;
    string temp_str, temp;
    time = clock();
//считаем кол-во строк
    ifstream F("in.txt");
    while (!F.eof()){
        getline(F, temp_str);
        kolvo_str++;
    }
    F.close();
    //cout << kolvo_str << endl;
    
    str = new string [kolvo_str];
    
    F.open("in.txt");
 
//считываем файл в массив
    while (!F.eof()){
        getline(F, str[i]);
        i++;
    }
    //cout << str[1] << endl;
    F.close();
    //int p(0);
    //cout << str[1].length() << endl;
    for(int i = 0; i < kolvo_str - 1; ++i) // i - номер прохода
    {            
        for(int j = 3; j < kolvo_str - 1; j++) // внутренний цикл прохода
        {     
            if (str[j + 1].length() < str[j].length()) 
            {
                temp = str[j + 1]; 
                str[j + 1] = str[j]; 
                str[j] = temp;
            }
			if (j%23 == 22)
			{
				j+=3;
				//p++;
			}
        }
    }
    //cout << str[0] << endl;
    
 
    ofstream outfile("out.txt");
    for(int i = 0; i < kolvo_str; i++) {
        outfile << str[i] << endl;;
    }
    outfile.close();
 
//¬ыводим врем€
    time = clock()- time;
    cout << ((float)time) / CLOCKS_PER_SEC << endl;
_getch();
return 0;
    
}