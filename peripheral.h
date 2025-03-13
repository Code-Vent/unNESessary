//
// Created by Hamid on 2/28/2025.
//

#ifndef NES_PERIPHERAL_H
#define NES_PERIPHERAL_H
#include<cstdint>

struct Range{
    uint16_t lower;
    uint16_t upper;
};

class Peripheral {
protected:
    uint16_t start_address, end_address;
    uint16_t address_mask;
public:
    Peripheral(Range address, uint16_t address_mask);
    virtual void write(uint16_t address, uint8_t data) {}
    virtual int8_t read(uint16_t address) { return 0; }
    bool containsAddress(uint16_t address);
    inline uint16_t index(uint16_t address){
        return (address - start_address) & address_mask;
    }
};

#endif //NES_PERIPHERAL_H
