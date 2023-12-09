#include<iostream>
#include <memory>
#include <vector>

class FlyBehavior 
{
public:
	virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior 
{
	void fly() override {
		std::cout << "умею летать!\n";
	}
};

class FlyNoWay : public FlyBehavior 
{
	void fly() override {
		std::cout << "НЕ умею летать!\n";
	}
};

class QuakBehavior
{
public:
	virtual void quak() = 0;
};

class Quak : public QuakBehavior
{
	void quak() override {
		std::cout << "крякает\n";
	}
};

class SQuak : public QuakBehavior
{
	void quak() override {
		std::cout << "пищит\n";
	}
};

class MuteQuak : public QuakBehavior
{
	void quak() override {
		std::cout << "не издаёт звуков\n";
	}
};

class Duck
{
public:
	std::shared_ptr<FlyBehavior> flybehavior;
	std::shared_ptr<QuakBehavior> quakbehavior;
	virtual void display() = 0;
	
	void performFly() {
		flybehavior->fly();
	}

	void performQuak() {
		quakbehavior->quak();
	}

	void setFlyBehavior(std::shared_ptr<FlyBehavior> f) {
		flybehavior = f;
	}
	
	void setQuakBehavior(std::shared_ptr<QuakBehavior> q) {
		quakbehavior = q;
	}
};

class GrayDuck : public Duck
{
public:
	void display() override {
		std::cout << "Серая утка\n";
	}

	GrayDuck() {
		flybehavior = std::make_shared<FlyWithWings>();
		quakbehavior = std::make_shared<Quak>();
	}
};

class RedDuck : public Duck
{
public:
	void display() override {
		std::cout << "Красная утка\n";
	}

	RedDuck() {
		flybehavior = std::make_shared<FlyNoWay>();
		quakbehavior = std::make_shared<SQuak>();
	}
};


int main() {
	setlocale(LC_ALL, "rus");

	std::vector<Duck*> v;
	v.push_back(new GrayDuck());
	v.push_back(new RedDuck());

	for (auto& p : v) {
		p->display();
		p->performFly();
		p->performQuak();
		std::cout << "\n\n";
	}

	v[0]->setFlyBehavior(std::make_shared<FlyNoWay>());
	v[1]->setQuakBehavior(std::make_shared<MuteQuak>());

	for (auto& p : v) {
		p->display();
		p->performFly();
		p->performQuak();
		std::cout << "\n\n";
	}
}