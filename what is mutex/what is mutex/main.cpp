#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

//что такое mutex, синхронизация потоков, защита разделяемых данных (пока что-то выполняется, другой трогать не может)

mutex mtx;     //создаем мьютекс, указываем секцию кода, которую нужно защищать во время работы потока

void Print(char ch){
    
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    mtx.lock();    //начало защиты
    for (int i = 0; i < 5; ++i){
        for(int i = 0; i < 10; i++){
            cout << ch;
            this_thread::sleep_for(chrono::milliseconds(20));
        }
        cout << endl;
    }
    cout << endl;
    mtx.unlock();      //конец защиты
    
    this_thread::sleep_for(chrono::milliseconds(2000));
    
}

int main() {
    setlocale(LC_ALL, "RU");
    
    thread t1(Print, '*');
    thread t2(Print, '#');
                             //в данном случае без синхронизации мы не получим два прямоугольника из символов, а получим перемешанную белеберду
    t1.join();
    t2.join();
    
    //во время работы потока защищаемого мьютексом остальные потоки не работают
    
    return 0;
}
