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
    last_address = 0;
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

int8_t Bus::read(uint16_t address) {
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

void Bus::latch_address(uint16_t address) {
    last_address = address;
}

void Bus::inc() {
    write(read() + 1);
}

void Bus::dec() {
    write(read() - 1);
}

void Bus::print_u16(uint16_t address) {
    cout << hex << (int)((read(address+1)<<8) | read(address)) << endl;
}

void Bus::print_u8(uint16_t address) {
    cout << hex << (int)read(address) << endl;
}
