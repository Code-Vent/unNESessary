//
// Created by Hamid on 3/10/2025.
//

#include "ppu2C02.h"
#include<cassert>
#include<iostream>

PPU2C02::PPU2C02(Bus& ppu_bus, Range address, uint32_t address_mask)
: Peripheral(address, address_mask), bus(ppu_bus), oam({.lower = 0, .upper = 0xFF}, 0x100)
{

}

void PPU2C02::write(uint16_t address, uint8_t data) {
    typedef struct  {
        uint8_t w : 1;
    }byte_tracker_t;
    static byte_tracker_t bt = {
            .w = 1
    };
    switch(address & address_mask){
        case 0x2000:
            ppu_ctrl = data;
            break;
        case 0x2001:
            ppu_mask = data;
            break;
        case 0x2003:
            oam_addr = data;
            break;
        case 0x2004:
            oam.write(oam_addr++, data);
            break;
        case 0x2005:
            ppu_scroll[bt.w++] = data;
            break;
        case 0x2006:
            ppu_addr[bt.w++] = data;
            break;
        case 0x2007:
            bus.write((ppu_addr[1] << 8) | ppu_addr[0], data);
            break;
        default:
            std::cout << std::hex << address << std::endl;
            assert(false);
            break;
    }
}

int8_t PPU2C02::read(uint16_t address) {
    switch (address & address_mask) {
        case 0x2002:
            return ppu_status;
        case 0x2004:
            return oam.read(oam_addr);
        case 0x2007:
            return bus.read((ppu_addr[1] << 8) | ppu_addr[0]);
        default:
            std::cout << std::hex << address << std::endl;
            assert(false);
            return 0;
    }
}
