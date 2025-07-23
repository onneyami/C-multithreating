#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

//recursive_mutex, рекурсивный мьютекс

//рекурсивный мьютекс в отличии от обычного мьютекса позволяет блокировать поток несколько раз, но и открывать его нужно будет столько же раз

recursive_mutex rm;

void Foo(int a){
    rm.lock();
    cout << a << " ";
    
    this_thread::sleep_for(chrono::milliseconds(500));
    
    if(a <= 1){
        cout << endl;
        rm.unlock();
        return;
    }
    
    a--;
    Foo(a);
    rm.unlock();
}

int main() {
    setlocale(LC_ALL, "RU");
    
    thread t1(Foo, 10);
    thread t2(Foo, 10);
    
    t1.join();
    t2.join();
    
    return 0;
}
