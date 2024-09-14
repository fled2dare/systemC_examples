#include <systemc.h>

class nand : public sc_module{
    public:
        sc_in<bool> a_in, b_in;
        sc_out<bool> f_out;
        SC_HAS_PROCESS(nand);
        nand(sc_module_name name) : sc_module(name){
            SC_METHOD(nand_function);
            sensitive << a_in << b_in;
        }
        void nand_function();
};

class aand : public sc_module {
public:
    sc_in<bool> aand_a_in, aand_b_in;
    sc_out<bool> aand_f_out;

    sc_signal<bool> nand12;  // Internal signal for intermediate result

    nand nand1, nand2;  // NAND gate instances

    SC_CTOR(aand) : nand1("nand1"), nand2("nand2") {
        nand1.a_in(aand_a_in);
        nand1.b_in(aand_b_in);
        nand1.f_out(nand12);

        nand2.a_in(nand12);
        nand2.b_in(nand12);
        nand2.f_out(aand_f_out);
    }
};



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
        wait(2, SC_NS);
        std::cout << "Test A=0, B=0: F=" << f_in.read() << " @time " << sc_time_stamp() << std::endl;

        a_out.write(false); b_out.write(true);
        wait(2, SC_NS);
        std::cout << "Test A=0, B=1: F=" << f_in.read() << " @time " << sc_time_stamp() << std::endl;

        a_out.write(true); b_out.write(false);
        wait(2, SC_NS);
        std::cout << "Test A=1, B=0: F=" << f_in.read() << " @time " << sc_time_stamp() << std::endl;

        a_out.write(true); b_out.write(true);
        wait(2, SC_NS);
        std::cout << "Test A=1, B=1: F=" << f_in.read() << " @time " << sc_time_stamp() << std::endl;
    }
};

void nand::nand_function() {
    bool result = !(a_in.read() && b_in.read());  // Correct way to read sc_in<bool>
    f_out.write(result);  // Correct way to write to sc_out<bool>
}


int sc_main(int, char*[]) {
    sc_signal<bool> a_s, b_s, f_s;

    testbench tb("tb");
    tb.a_out(a_s);
    tb.b_out(b_s);
    tb.f_in(f_s);

    aand aand_module("aand");
    aand_module.aand_a_in(a_s);
    aand_module.aand_b_in(b_s);
    aand_module.aand_f_out(f_s);

    sc_start();
    return 0;
}
