#include <systemc.h>

using namespace sc_core;

class module1 : public sc_module{
    public:
    SC_CTOR(module1)
    {
        SC_METHOD(function_a);
    }

    void function_a(){
        std::cout << name() << std::endl;
    }
};

class module2 : public sc_module{
    public:
    SC_CTOR(module2){
        SC_METHOD(function_b);
    }

    void function_b();
};

void module2 :: function_b(){
    std::cout << "called from outside the class" << name() << std::endl;
}

SC_MODULE(module3){
    SC_HAS_PROCESS(module3);
    module3(sc_module_name name) : sc_module(name)
    {
        SC_METHOD(func_c);
    }

    void func_c(){
        std::cout << name() << "this is my custom constructor" << std::endl;
    }
};

int sc_main(int, char*[]){
    module1 module1("a");
    module2 module2("b");
    module3 module3("c");
    sc_start();

    return 0;
}

