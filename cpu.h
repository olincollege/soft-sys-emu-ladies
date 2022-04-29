#include "register.h"
#include <stdint.h>
#include <cstdio>
#include <inttypes.h>

class Cpu {
public:
    Register AF;
    Register BC;
    Register DE;
    Register HL;

    Cpu();
    void load_rom(const char* filename);
    uint16_t get_PC();
    uint16_t get_SP();
    void inc_PC();
    
    void set_PC(uint16_t bytes);
    void set_SP(uint16_t bytes);
    int execute_next_opcode();

    int write_memory(uint16_t address, uint8_t data);
    uint8_t read_memory(uint16_t address);

    //opcode functions go under here
    int op_jpnn();

private:
    uint8_t memory[0x10000];
    uint16_t PC;
    uint16_t SP;
};
