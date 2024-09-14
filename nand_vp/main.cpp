#include <systemc.h>

class nand : public sc_module{
public:
    // design NAND gate with input A and B, and output F. Whenever any input changes, it prints the inputs and outputs.

    sc_in<bool> a_in, b_in;
    sc_out<bool> f_out;

    SC_HAS_PROCESS(nand);
    nand(sc_module_name name) : sc_module(name){
        SC_METHOD(nand_function);
        sensitive << a_in << b_in;
        // dont_initialize();
    }

    void nand_function();
};

void nand :: nand_function(){
    bool result = !(a_in.read() && b_in.read());
    f_out.write(result);
    /* std::cout << "a: " << a_in.read() << "b: " << b_in.read() << "f: " << result << std::endl; */
}

class testbench : public sc_module {
public:
    sc_in<bool> f_in;
    sc_out<bool> a_out, b_out;

    SC_HAS_PROCESS(testbench);
    testbench(sc_module_name name): sc_module(name) {
        SC_THREAD(tester);
    }

    void tester() {
        // Test all input combinations
        a_out.write(false); b_out.write(false);
        wait(10, SC_NS);
        std::cout << "Test A=0, B=0: F=" << f_in.read() << std::endl;

        a_out.write(false); b_out.write(true);
        wait(10, SC_NS);
        std::cout << "Test A=0, B=1: F=" << f_in.read() << std::endl;

        a_out.write(true); b_out.write(false);
        wait(10, SC_NS);
        std::cout << "Test A=1, B=0: F=" << f_in.read() << std::endl;

        a_out.write(true); b_out.write(true);
        wait(10, SC_NS);
        std::cout << "Test A=1, B=1: F=" << f_in.read() << std::endl;
    }
};

int sc_main(int, char*[]){
    sc_signal<bool> a_s, b_s, f_s;

    testbench tb("tb");
    tb.a_out(a_s);
    tb.b_out(b_s);
    tb.f_in(f_s);

    nand nand("nand");
    nand.a_in(a_s);
    nand.b_in(b_s);
    nand.f_out(f_s);

    sc_start();
    return 0;
}
