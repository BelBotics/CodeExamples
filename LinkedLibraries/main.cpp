#include <iostream>
#include <dlfcn.h>   // dlopen, dlsym, dlclose

int main() {
    void* handle = dlopen("./libmylib.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error: " << dlerror() << std::endl;
        return 1;
    }

    dlerror(); // reset errors

    typedef const char* (*hello_t)();
    hello_t hello = (hello_t) dlsym(handle, "helloFromLibrary");

    const char* err = dlerror();
    if (err) {
        std::cerr << "Symbol error: " << err << std::endl;
        dlclose(handle);
        return 1;
    }

    std::cout << hello() << std::endl;

    dlclose(handle);
    return 0;
}