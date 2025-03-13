//
// Created by Hamid on 2/28/2025.
//
#include"peripheral.h"


Peripheral::Peripheral(Range address, uint16_t mask)
        : start_address(address.lower), end_address(address.upper), address_mask(mask)
{}

bool Peripheral::containsAddress(uint16_t address) {
    return address >= start_address && address <= end_address;
}

