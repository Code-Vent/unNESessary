//
// Created by Hamid on 2/28/2025.
//

#include "cpu6502.h"
#include <cassert>


CPU6502::Instruction CPU6502::lookupTable[16][16] = {
        {&CPU6502::BRK, &CPU6502::ORA, &CPU6502::invalid, &CPU6502::SLO, &CPU6502::NOP, &CPU6502::ORA, &CPU6502::ASL, &CPU6502::SLO, &CPU6502::PHP, &CPU6502::ORA, &CPU6502::ASL, &CPU6502::ANC, &CPU6502::NOP, &CPU6502::ORA, &CPU6502::ASL, &CPU6502::SLO},
        {&CPU6502::BPL, &CPU6502::ORA, &CPU6502::invalid, &CPU6502::SLO, &CPU6502::NOP, &CPU6502::ORA, &CPU6502::ASL, &CPU6502::SLO, &CPU6502::CLC, &CPU6502::ORA, &CPU6502::NOP, &CPU6502::SLO, &CPU6502::NOP, &CPU6502::ORA, &CPU6502::ASL, &CPU6502::SLO},
        {&CPU6502::JSR, &CPU6502::AND, &CPU6502::invalid, &CPU6502::RLA, &CPU6502::BIT, &CPU6502::AND, &CPU6502::ROL, &CPU6502::RLA, &CPU6502::PLP, &CPU6502::AND, &CPU6502::ROL, &CPU6502::ANC, &CPU6502::BIT, &CPU6502::AND, &CPU6502::ROL, &CPU6502::RLA},
        {&CPU6502::BMI, &CPU6502::AND, &CPU6502::invalid, &CPU6502::RLA, &CPU6502::NOP, &CPU6502::AND, &CPU6502::ROL, &CPU6502::RLA, &CPU6502::SEC, &CPU6502::AND, &CPU6502::NOP, &CPU6502::RLA, &CPU6502::NOP, &CPU6502::AND, &CPU6502::ROL, &CPU6502::RLA},
        {&CPU6502::RTI, &CPU6502::EOR, &CPU6502::invalid, &CPU6502::SRE, &CPU6502::NOP, &CPU6502::EOR, &CPU6502::LSR, &CPU6502::SRE, &CPU6502::PHA, &CPU6502::EOR, &CPU6502::LSR, &CPU6502::ALR, &CPU6502::JMP, &CPU6502::EOR, &CPU6502::LSR, &CPU6502::SRE},
        {&CPU6502::BVC, &CPU6502::EOR, &CPU6502::invalid, &CPU6502::SRE, &CPU6502::NOP, &CPU6502::EOR, &CPU6502::LSR, &CPU6502::SRE, &CPU6502::CLI, &CPU6502::EOR, &CPU6502::NOP, &CPU6502::SRE, &CPU6502::NOP, &CPU6502::EOR, &CPU6502::LSR, &CPU6502::SRE},
        {&CPU6502::RTS, &CPU6502::ADC, &CPU6502::invalid, &CPU6502::RRA, &CPU6502::PLA, &CPU6502::ADC, &CPU6502::ROR, &CPU6502::ARR, &CPU6502::JMP, &CPU6502::ADC, &CPU6502::ROR, &CPU6502::RRA, &CPU6502::BVS, &CPU6502::ADC, &CPU6502::invalid, &CPU6502::RRA},
        {&CPU6502::SEI, &CPU6502::ADC, &CPU6502::NOP, &CPU6502::RRA, &CPU6502::NOP, &CPU6502::ADC, &CPU6502::ROR, &CPU6502::RRA, &CPU6502::NOP, &CPU6502::ADC, &CPU6502::ROR, &CPU6502::RRA, &CPU6502::NOP, &CPU6502::ADC, &CPU6502::ROR, &CPU6502::RRA},
        {&CPU6502::NOP, &CPU6502::STA, &CPU6502::NOP, &CPU6502::SAX, &CPU6502::STY, &CPU6502::STA, &CPU6502::STX, &CPU6502::SAX, &CPU6502::DEY, &CPU6502::NOP, &CPU6502::TXA, &CPU6502::XAA, &CPU6502::STY, &CPU6502::STA, &CPU6502::STX, &CPU6502::SAX},
        {&CPU6502::BCC, &CPU6502::STA, &CPU6502::NOP, &CPU6502::AHX, &CPU6502::STY, &CPU6502::STA, &CPU6502::STX, &CPU6502::SAX, &CPU6502::TYA, &CPU6502::STA, &CPU6502::TXS, &CPU6502::TAS, &CPU6502::SHY, &CPU6502::STA, &CPU6502::SHX, &CPU6502::AHX},
        {&CPU6502::LDY, &CPU6502::LDA, &CPU6502::LDX, &CPU6502::LAX, &CPU6502::LDY, &CPU6502::LDA, &CPU6502::LDX, &CPU6502::LAX, &CPU6502::TAY, &CPU6502::LDA, &CPU6502::TAX, &CPU6502::NOP, &CPU6502::LDY, &CPU6502::LDA, &CPU6502::LDX, &CPU6502::LAX},
        {&CPU6502::BCS, &CPU6502::LDA, &CPU6502::NOP, &CPU6502::LAX, &CPU6502::LDY, &CPU6502::LDA, &CPU6502::LDX, &CPU6502::LAX, &CPU6502::CLV, &CPU6502::LDA, &CPU6502::TSX, &CPU6502::LAS, &CPU6502::LDY, &CPU6502::LDA, &CPU6502::LDX, &CPU6502::LAX},
        {&CPU6502::CPY, &CPU6502::CMP, &CPU6502::NOP, &CPU6502::DCP, &CPU6502::CPY, &CPU6502::CMP, &CPU6502::DEC, &CPU6502::DCP, &CPU6502::INY, &CPU6502::CMP, &CPU6502::DEX, &CPU6502::AXS, &CPU6502::CPY, &CPU6502::CMP, &CPU6502::DEC, &CPU6502::DCP},
        {&CPU6502::BNE, &CPU6502::CMP, &CPU6502::NOP, &CPU6502::DCP, &CPU6502::NOP, &CPU6502::CMP, &CPU6502::DEC, &CPU6502::DCP, &CPU6502::CLD, &CPU6502::CMP, &CPU6502::NOP, &CPU6502::DCP, &CPU6502::NOP, &CPU6502::CMP, &CPU6502::DEC, &CPU6502::DCP},
        {&CPU6502::CPX, &CPU6502::SBC, &CPU6502::NOP, &CPU6502::ISB, &CPU6502::CPX, &CPU6502::SBC, &CPU6502::INC, &CPU6502::ISB, &CPU6502::INX, &CPU6502::SBC, &CPU6502::NOP, &CPU6502::SBC, &CPU6502::CPX, &CPU6502::SBC, &CPU6502::INC, &CPU6502::ISB},
        {&CPU6502::BEQ, &CPU6502::SBC, &CPU6502::NOP, &CPU6502::ISB, &CPU6502::NOP, &CPU6502::SBC, &CPU6502::INC, &CPU6502::ISB, &CPU6502::SED, &CPU6502::SBC, &CPU6502::NOP, &CPU6502::ISB, &CPU6502::NOP, &CPU6502::SBC, &CPU6502::INC, &CPU6502::ISB}
};

