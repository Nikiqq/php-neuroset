//#include <iostream> 
//#include <random>
//#include <time.h>
//#include <thread>
//#include <fstream>
// 
//using namespace std;
//const int k = 5;
//const int N = 10;
// 
//void score (string * str, int i, int kolvo_str) {
//    
//    int kolvo_num ;
// 
//        
//    for (int j = i; j <kolvo_str ; j+= N) {
//        kolvo_num = 0;
//        for (int t = 0; t < str[j].size(); t++){
//            if (isdigit(str[j][t])) kolvo_num++;
//        }
//        if (kolvo_num > k) cout <<"num:" << i << "__" << str[j] << endl;
//    }
// 
//}
// 
//int main() {
//    clock_t time;
//    thread t[N];
//    
//    string * str;
//    int kolvo_str = 0, i = 0;
//    string temp_str;
// 
////считаем кол-во строк
//    ifstream F("file.txt");
//    while (!F.eof()){
//        getline(F, temp_str);
//        kolvo_str++;
//    }
//    F.close();
//    
// 
//    str = new string [kolvo_str];
// 
//    F.open("file.txt");
// 
////считываем файл в массив
//    while (!F.eof()){
//        getline(F, str[i]);
//        i++;
//    }
// 
////Программа
//    time = clock();
//    for (i = 0; i < N; i++){
//        t[i] = std::thread (score, str, i, kolvo_str);
//    }
//        F.close();
// 
////Закрытие потоков
//    for (int i=0; i<N; ++i){
//        t[i].join();
//    }
// 
////Выводим время
//    time = clock()- time;
//    cout << ((float)time) / CLOCKS_PER_SEC << endl;
//}