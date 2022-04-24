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
void Screen::render_tiles() {
    uint8_t tile_size_in_memory = 16;

    uint8_t LCD_control = cpu->read_memory(LCDC); // store the LCD control register
    uint8_t scroll_x = cpu->read_memory(SCX);
    uint8_t scroll_y = cpu->read_memory(SCY);
    uint8_t window_x = cpu->read_memory(WX);
    uint8_t window_y = cpu->read_memory(WY);

    bool window = false;
    
    // check if we're drawing a window in this scanline
    if ((LCD_control & 0x4) >> 2) {
        if (window_y  <= LY) {
            window = true;
        }
    }

    uint16_t tile_map_loc;  // this will store the location of the tile in the background map
    
    // if there's no window, the background map will be here, otherwise the window will be here
    if (!window) { 
        if ((LCD_control & 0x10) >> 4) {
            tile_map_loc = 0x9C00;
        } else {
            tile_map_loc = 0x9800;
        }
    } else {
       if ((LCD_control & 0x2) >> 1) { 
           tile_map_loc = 0x9C00;
       } else {
           tile_map_loc = 0x9800;
       }
    }

    uint8_t abs_y = cpu->read_memory(LY) + scroll_y; // the absolute y position in the scanline
    uint16_t tile_row = (abs_y / 8) * 32;  // the vertical tile. TODO: what data structure to use here?
    
    uint16_t tile_data_address = 0; // this will store where the actual tile data lives


    for (int row_num = 0; row_num < 160; row_num++) {
        uint8_t abs_x; // TODO: calculate the x position into the va
        
        // TODO: calculate tile col, not sure what data structure to use
        
        tile_map_loc = tile_map_loc + tile_row + tile_col; // this will store where the tile id lives in the background map

        // TODO read the memory at the location calculated in tile_map_loc to get the tile id

        if ((LCD_control & 0x8) >> 3) {
            tile_data_address = 0x8000 + (tile_id)*tile_size_in_memory;
        } else {
            tile_data_address = 0x9000 + (int8_t)tile_id * tile_size_in_memory;
        }

        uint8_t row_byte1 = cpu->read_memory(tile_data_address);
        uint8_t row_byte2 = cpu->read_memory(tile_data_address + 1);


        // below this line not refactored, variable names and logic may be wrong
        for (int bit_num = 0; bit_num < 8; bit_num++) {
            uint8_t color = (row_byte1 & 0b10000000) + ((row_byte2 & 0b10000000) << 1);
            set_pixel(color, tile_x_on_screen + bit_num, tile_y_on_screen + row_num);
            row_byte1 <<= 1;
            row_byte2 <<= 1;
        }

        tile_address += 2;
    }
}
