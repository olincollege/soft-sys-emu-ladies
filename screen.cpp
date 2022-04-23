#include "screen.h"
#include <cstdio>
#include <stdint.h>

Screen::Screen(Cpu* cpu_ptr) {
    cpu = cpu_ptr;

    for (int i=0; i<160; i++) {
        for (int j = 0; j < 144; j++) {
            set_pixel(1, i, j);
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

// tileset is referenced in lcd register - a bit, 0 or 1
void Screen::load_tile(uint8_t tile_id, uint8_t tileset) {
    uint8_t tile_size_in_memory = 16;
    uint16_t tile_address = 0;
    uint8_t tile_x_on_screen = 0; // TODO: figure out where tile is
    uint8_t tile_y_on_screen = 0;

    if (tileset == 1) {
        tile_address = 0x8000 + (tile_id)*tile_size_in_memory;
    } else if (tileset == 0) {
        tile_address = 0x9000 + (int8_t)tile_id * tile_size_in_memory;
    }

    for (int row_num = 0; row_num < 8; row_num++) {
        uint8_t row_byte1 = cpu->read_memory(tile_address);
        uint8_t row_byte2 = cpu->read_memory(tile_address + 1);

        for (int bit_num = 0; bit_num < 8; bit_num++) {
            uint8_t color = (row_byte1 & 0b10000000) + ((row_byte2 & 0b10000000) << 1);
            set_pixel(color, tile_x_on_screen + bit_num, tile_y_on_screen + row_num);
            row_byte1 << 1;
            row_byte2 << 1;
        }

        tile_address += 2;
    }
}
