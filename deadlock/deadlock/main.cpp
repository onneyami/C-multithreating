#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

//deadlock, взаимная блокировка

//чтобы ее избежать нужно всегда соблюдать порядок мьютексов!

mutex mtx1;
mutex mtx2;

void Print(char ch){
    mtx1.lock();
this_thread::sleep_for(chrono::milliseconds(1));
    mtx2.lock();
    {
        for (int i = 0; i < 5; ++i){
            for(int i = 0; i < 10; i++){
                cout << ch;
                this_thread::sleep_for(chrono::milliseconds(20));
            }
            cout << endl;
        }
        cout << endl;
    }
    mtx1.unlock();
    mtx2.unlock();
}

void Print2(char ch){
    mtx2.lock();
this_thread::sleep_for(chrono::milliseconds(1));
    mtx1.lock();
    {
        for (int i = 0; i < 5; ++i){
            for(int i = 0; i < 10; i++){
                cout << ch;
                this_thread::sleep_for(chrono::milliseconds(20));
            }
            cout << endl;
        }
        cout << endl;
    }
    mtx2.unlock();
    mtx1.unlock();
}

//в данном примере из-за разного порядка вызовов мьютексов мы получаем взаимную блокировку

int main() {
    setlocale(LC_ALL, "RU");
    
    thread t1(Print, '*');
    thread t2(Print2, '#');
                             
    t1.join();
    t2.join();
    
    return 0;
}


