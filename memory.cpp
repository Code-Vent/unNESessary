//
// Created by Hamid on 2/28/2025.
//

#include"memory.h"


Memory::Memory(Range address, uint16_t size, uint16_t mask)
        : Peripheral(address, mask), bytes(size, 0)
{
}

int8_t Memory::read(uint16_t address) {
    return bytes.at(index(address));
}

void Memory::write(uint16_t address, uint8_t data) {
    bytes.at(index(address)) = data;
}

uint8_t& Memory::operator[](uint32_t index)
{
    return bytes.at(index & address_mask);
}

uint8_t Memory::operator[](uint32_t index) const
{
    return bytes.at(index & address_mask);
}

void Memory::discard() {
    bytes.clear();
}

uint32_t &Memory::get_addr_mask() {
    return address_mask;
}

Range &Memory::get_addr_range() {
    return addr_range;
}