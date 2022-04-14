#include "register.h"
#include <stdint.h>

class Cpu {
public:
    Register AF;
    Register BC;
    Register DE;
    Register HL;

    Cpu();
    uint16_t get_PC();
    uint16_t get_SP();
    void set_PC(uint16_t bytes);
    void set_SP(uint16_t bytes);

private:
    uint8_t memory[0x10000];
    uint16_t PC;
    uint16_t SP;
};

