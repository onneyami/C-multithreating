#include <iostream>
#include <thread>

using namespace std;

//многопоточное программирование, получение результата из потока по ссылке

/*void Sum(int a, int b){
    
    this_thread::sleep_for(chrono::milliseconds(2000));    //имитация задержки в 2 секунды, типо вычисляет долго
    
    cout << "SUM Started." << endl;
    
    this_thread::sleep_for(chrono::milliseconds(3000));
    
    cout << "Result of a + b is " << a + b << endl;    //логика по правилам программирования нарушена
    
    this_thread::sleep_for(chrono::milliseconds(1000));
    
    cout << "SUM Ended." << endl;
    
}*/

void DoWork(int &a){    //во-первых передаем по ссылке, чтобы не создавалась копия
    
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    cout << "DO_WORK started." << endl;
    
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    a = a*2;
    
    this_thread::sleep_for(chrono::milliseconds(2000));

    cout << "DO_WORK ended." << endl;
    
    cout << "ID потока = " << this_thread::get_id() << endl;
    
}

int main() {
    setlocale(LC_ALL, "RU");
    
    int q = 5;
    
    thread t(DoWork, std::ref(q));     //первый параметр в потоке - это функция, второй - элемент
    
    for(size_t i = 0; i < 10; i++){
        cout << "ID потока = " << this_thread::get_id() << "\tmainworks\t" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    
    t.join();    //присоединяется к работе после завершения потока перед ним
    
    cout << q << endl;
    
    return 0;
}

//std::red() - создает класс reference, который позволяет работать с потоком, чтобы получить значение через ссылку, по сути обертка для переменной

//вместо join() можно detach(), он не будет выполнять действия, если не дождется завершения работы предыдушего потока, в отличии от join()
