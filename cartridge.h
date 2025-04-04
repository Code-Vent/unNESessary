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
    Memory* prg_rom;
    Memory* prg_ram;
    Memory* chr;
    Connection* prg_rom_conn;
    Connection* prg_ram_conn;
    Connection* chr_conn;
    Bus& main_bus;
    Range prg_addr;
    Bus& ppu_bus;
    Range chr_addr;
    uint8_t _load(const std::string& file_name, Header& header);
    void clear();
    friend class Nes;
public:
    Cartridge(Bus& main_bus, Range pgr_rom, Bus& ppu_bus, Range chr_ram);
    ~Cartridge();
    void load(const std::string& file_name, Mapper* m= nullptr);
};

#endif //NES_CARTRIGE_H
