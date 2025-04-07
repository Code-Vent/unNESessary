#include "nes.h"
#include<iostream>
#include<string>

using namespace std;

Nes::Nes()
        :cpu(main_bus, Memory({.lower=0, .upper=0x1FFF}, 0x0800, 0x07FF)),
        cart(main_bus, {.lower=0x4020, .upper=0xFFFF}, ppu_bus, {.lower=0, .upper=0x3EFF}),
        ppu(ppu_bus, {.lower = 0x2000, .upper = 0x3FFF}, 0x2007)
{
    main_bus.add(ppu);
}

void Nes::_run() {
    cpu.reset();
    while (cpu.execute() && main_bus.no_error()) {
        cout << cpu;
        //cout << "Clock Cycles = " << (int)main_bus.clock_cycles << endl;
    }
}

void Nes::run(const std::string& file_name)
{
    cart.load(file_name);
    _run();
}


void Nes::cpu_test() {
    cart.load("../nestest.nes");
    cpu.reset();
    cpu.set_pc(0xC000);
    cout << hex << "PC = " << (int)cpu.pc << endl;
    while (cpu.execute() && main_bus.no_error()) {
        cout << hex << "PC = " << (int)cpu.pc << endl;
    }
}