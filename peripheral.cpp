//
// Created by Hamid on 2/28/2025.
//
#include"peripheral.h"


Peripheral::Peripheral(Range address, uint16_t mask)
        : addr_range(address), address_mask(mask)
{}

bool Peripheral::containsAddress(uint16_t address) {
    return address >= addr_range.lower && address <= addr_range.upper;
}

