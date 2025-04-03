//
// Created by Hamid on 2/28/2025.
//
#include"bus.h"
#include <iostream>

using namespace std;

Bus::Bus()
: pp()
{
    error = false;
    last_address = last_data = 0;
}

Peripheral* Bus::find(uint16_t address) {
    for (auto p : pp) {
        if (p->containsAddress(address))
            return p;
    }
    return nullptr;
}

void Bus::remove(uint16_t address) {
    for (auto iter = pp.begin(); iter != pp.end(); ++iter) {
        if ((*iter)->containsAddress(address))
            pp.erase(iter);
    }
}

void Bus::write(uint16_t address, uint8_t data) {
    auto p = find(address);
    if (p != nullptr)
        p->write(address, data);
    else
        error = true;
    last_address = address;
}

void Bus::write(uint8_t data)
{
    write(last_address, data);
}

void Bus::write() {
    write(last_address, last_data);
}

int8_t Bus::read(uint16_t address) {
    if(address == 0x2000)
    {
        auto i = 0;
    }
    auto p = find(address);
    if (p != nullptr)
        return p->read(address);
    else
        error = true;
    last_address = address;
    return 0;
}

int8_t Bus::read() {
    return read(last_address);
}

void Bus::add(Peripheral& p) {
    pp.push_back(&p);
}

void Bus::latch_data(uint16_t address) {
    last_address = address;
    last_data = read(address);
}

void Bus::latch_address(uint16_t address) {
    /*
    uint16_t addr_abs = 0;
    if (ptr_lo == 0x00FF) // Simulate page boundary hardware bug
    {
        addr_abs = (read(cpu->bus, ptr & 0xFF00) << 8) | read(cpu->bus, ptr + 0);
    }
    else // Behave normally
    {
        addr_abs = (read(cpu->bus, ptr + 1) << 8) | read(cpu->bus, ptr + 0);
    }
    cpu->data = read(cpu->bus, addr_abs);
     */
    uint16_t ptr_lo = read(address);
    uint16_t ptr_hi = read(address + 1);
    last_address = (ptr_hi << 8) | ptr_lo;
}

void Bus::set_address_rel(uint16_t base) {
    auto addr = base + last_data;
    if((addr & 0xFF00) != (base & 0xFF00))
        clock_cycles++;
    last_address = addr & 0xFFFF;
}

void Bus::latch_data_rel(uint8_t rel) {
    auto addr = rel + last_data;
    if((addr & 0xFF00) != (last_address & 0xFF00))
        clock_cycles++;
    last_address = addr & 0xFFFF;
    latch_data();
}

void Bus::latch_address() {
    latch_address(last_address);
}

void Bus::latch_data() {
    latch_data(last_address);
}

int8_t Bus::inc() {
    return ++last_data;
}

int8_t Bus::dec() {
    return --last_data;
}

void Bus::print_u16(uint16_t address) {
    cout << hex << (int)((read(address+1)<<8) | read(address)) << endl;
}

void Bus::print_u8(uint16_t address) {
    cout << hex << (int)read(address) << endl;
}
