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
}