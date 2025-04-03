//
// Created by Hamid on 3/10/2025.
//

#ifndef NES_PPU2C02_H
#define NES_PPU2C02_H

#include "peripheral.h"
#include "bus.h"
#include"memory.h"

class PPU2C02 : public Peripheral{
    Bus&    bus;
    Memory  oam;
    Memory  vram;
    Memory  palette;
    uint8_t ppu_ctrl;
    uint8_t ppu_mask;
    uint8_t ppu_status;
    uint8_t oam_addr;
    uint8_t ppu_scroll[2];
    uint8_t ppu_addr[2];
public:
    friend class Renderer;
    PPU2C02(Bus& ppu_bus, Range address, uint32_t address_mask);

    void write(uint16_t address, uint8_t data) override;
    int8_t read(uint16_t address) override;
};


#endif //NES_PPU2C02_H
