#include <iostream>

class Animal;
class Dog;
class Cat;

class Visitor {
public:
    enum AnimalType {none, dogType, catType};
    AnimalType value = none;

public:
    void visit(Dog &ref) {value = dogType;}
    void visit(Cat &ref) {value = catType;}
    virtual ~Visitor() = default;
};

class Animal {
public:
    virtual void accept(Visitor &v) = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
    void accept(Visitor &v) override {v.visit(*this);}
};

class Cat : public Animal {
    void accept(Visitor &v) override {v.visit(*this);}
};

void meeting(Animal* firstPtr, Animal* secondPtr) {
    Visitor v1, v2;
    firstPtr->accept(v1);
    secondPtr->accept(v2);
    int flag = static_cast<int> (v1.value) << 2 | static_cast<int> (v2.value);
    switch (flag) {
        case 0b0101: std::cout << "Woof-Woof" << std::endl; break;
        case 0b0110: std::cout << "Bark Meow" << std::endl; break;
        case 0b1001: std::cout << "Meow Bark" << std::endl; break;
        case 0b1010: std::cout << "Purr Purr" << std::endl; break;
        default: std::cout << "Unknown animal" << std::endl;
    }
}

int main() {
    Animal* a = new Dog();
    Animal* b = new Cat();
    meeting(a,a);
    meeting(a,b);
    meeting(b,a);
    meeting(b,b);

    return 0;
}
