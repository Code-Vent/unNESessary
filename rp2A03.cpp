//
// Created by Hamid on 4/2/2025.
//

#include "rp2A03.h"


RP2A03::RP2A03(Bus& main_bus, Range address)
: Peripheral(address, 0xFFFF), bus(main_bus)
{

}

void RP2A03::write(uint16_t address, uint8_t data) {
    switch (address & address_mask) {
        case 0x4014:  //OAM DMA
            uint16_t addr = data << 8;
            for(int i = 0; i < 256; ++i){
                auto val = bus.read(addr++);
                bus.write(0x2004, val);  //OAM_DATA
            }
            break;
    }
}

int8_t RP2A03::read(uint16_t address) {
    return 0;
}