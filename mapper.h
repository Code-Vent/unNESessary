#ifndef NES_MAPPER_H
#define NES_MAPPER_H
#include"peripheral.h"
#include "memory.h"
#include<string>
#include<fstream>
#include<iostream>

class Connection : public Peripheral{
public:
    Memory** bytes;
    Connection(Range address, uint16_t address_mask)
    : Peripheral(address, address_mask)
    {}
};

class Mapper
{
public:
    Mapper(){
    }

    virtual Connection* get_prg_rom_conn(Range address, uint16_t address_mask=0xFFFF) = 0;
    virtual Connection* get_chr_ram_conn(Range address, uint16_t address_mask=0xFFFF) = 0;
};


class PRG_Conn_Template : public Connection{
public:
    explicit PRG_Conn_Template(Range address, uint16_t address_mask)
    : Connection(address, address_mask)
    {}

    void write(uint16_t address, uint8_t data) override{
        auto i = 0;
    }

    int8_t read(uint16_t address) override{
        return 0;
    }
};

class CHR_Conn_Template : public Connection{
public:
    explicit CHR_Conn_Template(Range address, uint16_t address_mask)
    : Connection(address, address_mask)
    {}

    void write(uint16_t address, uint8_t data) override{

    }

    int8_t read(uint16_t address) override{
        return 0;
    }
};

class Mapper_Template : public Mapper{

public:
    explicit Mapper_Template()
    :Mapper()
    {}

    Connection* get_chr_ram_conn(Range address, uint16_t address_mask) override{
        return new CHR_Conn_Template(address, address_mask);
    }

    Connection* get_prg_rom_conn(Range address, uint16_t address_mask) override{
        return new PRG_Conn_Template(address, address_mask);
    }
};

#endif

