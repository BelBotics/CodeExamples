#include <iostream>
#include <dlfcn.h>   // dlopen, dlsym, dlclose
#include "src/mylib.h"

int main() {
    void* handle; 
    int librarySelector;
    std::cout << "Select which library to open (enter 1 or 2)?" << std::endl;
    std::cin >> librarySelector;

    switch (librarySelector)
    {
    case 1:
        /* code */
        handle = dlopen("./libmylib.so", RTLD_LAZY);
        if (!handle) {
            std::cerr << "Error: " << dlerror() << std::endl;
            return 1;
        }
        break;

    case 2:
        /* code */
        handle = dlopen("./libmylib2.so", RTLD_LAZY);
        if (!handle) {
            std::cerr << "Error: " << dlerror() << std::endl;
            return 1;
        }
        break;
    
    default:
        std::cout << "Wrong library id selection";
        return 0;
        break;
    }



    dlerror(); // reset errors

    // Creation of typedef for library functions with multiple input arguments
    //typedef return_type (*alias_name)(arg1_type, arg2_type, ...);

    //typedef const char* (*hello_t)();
    //hello_t hello = (hello_t) dlsym(handle, "helloFromLibrary");
    typedef std::string (*hello_t)();
    hello_t hello = (hello_t) dlsym(handle, "helloFromLibrary");

    const char* err = dlerror();
    if (err) {
        std::cerr << "Symbol error: " << err << std::endl;
        dlclose(handle);
        return 1;
    }

    std::cout << hello() << std::endl;

    // Call library function which calculates float value to the n-th power
    typedef float (*libFunc1_t)(int, float);
    libFunc1_t libPow = (libFunc1_t) dlsym(handle, "calcPow");

    err = dlerror();
    if (err) {
        std::cerr << "Symbol error: " << err << std::endl;
        dlclose(handle);
        return 1;
    }



    // Work with interface class of the library
    // Load factory functions
    create_t* create = (create_t*) dlsym(handle, "create");
    destroy_t* destroy = (destroy_t*) dlsym(handle, "destroy");

    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
        dlclose(handle);
        return 1;
    }

    // Use the class via interface
    IHello* helloIClass = create();
    std::cout << helloIClass->greet("Pavle") << std::endl;
    destroy(helloIClass);

    dlclose(handle);

    int userPow = 0;
    float userFloat = 0.0;

    while(1)
    {
        std::cout << "Enter float number which power shall be calculted" << std::endl;
        std::cin >> userFloat;
        std::cout << "Enter integer number for the power number" << std::endl;
        std::cin >> userPow;
        std::cout << userFloat << " to the power of " << userPow << "  is: " << libPow(userPow, userFloat) << std::endl;    
    }

    dlclose(handle);
    return 0;
}