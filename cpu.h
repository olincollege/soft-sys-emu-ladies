#include "register.h"
#include <stdint.h>
#include <cstdio>

class Cpu {
public:
    Register AF;
    Register BC;
    Register DE;
    Register HL;

    Cpu();

    int write_memory(uint8_t address, uint8_t data);
    uint8_t read_memory(uint8_t address);

private:
    uint8_t memory[0x10000];
    uint16_t PC;
    uint16_t SP;
};

