#ifndef NES__H
#define NES__H

#include "bus.h"
#include "memory.h"
#include "cpu6502.h"
#include"cartridge.h"
#include "mapper.h"
#include "ppu2C02.h"
//#include"apu2A03.h"
#include<string>

class Nes {

    Bus main_bus;
    Bus ppu_bus;
    CPU6502 cpu;
    Cartridge cart;
    //APU2A03* apu;
    PPU2C02 ppu;
    void _run();
public:
    Nes();
    ~Nes() = default;
    void run(const std::string& file_name);
    [[maybe_unused]]
    void cpu_test();
    CPU6502& get_cpu(){return cpu;}
};




#endif //NES_H