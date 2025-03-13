//
// Created by Hamid on 2/28/2025.
//

#ifndef NES_BUS_H
#define NES_BUS_H
#include<cstdint>
#include<vector>
#include"peripheral.h"

class Bus {
    std::vector<Peripheral*> pp;
    bool error;
    uint16_t last_address;
    int8_t last_data;

public:
    uint8_t clock_cycles;
    Bus() = default;
    void add(Peripheral&);
    void remove(uint16_t address);
    void write(uint16_t address, uint8_t data);
    void write(uint8_t data);
    void write();
    int8_t read(uint16_t address);
    int8_t read();
    int8_t dec();
    int8_t inc();
    Peripheral* find(uint16_t address);
    void latch_data(uint16_t address);
    void latch_data_rel(uint8_t rel);
    void latch_data();
    void latch_address(uint16_t address);
    void set_address_rel(uint16_t base);
    void latch_address();
    inline uint16_t address() { return last_address; }
    inline int8_t  data() { return last_data; }
    inline bool no_error() { return !error; }
    void print_u8(uint16_t address);
    void print_u16(uint16_t address);
};
#endif //NES_BUS_H
