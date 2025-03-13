#ifndef NES_MAPPER_H
#define NES_MAPPER_H
#include"peripheral.h"

class Connection : public Peripheral{
public:
    Connection(Range address, uint16_t address_mask)
    : Peripheral(address, address_mask)
    {}
};

class Mapper
{
protected:
    Connection* main_bus;
    Connection* ppu_bus;
public:
    Mapper(){
        main_bus = nullptr;
        ppu_bus = nullptr;
    }
    virtual Peripheral& get_prg_rom_conn(Range address, uint16_t address_mask=0xFFFF) = 0;
    virtual Peripheral& get_chr_ram_conn(Range address, uint16_t address_mask=0xFFFF) = 0;
    virtual ~Mapper(){
        if(main_bus != nullptr)delete main_bus;
        if(ppu_bus != nullptr)delete ppu_bus;
    }
};

class PRG_Conn : public Connection{
public:
    explicit PRG_Conn(Range address, uint16_t address_mask)
    : Connection(address, address_mask)
    {}

    void write(uint16_t address, uint8_t data) override{

    }

    int8_t read(uint16_t address) override{
        return 0;
    }
};

class CHR_Conn : public Connection{
public:
    explicit CHR_Conn(Range address, uint16_t address_mask)
    : Connection(address, address_mask)
    {}

    void write(uint16_t address, uint8_t data) override{

    }

    int8_t read(uint16_t address) override{
        return 0;
    }
};

class Mapper00 : public Mapper{

public:
    explicit Mapper00()
    :Mapper()
    {}

    Peripheral & get_chr_ram_conn(Range address, uint16_t address_mask) override{
        if(ppu_bus == nullptr)
            ppu_bus = new CHR_Conn(address, address_mask);
        return *ppu_bus;
    }

    Peripheral & get_prg_rom_conn(Range address, uint16_t address_mask) override{
        if(main_bus == nullptr)
            main_bus = new PRG_Conn(address, address_mask);
        return *main_bus;
    }
};

#endif