#define a registers[a_index]
#define x registers[x_index]
#define y registers[y_index]
#define sp registers[sp_index]
#define sr registers[sr_index]

CPU6502::CPU6502(Bus& main_bus, Memory&& r)
        : ram(std::move(r)),
        stack({.lower=0, .upper=0xFF}, 0x100),
        registers({.lower=reg_base_addr, .upper=reg_base_addr+4}, 5),
        bus(main_bus)
{
    bus.clock_cycles = 0;
    a = 0; // Accumulator
    x = 0; // X Register
    y = 0; // Y Register
    sr = 0; // Processor Status
    sp = 0xFF; // Stack Pointer
    pc = 0; // Program Counter
    error = false;
    bus.add(registers);
    bus.add(ram);
}

uint8_t CPU6502::pop() {
    if (sp < 0xff)
        sp++;
    return stack.read(sp);
}

void CPU6502::push(uint8_t data) {
    stack.write(sp, data);
    if (sp > 0)
        sp--;
}

void CPU6502::push_pc() {
    push((pc >> 8) & 0x00FF);
    push(pc & 0x00FF);
}

void CPU6502::branch() {
    bus.set_address_rel(pc);
    pc = bus.address();
    bus.clock_cycles++;
}

void CPU6502::pop_pc() {
    auto lo = pop();
    auto hi = pop();
    pc = (hi << 8) | lo;
}

