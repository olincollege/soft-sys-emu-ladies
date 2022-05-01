#include "cpu.h"

int Cpu::op_jpnn() {
    uint16_t address = (read_memory(PC) << 8) | read_memory(PC+1);
    set_PC(address);
}