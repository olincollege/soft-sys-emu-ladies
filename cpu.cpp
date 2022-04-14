#include "cpu.h"

Cpu::Cpu() {
    AF.set_all(0x01B0);
    BC.set_all(0x0013);
    DE.set_all(0x00D8);
    HL.set_all(0x014D);
    
    PC = 0x0100;
    SP = 0xFFFE;

    // memory[]
}

uint16_t Cpu::get_PC(){
    return PC;
}

uint16_t Cpu::get_SP() {
    return SP;
}

void Cpu::set_PC(uint16_t bytes){
    PC = bytes;
}

void Cpu::set_SP(uint16_t bytes){
    SP = bytes;
    
int Cpu::write_memory(uint8_t address, uint8_t data) {
    if (address < 0x8000) {
        fprintf(stderr, "Tried to write to read-only memory");
        return 0;

    } else if ((address >= 0xE000) && (address < 0xFE00)) {
        memory[address] = data;
        write_memory(address-0x2000, data);
        return 1;
    
    } else if ((address >= 0xFEA0) && (address < 0xFEFF)) {
        fprintf(stderr, "Tried to write to restricted memory");
        return 0;

    } else {
        memory[address] = data;
        return 1;
    }
}

uint8_t Cpu::read_memory(uint8_t address) {
    return memory[address];
    // TODO: we don't know if restricted memory is readable
}