void CPU6502::mod_zero(int8_t result) {
    sr = (result == 0)? sr | flags::ZERO : sr & ~flags::ZERO;
}

void CPU6502::mod_zero_neg_flags(int8_t result) {
    sr = (result == 0)? sr | flags::ZERO : sr & ~flags::ZERO;
    sr = (result | 0x80)? sr | flags::NEGATIVE : sr & ~flags::NEGATIVE;
}

void CPU6502::mod_zero_neg_carry_flags(int8_t result) {
    sr = (result == 0)? sr | flags::ZERO : sr & ~flags::ZERO;
    sr = (result | 0x80)? sr | flags::NEGATIVE : sr & ~flags::NEGATIVE;
    sr = (sr | flags::NEGATIVE)? sr & ~flags::CARRY : sr | flags::CARRY;
}

void CPU6502::call_addr_mode(uint8_t opcode) {
    //Addressing Mode
    switch (opcode) {
        // Accumulator
        case 0x0A: // ASL
        case 0x4A: // LSR
        case 0x2A: // ROL
        case 0x6A: // ROR
            CPU6502::acc();
            break;

            // Immediate
        case 0x09: case 0x29: case 0x49: case 0x69: case 0xA9: case 0xC9: case 0xE9:
        case 0x0B: case 0x2B: case 0xCB: case 0xA0: case 0xA2: case 0xC0: case 0xE0:
        case 0x80: case 0x82: case 0x89: case 0xC2: case 0xE2: case 0x4B: case 0x6B:
        case 0x8B: case 0xAB: case 0xEB:
            CPU6502::imm();
            break;

            // Zero Page
        case 0x05: case 0x25: case 0x45: case 0x65: case 0x85: case 0xA5: case 0xC5:
        case 0xE5: case 0x07: case 0x87: case 0xA7: case 0xC7: case 0xE7: case 0x47:
        case 0x06: case 0x24: case 0x26: case 0x46: case 0x66: case 0x84: case 0x86:
        case 0xA4: case 0xA6: case 0xC4: case 0xC6: case 0xE4: case 0xE6: case 0x04:
        case 0x44: case 0x64: case 0x27: case 0x67:
            CPU6502::zp0();
            break;

            // Zero Page,X
        case 0x15: case 0x35: case 0x55: case 0x75: case 0x95: case 0xB5: case 0xD5:
        case 0xF5: case 0x17: case 0xD7: case 0xF7: case 0x57: case 0x16: case 0x36:
        case 0x56: case 0x76: case 0x94: case 0xB4: case 0xD6: case 0xF6: case 0x14:
        case 0x34: case 0x54: case 0x74: case 0xD4: case 0xF4: case 0x37: case 0x77:
            CPU6502::zpx();
            break;

            // Zero Page,Y
            case 0x96: case 0xB6: case 0x97: case 0xB7:
            CPU6502::zpy();
            break;

            // Absolute
            case 0x0D: case 0x2D: case 0x4D: case 0x6D: case 0x8D: case 0xAD: case 0xCD:
            case 0xED: case 0x4C: case 0x0F: case 0x8F: case 0xAF: case 0xCF: case 0xEF:
            case 0x4F: case 0x0E: case 0x20: case 0x2C: case 0x4E: case 0x6E: case 0x8C:
            case 0x8E: case 0xAC: case 0xAE: case 0xCC: case 0xCE: case 0xEC: case 0xEE:
            case 0x0C: case 0x2F: case 0x6F:
            CPU6502::abs();
            break;

            // Absolute,X
        case 0x1D: case 0x3D: case 0x5D: case 0x7D: case 0x9D: case 0xBD: case 0xDD:
        case 0xFD: case 0x1F: case 0xDF: case 0xFF: case 0x5F: case 0x1E: case 0x2E:
        case 0x3E: case 0x5E: case 0x7E: case 0x9C: case 0xBC: case 0xDE: case 0xFE:
        case 0x1C: case 0x3C: case 0x5C: case 0x7C: case 0xDC: case 0xFC: case 0x3F:
        case 0x7F:
            CPU6502::abx();
            break;

            // Absolute,Y
        case 0x19: case 0x39: case 0x59: case 0x79: case 0x99: case 0xB9: case 0xD9:
        case 0xF9: case 0x1B: case 0x9F: case 0xBF: case 0xDB: case 0xFB: case 0x9B:
        case 0xBB: case 0x5B: case 0x9E: case 0xBE: case 0x3B: case 0x7B:
            CPU6502::aby();
            break;

            // Indirect
        case 0x6C: // JMP (Indirect)
            CPU6502::ind();
            break;

            // Indexed Indirect (Indirect,X)
        case 0x01: case 0x21: case 0x41: case 0x61: case 0x81: case 0xA1: case 0xC1:
        case 0xE1: case 0x03: case 0x83: case 0xA3: case 0xC3: case 0xE3: case 0x43:
        case 0x23: case 0x63:
            CPU6502::x_ind();
            break;

            // Indirect Indexed (Indirect),Y
        case 0x11: case 0x31: case 0x51: case 0x71: case 0x91: case 0xB1: case 0xD1:
        case 0xF1: case 0x13: case 0x93: case 0xB3: case 0xD3: case 0xF3: case 0x53:
        case 0x33: case 0x73:
            CPU6502::ind_y();
            break;

            // Relative
        case 0x10: case 0x30: case 0x50: case 0x70: case 0x90: case 0xB0: case 0xD0: case 0xF0:
            CPU6502::rel();
            break;

            // Implied
        case 0x00: case 0x08: case 0x18: case 0x28: case 0x38: case 0x48: case 0x58: case 0x68:
        case 0x78: case 0x88: case 0x98: case 0xA8: case 0xB8: case 0xC8: case 0xD8: case 0xE8:
        case 0xF8: case 0xCA: case 0xEA: case 0xBA: case 0x8A: case 0xAA: case 0x9A: case 0x40:
        case 0x60: case 0x1A: case 0x3A: case 0x5A: case 0x7A: case 0xDA: case 0xFA:
        case 0x02: case 0x12: case 0x22: case 0x32: case 0x42: case 0x52: case 0x62: case 0x72:
        case 0x92: case 0xB2: case 0xD2: case 0xF2:
            CPU6502::imp();
            break;

            // Unknown opcode
        default:
            // Could log unknown opcode here
            std::cerr << std::hex << "\nunknown opcode: " << (int)opcode << std::endl;
            assert(false);
            break;
    }
}

