#ifndef NES_MAPPER_H
#define NES_MAPPER_H
#include"peripheral.h"
#include "memory.h"
#include<string>
#include<fstream>
#include<iostream>

typedef struct
{
    char name[4];
    uint8_t prg_rom_chunks;
    uint8_t chr_rom_chunks;
    uint8_t mapper1;
    uint8_t mapper2;
    uint8_t prg_ram_size;
    uint8_t tv_system1;
    uint8_t tv_system2;
    char unused[5];
} Header;

class Connection : public Peripheral{
public:
    Memory** bytes;
    Connection(Range address, uint16_t address_mask)
    : Peripheral(address, address_mask)
    {
        bytes = nullptr;
    }

    void write(uint16_t address, uint8_t data) override{
        (*bytes)->write(address, data);
    }

    int8_t read(uint16_t address) override{
        return (*bytes)->read(address);
    }
};

class Mapper
{
protected:
    Connection* prg_rom_conn;
    Connection* prg_ram_conn;
    Connection* chr_conn;
public:

    Mapper(){
    }

    virtual bool map(const Header&) {
        return false;
    }

    virtual Connection* get_prg_rom_conn(Range address, uint16_t address_mask=0xFFFF) = 0;
    virtual Connection* get_chr_rom_conn(Range address, uint16_t address_mask=0xFFFF) = 0;
    virtual Connection* get_prg_ram_conn(Range address, uint16_t address_mask=0xFFFF) = 0;
    virtual Connection* get_chr_ram_conn(Range address, uint16_t address_mask=0xFFFF) = 0;
};


class PRG_Conn_Template : public Connection{
public:
    explicit PRG_Conn_Template(Range address, uint16_t address_mask)
    : Connection(address, address_mask)
    {}
};

class CHR_Conn_Template : public Connection{
public:
    explicit CHR_Conn_Template(Range address, uint16_t address_mask)
    : Connection(address, address_mask)
    {}
};

class Mapper_Template : public Mapper{

public:
    explicit Mapper_Template()
    :Mapper()
    {}

    Connection* get_chr_rom_conn(Range address, uint16_t address_mask) override{
        chr_conn = new CHR_Conn_Template(address, address_mask);
        return chr_conn;
    }

    Connection* get_prg_rom_conn(Range address, uint16_t address_mask) override{
        prg_rom_conn = new PRG_Conn_Template(address, address_mask);
        return prg_rom_conn;
    }

    Connection* get_chr_ram_conn(Range address, uint16_t address_mask) override{
        chr_conn = new CHR_Conn_Template(address, address_mask);
        return chr_conn;
    }

    Connection* get_prg_ram_conn(Range address, uint16_t address_mask) override{
        prg_ram_conn = new PRG_Conn_Template(address, address_mask);
        return prg_ram_conn;
    }
};

#endif

