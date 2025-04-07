//
// Created by Hamid on 2/28/2025.
//

#ifndef NES_BUS_H
#define NES_BUS_H
#include<cstdint>
#include<vector>
#include<iostream>
#include"peripheral.h"


class Bus {
    std::vector<Peripheral*> pp;
    bool error;
    uint16_t last_address;
    friend class CPU6502;
public:
    uint8_t clock_cycles;
    Bus();
    void add(Peripheral&);
    void remove(uint16_t address);
    void write(uint16_t address, uint8_t data);
    void write(uint8_t data);
    int8_t read(uint16_t address);
    int8_t read();
    Peripheral* find(uint16_t address);
    inline uint16_t address() { return last_address; }
    inline bool no_error() {
        if(error)
            std::cerr << std::hex << "Last Address = " << last_address << std::endl;
        return !error;
    }
    void print_u8(uint16_t address);
    void print_u16(uint16_t address);
};
#endif //NES_BUS_H
