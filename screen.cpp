#include "screen.h"
#include <cstdio>

Screen::Screen() {
    for (int i=0; i<160; i++) {
        for (int j = 0; j < 144; j++) {
            window[i][j] = bit_color_to_SDL_color(3);
        }
    }
}

void Screen::set_pixel(uint8_t color, int x, int y) {
    uint32_t pixel = bit_color_to_SDL_color(color);
    window[x][y] = pixel;
}

uint32_t Screen::bit_color_to_SDL_color(uint8_t color_bits) {
    switch (color_bits) {
    case 0:
        return 0xFFFFFFFF;
        break;
    case 1:
        return 0xC0C0C0FF;
        break;
    case 2:
        return 0x606060FF;
        break;
    case 3:
        return 0x000000FF;
        break;
    default:
        fprintf(stderr, "Unknown bit color value\n");
        return -1;
    }
}

uint8_t Screen::SDL_color_to_bit_color(uint32_t color_SDL) {
    switch (color_SDL) {
        case 0xFFFFFFFF:
            return 1;
            break;
        case 0xC0C0C0FF:
            return 1;
            break;
        case 0x606060FF:
            return 2;
            break;
        case 0x000000FF:
            return 3;
            break;
        default:
            fprintf(stderr, "Unknown SDL color value\n");
            return -1;
        }
}

uint32_t* Screen::get_window() {
    return &window[0][0];
}