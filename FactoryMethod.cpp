//«Фабричный метод» - предоставляет дочерним классам интерфейс для создания экземпляров некоторого класса. 
//В момент создания наследники могут определить какой класс создавать. 
//Это позволяет использовать в коде программы неспецифические классы, 
//а манипулировать абстрактными объектами на более высоком уровне.

#include <iostream>

class IProdaction {
public:
    virtual void release() = 0;
    ~IProdaction() {};
};

class Car : public IProdaction {
public:
    void release() override {
        std::cout << "Выпущен новый легковой автомобиль" << std::endl;
    }
};

class Truck : public IProdaction {
public:
    void release() override {
        std::cout << "Выпущен грузовой автомобиль" << std::endl;
    }
};

class IWorkShop {
public:
    virtual IProdaction* create() = 0;
    ~IWorkShop() {};
};

class CarWorkShop : public IWorkShop {
public:
    IProdaction* create() override {
        return new Car();
    }
};

class TruckWorkShop : public IWorkShop {
public:
    IProdaction* create() override {
        return new Truck();
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    IWorkShop* creator = new CarWorkShop();//экземпляр цеха по производству легковых автомобилей
    IProdaction* car = creator->create();//создаётся легковой автомобиль
    creator = new TruckWorkShop();//переквалифицируем цех на производство грузовых авто
    IProdaction* truck = creator->create();//создаётся грузовой автомобиль

    car->release();//на созданных авто вызываем метод release, 
    truck->release();//выполняющий выпуск автомобилей

    delete creator;
    delete car;
    delete truck;
}

