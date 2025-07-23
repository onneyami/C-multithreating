#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

//lock_guard mutext

//lock_guard это класс, который захватывает мьютекс в конструктор и освобождает при вызове деструктора, нужен чисто для автоматизации, если мы забудем к примеру сделать unlock() для потока

mutex mtx;
void Print(char ch){

    this_thread::sleep_for(chrono::milliseconds(2000));
    
    {    //ограничение lock_guard
        lock_guard<mutex> guard(mtx);     //теперь lock_guard делает lock() и unlock() за нас
        for (int i = 0; i < 5; ++i){
            for(int i = 0; i < 10; i++){
                cout << ch;
                this_thread::sleep_for(chrono::milliseconds(20));
            }
            cout << endl;
        }
        cout << endl;
    }    //снятие ограничения lock_guard, следовательно это место вызова деструктора
        
    this_thread::sleep_for(chrono::milliseconds(2000));
    
}

int main() {
    setlocale(LC_ALL, "RU");
    
    thread t1(Print, '*');
    thread t2(Print, '#');
                             
    t1.join();
    t2.join();
    
    return 0;
}

