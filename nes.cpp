#include "nes.h"
#include<iostream>
#include<string>

using namespace std;

Nes::Nes(const std::string& file_name)
        :cpu(main_bus, Memory({.lower=0, .upper=0x1FFF}, 0x0800, 0x07FF)),
        cart(main_bus, {.lower=0x4020, .upper=0xFFFF}, ppu_bus, {.lower=0, .upper=0x3EFF}, file_name)
{
}

Nes::~Nes() {
}

void Nes::run()
{
}


void Nes::cpu_test() {
    main_bus.write(0xfffc, 0x00);
    main_bus.write(0xfffd, 0x00);
    main_bus.write(0x0000, 0xa9);
    main_bus.write(0x0001, 0x42);
    main_bus.write(0x0002, 0x8d);
    main_bus.write(0x0003, 0x00);
    main_bus.write(0x0004, 0x02);
    main_bus.write(0x0005, 0xD0);//BNE
    main_bus.write(0x0006, (std::uint8_t)-7);
    //main_bus.write(0x0007, 0x00);

    cpu.reset();
    while (cpu.execute() && main_bus.no_error()) {
        cout << cpu;
        //cout << "Clock Cycles = " << (int)main_bus.clock_cycles << endl;
    }
}