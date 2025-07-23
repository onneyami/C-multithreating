#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

//многопоточность, потоки

void DoWork(){
    cout << "Start DoWork" << endl;
    for(size_t i = 0; i << 10; i++){
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << this_thread::get_id() << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    
    thread th(DoWork);  //синтаксис добавления потока, передаем туда указатель на функцию
    
    th.detach();    //разрывает связь с главным потоком, будет выполнятся самостоятельно даже после окончания работы главного потока, join - ждет завершения главного и начинает работу этого, значит использовать его нужно после завершения главного
    
    cout << "Start main" << endl;
    for(size_t i = 0; i << 10; i++){
        this_thread::sleep_for(chrono::milliseconds(500));    //задежка кода на полсекунды
        cout << this_thread::get_id() << endl;     //получение ID потока
    }
    
    return 0;
}
//запускать потоков можно и не только 2, ограничений нет
