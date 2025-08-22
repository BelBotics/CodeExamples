#pragma once
#include <string>

extern "C" {
    //const char* helloFromLibrary();
    std::string helloFromLibrary();

    float calcPow(int a, float f);
}

class IHello {
    public:
        virtual ~IHello() = default;
        virtual std::string greet(const std::string& name) = 0;
};
    
// Factory function types
typedef IHello* create_t();
typedef void destroy_t(IHello*);