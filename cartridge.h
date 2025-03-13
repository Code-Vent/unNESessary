//
// Created by Hamid on 2/28/2025.
//

#ifndef NES_CARTRIDGE_H
#define NES_CARTRIDGE_H

#include"memory.h"
#include"mapper.h"
#include<cstdint>
#include"bus.h"

class Cartridge {
    Mapper* mp;
public:
    Cartridge(Bus& main_bus, Range pgr_rom, Bus& ppu_bus, Range chr_ram, Mapper* mapper=nullptr);

};

#endif //NES_CARTRIGE_H
