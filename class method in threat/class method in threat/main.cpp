#include <iostream>
#include <thread>

using namespace std;

//метод класса в потоке

class MyClass{
public:
    void DoWork(){
        this_thread::sleep_for(chrono::milliseconds(2000));
        
        cout << "ID потока = " << this_thread::get_id() << "DoWork STARTED" << endl;
        
        this_thread::sleep_for(chrono::milliseconds(5000));
        
        cout << "ID потока = " << this_thread::get_id() << "DoWork STOPPED" << endl;
    }
    
    void DoWork2(int a){
        this_thread::sleep_for(chrono::milliseconds(2000));
        
        cout << "ID потока = " << this_thread::get_id() << "DoWork2 STARTED" << endl;
        
        this_thread::sleep_for(chrono::milliseconds(2000));
        
        cout << "The number is: " << a << endl;
        
        this_thread::sleep_for(chrono::milliseconds(5000));
        
        cout << "ID потока = " << this_thread::get_id() << "DoWork2 STOPPED" << endl;
    }
    
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
};


int main() {
    setlocale(LC_ALL, "RU");
    
    int result;
    MyClass m;
    
    thread t([&](){
        result = m.Sum(2,5);    //передаем в поток лямбду функцию, которая будет получать результат из метода класса, при этом передаем все внешние элементы по ссылке
    });
    
    //просто передать метод в поток, как мы делали это с функциями нельзя, по типу: thread t_2(m.DoWork())
    
    //thread t_2([&](){m.DoWork();});
    
    thread t_2(&MyClass::DoWork, m);   //для тех методов класса, которые НЕ возвращают никаких значений можно использовать данный синтаксис:
    //thread название_потока(&Название_класса::название_метода, элемент_класса_с_которым_работаем)
    
    thread t_3(&MyClass::DoWork2, m, 5);   //для метода, который принимает значение, но не возвращает, третий параметр - это передаваемое значение в метод, но точно также можно и через лямбду, смотря как удобнее
    
    for(size_t i = 1; i <= 10; i++){
        cout << "ID потока = " << this_thread::get_id() << "main works " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    
    t.join();   //дожидаемся выполнения логики в потоке t, даже если логика цикла for выполнится быстрее
    cout << "RESULT: " << result << endl;
    
    t_2.join();
    t_3.join();
    
    return 0;
}

//выполняем метод Sum в отдельном потоке