bool CPU6502::execute() {
    uint8_t opcode = bus.read(pc++);
    bus.clock_cycles = 0;
    call_addr_mode(opcode);
    uint8_t row = (opcode & 0xF0) >> 4;
    uint8_t col = (opcode & 0x0F);
    (this->*lookupTable[row][col].instruction)();
    return !error;
}

void CPU6502::reset() {
    pc = (bus.read(0xFFFD) << 8) | bus.read(0xFFFC);
    x = y = 0;
    a = 0;
    sr = flags::ALWAYS_HIGH | flags::INTERRUPT;
    sp = 0xFF;
    bus.latch_data(0);
    error = false;
}

void CPU6502::x_ind() {
    uint16_t t = bus.read(pc);
    pc++;
    uint16_t lo = bus.read((uint16_t)(t + (uint16_t)x) & 0x00FF);
    uint16_t hi = bus.read((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);
    uint16_t addr_abs = (hi << 8) | lo;
    bus.latch_data(addr_abs);
    bus.clock_cycles += 6;
}

void CPU6502::imm() {
    bus.latch_data(pc);
    pc++;
    bus.clock_cycles += 2;
}

void CPU6502::abs() {
    bus.latch_address(pc);
    pc += 2;
    bus.latch_data();
    bus.clock_cycles += 4;
}

void CPU6502::ind() {
    bus.latch_address(pc);
    pc += 2;
    bus.latch_address();
    //bus.latch_data();
    bus.clock_cycles += 5;
}

void CPU6502::ind_y() {
    uint16_t t = bus.read(pc);
    pc++;
    uint16_t lo = bus.read(t & 0x00FF);
    uint16_t hi = bus.read((t + 1) & 0x00FF);

    uint16_t addr_abs = (hi << 8) | lo;
    addr_abs += y;

    if ((addr_abs & 0xFF00) != (hi << 8))
        bus.clock_cycles++;
    bus.latch_data(addr_abs);
    bus.clock_cycles += 5;
}

void CPU6502::zp0() {
    uint16_t address = bus.read(pc);
    bus.latch_data(address & 0x00FF);
    pc++;
    bus.clock_cycles += 3;
}

void CPU6502::zpx() {
    uint16_t address = bus.read(pc) + x;
    bus.latch_data(address & 0x00FF);
    pc++;
    bus.clock_cycles += 4;
}

void CPU6502::zpy() {
    uint16_t address = bus.read(pc) + y;
    bus.latch_data(address & 0x00FF);
    pc++;
    bus.clock_cycles += 4;
}

void CPU6502::aby() {
    bus.latch_address(pc);
    pc += 2;
    bus.latch_data_rel(y);
    bus.clock_cycles += 4;
}

void CPU6502::abx() {
    bus.latch_address(pc);
    pc += 2;
    bus.latch_data_rel(x);
    bus.clock_cycles += 4;
}

void CPU6502::rel() {
    bus.latch_data(pc);
    pc++;
    bus.clock_cycles += 2;
}

void CPU6502::acc() {
    bus.latch_data(reg_base_addr + a_index);
    bus.clock_cycles += 2;
}

void CPU6502::imp() {
    bus.clock_cycles += 2;
}


///////////////////////////////////////////////////////////////////////////


void CPU6502::BRK() {
    bus.clock_cycles += 5;
    pc += 2;
    push_pc();
    push(sr);
    sr |= flags::B | flags::INTERRUPT;
    pc = (uint16_t)bus.read(0xFFFE) | ((uint16_t)bus.read(0xFFFF) << 8);
}

void CPU6502::ORA() {
    a |= bus.data(); // Dummy ORA logic
    mod_zero_neg_flags(a);
}

void CPU6502::invalid() {
    //bus.clock_cycles += 2; // Invalid Opcode
}

void CPU6502::SLO() {
    bus.clock_cycles += 2;
    auto data = bus.data();
    (data & 0x80)? sr |= flags::CARRY : sr &= ~flags::CARRY;
    data <<= 1;
    a |= data;
    mod_zero_neg_flags(a);
}

void CPU6502::NOP() {
    //bus.clock_cycles += 2;
}

void CPU6502::ASL() {
    bus.clock_cycles += 2;
    sr |= ((uint8_t)(bus.data() >> 7) & flags::CARRY);
    auto data = bus.data() << 1;
    mod_zero_neg_flags(data);
    bus.write(data);
}

void CPU6502::PHP() {
    bus.clock_cycles += 1;
    push(sr);
}

void CPU6502::ANC() {
    a &= bus.data();
    sr = (a == 0x80) ? sr | flags::CARRY : sr & ~flags::CARRY;
}

void CPU6502::BPL() {
    if (!(sr & flags::NEGATIVE))
        branch();
}

void CPU6502::CLC() {
    sr &= ~flags::CARRY;
}

void CPU6502::JSR() {
    bus.clock_cycles += 2;
    pc--;
    push_pc();
    pc = bus.address();
}

void CPU6502::AND() {
    a &= (bus.data() & 0x00FF);
    mod_zero_neg_flags(a);
}

void CPU6502::PLP() {
    bus.clock_cycles += 2;
    sr = pop();
}

void CPU6502::BMI() {
    if (sr & flags::NEGATIVE)
        branch();
}

void CPU6502::SEC() {
    sr |= flags::CARRY;
}

void CPU6502::RTI() {
    bus.clock_cycles += 4;
    sr = pop();
    pop_pc();
}

void CPU6502::EOR() {
    a ^= bus.data();
    mod_zero_neg_flags(a);
}

void CPU6502::PHA() {
    bus.clock_cycles += 1;
    push(a);
}

void CPU6502::LSR() {
    bus.clock_cycles += 2;
    sr &= ~flags::CARRY;
    sr ^= (bus.data() & flags::CARRY);
    auto temp = bus.data() >> 1;
    mod_zero_neg_flags(temp);
    bus.write(temp);
}

void CPU6502::JMP() {
    pc = bus.address();
}

void CPU6502::RTS() {
    bus.clock_cycles += 4;
    pop_pc();
    pc++;
}

void CPU6502::ADC() {
    uint8_t carry = (sr & flags::CARRY);
    auto result = a + bus.data() + carry;
    if (result > 0xFF) sr |= flags::CARRY;
    if ((result ^ a) & (result ^ bus.data()) & 0x80) sr |= flags::OVERFLOW;
    mod_zero_neg_flags(result);
    a = result;
}

void CPU6502::PLA() {
    bus.clock_cycles += 2;
    a = pop();
    mod_zero_neg_flags(a);
}

void CPU6502::ROR() {
    bus.clock_cycles += 2;
    auto temp = bus.data() & 0xFEFF;
    temp ^= ((sr & flags::CARRY) << 8);
    sr &= ~flags::CARRY;
    sr ^= (temp & flags::CARRY);
    temp >> 1;
    bus.write(temp & 0x00FF);
    mod_zero_neg_flags(temp & 0x00FF);
}

void CPU6502::STA() {
    // Store accumulator to memory
    bus.write(a);
}

void CPU6502::LDA() {
    a = bus.data();
    mod_zero_neg_flags(a);
}

void CPU6502::CMP() {
    auto result = a - bus.data();
    mod_zero_neg_carry_flags(result);
}

void CPU6502::INC() {
    bus.clock_cycles += 2;
    bus.inc();
    mod_zero_neg_flags(bus.data());
    bus.write();
}

void CPU6502::SED() {
    sr |= flags::DECIMAL;
}

void CPU6502::BCC() {
    if (!(sr & flags::CARRY))
        branch();
}

void CPU6502::BCS() {
    if (sr & flags::CARRY)
        branch();
}

void CPU6502::BNE() {
    if (!(sr & flags::ZERO))
        branch();
}

void CPU6502::BEQ() {
    if (sr & flags::ZERO)
        branch();
}

void CPU6502::SAX() {
    a &= x;
    bus.write(a);
}

void CPU6502::AHX() {
    uint8_t result = a & x & (pc >> 8);
    bus.write(result);
}

void CPU6502::LAX() {
    a = x = bus.data();
    mod_zero_neg_flags(a);
}

void CPU6502::DCP() {
    bus.clock_cycles += 2;
    bus.dec();
    CMP();
}

void CPU6502::ISB() {
    bus.clock_cycles += 2;
    bus.inc();
    SBC();
}

void CPU6502::TAS() {
    sp = a & x & (pc >> 8);
    bus.write(sp);
}

void CPU6502::LAS() {
    a = x = sp &= bus.data();
    mod_zero_neg_flags(a);
}

void CPU6502::AXS() {
    x &= a;
    x -= bus.data();
    mod_zero_neg_carry_flags(x);
}

void CPU6502::SHY() {
    uint8_t result = y & ((pc >> 8) + 1);
    bus.write(result);
}

void CPU6502::SHX() {
    uint8_t result = x & ((pc >> 8) + 1);
    bus.write(result);
}

void CPU6502::RLA() {
    ROL();
    AND();
}

void CPU6502::BIT() {
    auto result = a & bus.data();
    mod_zero(result);
    sr |= (bus.data() & flags::OVERFLOW & flags::NEGATIVE);
}

void CPU6502::ROL() {
    bus.clock_cycles += 2;
    auto temp = (uint16_t)bus.data() << 1;
    temp ^= (sr & flags::CARRY);
    sr &= ~flags::CARRY;
    sr ^= ((temp >> 8) & flags::CARRY);
    bus.write(temp & 0x00FF);
    mod_zero_neg_flags(temp & 0x00FF);
}

void CPU6502::SRE() {
    LSR();
    EOR();
}

void CPU6502::ALR() {
    AND();
    LSR();
}

void CPU6502::BVC() {
    if (!(sr & flags::OVERFLOW))
        branch();
}

void CPU6502::CLI() {
    bus.clock_cycles += 2;
    sr &= ~flags::INTERRUPT;
}

void CPU6502::RRA() {
    ROR();
    ADC();
}

void CPU6502::ARR() {
    AND();
    ROR();
}

void CPU6502::BVS() {
    if (sr & flags::OVERFLOW)
        branch();
}

void CPU6502::SEI() {
    sr |= 0x04;
}

void CPU6502::STY() {
    // Store Y register to memory
    bus.write(y);
}

void CPU6502::STX() {
    // Store X register to memory
    bus.write(x);
}

void CPU6502::DEY() {
    y--;
    mod_zero_neg_flags(y);
}

void CPU6502::TXA() {
    a = x;
    mod_zero_neg_flags(a);
}

void CPU6502::TYA() {
    a = y;
    mod_zero_neg_flags(a);
}

void CPU6502::TXS() {
    sp = x;
}

void CPU6502::LDY() {
    y = bus.data();
    mod_zero_neg_flags(y);
}

void CPU6502::LDX() {
    x = bus.data();
    mod_zero_neg_flags(x);
}

void CPU6502::XAA() {
    a &= bus.data();
    TAX();
}

void CPU6502::TAX() {
    x = a;
    mod_zero_neg_flags(x);
}

void CPU6502::TAY() {
    y = a;
    mod_zero_neg_flags(y);
}

void CPU6502::CLV() {
    sr &= ~flags::OVERFLOW;
}

void CPU6502::TSX() {
    x = sp;
    mod_zero_neg_flags(x);
}

void CPU6502::DEC() {
    bus.clock_cycles += 2;
    bus.dec();
    mod_zero_neg_flags(bus.data());
    bus.write();
}

void CPU6502::INY() {
    y++;
    mod_zero_neg_flags(y);
}

void CPU6502::DEX() {
    x--;
    mod_zero_neg_flags(x);
}

void CPU6502::CLD() {
    sr &= ~flags::DECIMAL;
}

void CPU6502::INX() {
    x++;
    mod_zero_neg_flags(x);
}

void CPU6502::CPY() {
    auto result = y - bus.data();
    mod_zero_neg_carry_flags(result);
}

void CPU6502::CPX() {
    auto result = x - bus.data();
    mod_zero_neg_carry_flags(result);
}

void CPU6502::SBC() {
    bus.clock_cycles += 2;
    auto val = ~bus.data();
    auto result = a + val + (sr & flags::CARRY);
    if ((int8_t)a < 0)sr |= flags::CARRY;
    if (a & 0x80)sr |= flags::NEGATIVE;
    if (a == 0)sr |= flags::ZERO;
    if ((result ^ a) & (result ^ val) & 0x80)sr |= flags::OVERFLOW;
    a = result;
}

std::ostream& operator<<(std::ostream& os, const CPU6502& cpu){
    os << "**************************************\n";
    os << std::hex << "PC = " << cpu.pc << std::endl
       << "A = " << (int)cpu.registers[a_index] << std::endl
       << "X = " << (int)cpu.registers[x_index] << std::endl
       << "Y = " << (int)cpu.registers[y_index] << std::endl
       << "SR = " << (int)cpu.registers[sr_index] << std::endl
       << "SP = " << (int)cpu.registers[sp_index] << std::endl;
    os << "**************************************\n";
    return os;
}




