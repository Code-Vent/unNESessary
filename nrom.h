//
// Created by Hamid on 4/1/2025.
//

#ifndef NES_NROM_H
#define NES_NROM_H
#include"mapper.h"

class PRG_Conn_NROM : public Connection{
public:
    explicit PRG_Conn_NROM(Range address, uint16_t address_mask)
            : Connection(address, address_mask)
    {}
};

class CHR_Conn_NROM : public Connection{
public:
    explicit CHR_Conn_NROM(Range address, uint16_t address_mask)
            : Connection(address, address_mask)
    {}
};

class Mapper_NROM : public Mapper{

public:

    explicit Mapper_NROM()
            :Mapper()
    {}

    bool map(const Header & h) override{
        Memory* m = *prg_conn->bytes;
        auto& addr_mask = m->get_addr_mask();
        auto& addr_range = m->get_addr_range();
        addr_range.lower = 0x8000;
        addr_mask = (h.prg_rom_chunks == 1)? 0xBFFF : 0xFFFF;
        addr_range.upper = addr_mask;
        return true;
    }

    Connection* get_chr_ram_conn(Range address, uint16_t address_mask) override{
        chr_conn = new CHR_Conn_NROM(address, address_mask);
        return chr_conn;
    }

    Connection* get_prg_rom_conn(Range address, uint16_t address_mask) override{
        prg_conn = new PRG_Conn_NROM(address, address_mask);
        return prg_conn;
    }
};

#endif //NES_NROM_H
