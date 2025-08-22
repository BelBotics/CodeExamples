#include "mylib.h"

//const char* helloFromLibrary()
std::string helloFromLibrary()
{
    return "Hello from dynamically loaded library";
}

float calcPow(int a, float f)
{
    float tempResult = 1.0;
    while(a)
    {
        tempResult = tempResult * f;
        a--;
    }

    return tempResult;
}

class Hello : public IHello 
{
    public:
    std::string greet(const std::string& name) override 
    {
        return "Hello " + name + " but this time from the second library";
    }
};
    
// Factory functions (C linkage to avoid C++ name mangling)
extern "C" IHello* create() {
    return new Hello();
}

extern "C" void destroy(IHello* p) {
    delete p;
}