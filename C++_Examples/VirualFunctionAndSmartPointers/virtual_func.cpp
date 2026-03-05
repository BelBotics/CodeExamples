#include <iostream>
#include <memory>

#define MaxArraySize 2

class Base
{
    public:
        virtual void show() = 0; // pure virtual function

};

class Defived1 : public Base
{
    public:
        void show() override
        {
            std::cout << "Derived1 show function called" << std::endl;
        }


};

class Derived2 : public Base
{
    public:
        void show() override
        {
            std::cout << "Derived2 show function called" << std::endl;
        }
};



int main()
{
    // create an array of pointers to Base class
    std::unique_ptr<Base> basePtr[MaxArraySize];

    basePtr[0] = std::make_unique<Defived1>();
    basePtr[1] = std::make_unique<Derived2>();

    // call the show function using base class pointers
    for (int i = 0; i < MaxArraySize; i++)
    {
        basePtr[i]->show();
    }

    return 0;
}