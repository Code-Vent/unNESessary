//
// Created by Hamid on 2/28/2025.
//

#ifndef NES_PERIPHERAL_H
#define NES_PERIPHERAL_H
#include<cstdint>

struct Range{
    uint32_t lower;
    uint32_t upper;
};

class Peripheral {
protected:
    Range addr_range;
    uint32_t address_mask;
public:
    Peripheral(Range address, uint32_t address_mask);
    virtual void write(uint16_t address, uint8_t data) {}
    virtual int8_t read(uint16_t address) { return 0; }
    bool containsAddress(uint16_t address);
    inline uint16_t index(uint16_t address){
        return (address - addr_range.lower) & address_mask;
    }
};

#endif //NES_PERIPHERAL_H
