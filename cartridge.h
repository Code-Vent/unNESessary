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
    Mapper* mapper;
    Memory* prg;
    Memory* chr;
    Connection* prg_conn;
    Connection* chr_conn;
    uint8_t load(const std::string& file_name, Header& header);
public:
    Cartridge(Bus& main_bus, Range pgr_rom, Bus& ppu_bus, Range chr_ram, const std::string& file_name);
    ~Cartridge();
};

#endif //NES_CARTRIGE_H
