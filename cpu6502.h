//
// Created by Hamid on 2/28/2025.
//

#ifndef NES_CPU6502_H
#define NES_CPU6502_H
#include"memory.h"
#include<cstdint>
#include <iostream>
#include"bus.h"
#include "rp2A03.h"

constexpr uint16_t reg_base_addr = 0x800;
constexpr uint8_t a_index = 0;
constexpr uint8_t x_index = 1;
constexpr uint8_t y_index = 2;
constexpr uint8_t sp_index = 3;
constexpr uint8_t sr_index = 4;


class CPU6502 {
    struct Instruction {
        void (CPU6502::* instruction)();
    };
protected:
    Memory ram;
    Memory stack;
    Memory registers;

    uint16_t pc;
    Bus& bus;

    RP2A03 co_proc;

    static Instruction lookupTable[16][16];
    enum flags {
        CARRY = 0x01,
        ZERO = 0x02,
        INTERRUPT = 0x04,
        DECIMAL = 0x08,
        B = 0x10,
        ALWAYS_HIGH = 0x20,
        OVERFLOW = 0x40,
        NEGATIVE = 0x80
    };
    bool error;
    //////////////ADRESSING MODES//////////////////////////////
    void x_ind();
    void imm();
    void abs();
    void ind();
    void ind_y();
    void zp0();
    void zpx();
    void zpy();
    void aby();
    void abx();
    void rel();
    void acc();
    void imp();
    void call_addr_mode(uint8_t opcode);
    void mod_zero_neg_flags(int8_t result);
    void mod_zero_neg_carry_flags(int8_t result);
    void mod_zero(int8_t result);
    void indexed_indirect();
    void indirect_indexed();
    void indirect();
    void fetch_address(uint8_t indexed = 0, uint16_t mask=0xFFFF);
    void fetch_rel_address();
    //////////////ADRESSING MODES//////////////////////////////
    void push(uint8_t data);
    uint8_t pop();
    void push_pc();
    void pop_pc();
    void branch();
    /////////////INSTRUCTIONS///////////////////////////////////
    void BRK();
    void ORA();
    void invalid();
    void SLO();
    void NOP();
    void ASL();
    void PHP();
    void ANC();
    void BPL();
    void CLC();
    void JSR();
    void AND();
    void RLA();
    void BIT();
    void ROL();
    void PLP();
    void BMI();
    void SEC();
    void RTI();
    void EOR();
    void SRE();
    void PHA();
    void LSR();
    void JMP();
    void ALR();
    void BVC();
    void CLI();
    void RTS();
    void ADC();
    void RRA();
    void PLA();
    void ROR();
    void ARR();
    void BVS();
    void SEI();
    void STA();
    void STY();
    void STX();
    void DEY();
    void TXA();
    void TYA();
    void TXS();
    void LDA();
    void LDY();
    void LDX();
    void TAX();
    void TAY();
    void CLV();
    void TSX();
    void CPY();
    void CMP();
    void DEC();
    void INY();
    void DEX();
    void CLD();
    void CPX();
    void SBC();
    void INC();
    void INX();
    void SED();
    void BCC();
    void BCS();
    void BNE();
    void BEQ();
    void SAX();
    void AHX();
    void LAX();
    void DCP();
    void ISB();
    void TAS();
    void LAS();
    void AXS();
    void SHY();
    void SHX();
    void XAA();
    /////////////INSTRUCTIONS///////////////////////////////////////////
public:
    CPU6502(Bus& main_bus, Memory&& ram);
    bool execute();
    void reset();
    void set_pc(uint16_t address);
    friend std::ostream& operator<<(std::ostream& os, const CPU6502&);
    friend class Nes;
};

#endif //NES_CPU6502_H
