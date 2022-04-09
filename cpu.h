#include "register.h"
#include <stdint.h>

class Cpu {
public:
    Register AF;
    Register BC;
    Register DE;
    Register HL;

    Cpu();



private:
    uint8_t memory[0x10000];
    uint16_t PC;
    uint16_t SP;
};

