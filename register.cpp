#include "register.h"

uint8_t Register::get_lo() {
    return reg & 0x00FF;
}

uint8_t Register::get_hi() {
    return (reg & 0xFF00) >> 8;
}

uint16_t Register::get_all() {
    return reg;
}

void Register::set_lo(uint8_t val) {
    reg = (reg & 0xFF00) | val;
}

void Register::set_hi(uint8_t val) {
    reg = (reg & 0x00FF) | (val << 8);
}

void Register::set_all(uint16_t val) {
    reg = val;
}