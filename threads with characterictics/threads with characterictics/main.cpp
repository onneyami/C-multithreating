#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

//потоки с параметрами

void DoWork(int a, int b){
    cout << "Start DoWork" << endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
    cout << "ID потока: " <<  this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
    cout << "a + b: " << a + b << endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
    cout << "End DoWork" << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    
    thread th(DoWork, 5, 2);    //передаем сначала указатель на функцию (ее название), а далее подряд все параметры передаваемые в функцию
    
    for(size_t i = 0; i < 20; i++){
        cout << "ID потока: " << this_thread::get_id() << "Main works" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    
    th.join();
    
    return 0;
}

