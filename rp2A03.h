//
// Created by Hamid on 4/2/2025.
//

#ifndef NES_RP2A03_H
#define NES_RP2A03_H
#include "peripheral.h"
#include "bus.h"

class RP2A03 : public Peripheral{
    Bus& bus;
    friend class Renderer;
    friend class AudioPlayer;
public:
    RP2A03(Bus& main_bus, Range address);

    void write(uint16_t address, uint8_t data) override;
    int8_t read(uint16_t address) override;
};


#endif //NES_RP2A03_H
