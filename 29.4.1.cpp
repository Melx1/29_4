#include <iostream>

class Visitor;
class Animal;
class Dog;
class Cat;

class DogVisitor {
public:
    virtual void dogMessage (Dog* ptr) {std::cout << "Woof";}
    virtual void dogMessage (Cat* ptr) {std::cout << "Bark";}
};

class CatVisitor {
public:
    virtual void catMessage (Dog* ptr) {std::cout << "Meow";}
    virtual void catMessage (Cat* ptr) {std::cout << "Purr";}
};

class Animal {
public:
    virtual void firstAccept (Visitor* v, Animal* ptr) = 0;
    virtual void secondAccept (DogVisitor*) = 0;
    virtual void secondAccept (CatVisitor*) = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void firstAccept (Visitor*, Animal*) override;
    void secondAccept (DogVisitor*) override;
    void secondAccept (CatVisitor*) override;
};

class Cat : public Animal {
public:
    void firstAccept (Visitor*, Animal*) override;
    void secondAccept (CatVisitor*) override;
    void secondAccept (DogVisitor*) override;
};


class Visitor {
public:
    virtual void firstFn (Dog* arg1, Animal* arg2) {
        DogVisitor v;
        arg2->secondAccept(&v);
    }

    virtual void firstFn (Cat* arg1, Animal* arg2) {
        CatVisitor v;
        arg2->secondAccept(&v);
    }

    virtual ~Visitor() = default;
};

void Dog::firstAccept (Visitor* v, Animal* ptr) {
    v->firstFn(this, ptr);
}

void Dog::secondAccept (DogVisitor* v) {
    v->dogMessage(this);
}

void Dog::secondAccept (CatVisitor* v) {
    v->catMessage(this);
}

void Cat::firstAccept (Visitor* v, Animal* ptr) {
    v->firstFn(this, ptr);
}
void Cat::secondAccept (CatVisitor* v) {
    v->catMessage(this);
}

void Cat::secondAccept (DogVisitor* v) {
    v->dogMessage(this);
}

void meeting (Animal* firstPtr, Animal* secondPtr) {
    Visitor v1, v2;
    firstPtr->firstAccept(&v1, secondPtr);
    std::cout << " ";
    secondPtr->firstAccept(&v2, firstPtr);
    std::cout << std::endl;
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
