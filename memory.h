//
// Created by Hamid on 2/28/2025.
//

#ifndef NES_MEMORY_H
#define NES_MEMORY_H

#include "peripheral.h"
#include<cstdint>
#include<vector>

class Memory : public Peripheral {
public:
    std::vector<uint8_t> bytes;
public:
    Memory(Range address, uint16_t size, uint16_t address_mask=0xFFFF);
    int8_t read(uint16_t address) override;
    void write(uint16_t address, uint8_t data) override;
    uint8_t& operator[](uint32_t index);
    uint8_t operator[](uint32_t index) const;
    char* ptr(){return (char*)bytes.data();}
    void discard();
    Range& get_addr_range();
    uint32_t& get_addr_mask();
};

#endif //NES_MEMORY_H
