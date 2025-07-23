#include <iostream>
#include <thread>

using namespace std;

//многопоточное программирование, лямбда выражения и возврат результата выполнения потока

//для чего? чтобы функция выполнялась параллельно с чем-то

int Sum(int a, int b){
    
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    cout << "SUM started." << endl;
    
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    cout << "SUM working." << endl;
    
    this_thread::sleep_for(chrono::milliseconds(2000));

    cout << "SUM ended." << endl;
    
    cout << "ID потока = " << this_thread::get_id() << endl;
    
    return a + b;
}

int main() {
    setlocale(LC_ALL, "RU");
    
    //int result = Sum(5,7);
    //cout << result << endl;
    
    int result;
    
    thread t([&result]() {result = Sum(2,5);} );   //в этом случае отдельная анонимная функция выполнится в отдельном потоке и вернет в переменную result, захваченную нами по ссылке в эту функцию результат выполнения функции Sum
    
    for(size_t i = 1; i < 10; i++){
        cout << "ID потока = " << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    
    t.join();    //после того, как основному потоку нечего будет делать после 10 итерации нашего цикла, подключается другой поток с нашей функцией sum
    cout << "SUM result: " << result << endl;
    
    return 0;
}



