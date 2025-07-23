#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

//unique_lock mutex, unique_lock mutex vs lock_guard

mutex mtx;

void Print(char ch){
    
    unique_lock<mutex> ul(mtx, defer_lock);   //после указания defer_lock в этом месте lock() не вызывается, можно вызвать где удобно
    
    ul.lock();    //также после вызова lock() не нужно помнить о том забыли или не забыли об unlock(), он сам вызовется как деструктор
    
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    for(int i = 0; i < 5; i++){
        for(int i = 0; i < 10; i++){
            cout << ch;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout << endl;
    }
    cout << endl;
    
    ul.unlock();    //в отличии от lock_guard unique_lock может вызывать unlock
    
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
