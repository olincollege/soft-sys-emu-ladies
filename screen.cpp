#include "screen.h"
#include <cstdio>
#include <stdint.h>

int scanline_counter = 0;

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
    window[x + width * y] = pixel;
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
    return &window[0];
}

void Screen::draw_all_scanlines(int cycles) {
  scanline_counter += cycles;

  if (scanline_counter >= 456) {
    //move to the next line
    uint8_t curr_line = cpu->read_memory(LY);
    curr_line++;
    cpu->write_memory(LY, curr_line);

    scanline_counter = 0;

    if (curr_line == 144) {
      // TODO: ENTER VBLANK

    } else if (curr_line > 154) { // go back to the first line
      cpu->write_memory(LY, 0);

    } else if (curr_line < 144) {
      draw_scanline();
    }
  }
}

//vblank, hblank stuff
void Screen::set_lcd_status() {
  //uint8_t lcd_status = cpu->read_memory(STAT);
  //uint8_t curr_line = cpu->read_memory(LY);

  // rest of the stuff.... do we need to implement interrupts?
}

// tileset is referenced in lcd register - a bit, 0 or 1
void Screen::draw_scanline() {
    uint8_t tile_size_in_memory = 16;

    uint8_t LCD_control = cpu->read_memory(LCDC); // store the LCD control register
    uint8_t scroll_x = cpu->read_memory(SCX);
    uint8_t scroll_y = cpu->read_memory(SCY);
    // uint8_t window_x = cpu->read_memory(WX);
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
    uint16_t tile_row = (abs_y >> 8) * 32;  // what tile we are on if the tiles were in a long line, granularity to row

    uint16_t tile_data_address = 0; // this will store where the actual tile data lives


    for (int pixel = 0; pixel < 160; pixel++) {
        uint8_t abs_x = pixel + scroll_x;

        //NOTE: some window stuff would go here. not implementing it.

        uint16_t tile_col = abs_x >> 8;
        uint16_t tile_id = tile_map_loc + tile_row + tile_col; // this will store where the tile id lives in the background map

        // TODO codeslinger includes this 128 offset without explaining it. should check why it is there.
        if ((LCD_control & 0x8) >> 3) {
            tile_data_address = 0x8000 + (tile_id)*tile_size_in_memory;
        } else {
            tile_data_address = 0x9000 + ((int8_t)tile_id + 128) * tile_size_in_memory;
        }

        // get the bytes that contain the row's color data
        uint8_t row_within_tile = abs_y % 8;
        uint16_t curr_row_address = tile_data_address + 2*row_within_tile;
        uint8_t row_byte1 = cpu->read_memory(curr_row_address);
        uint8_t row_byte2 = cpu->read_memory(curr_row_address + 1);

        uint8_t pixel_within_row = abs_x % 8;

        //bitshifting to grab actual pixel data
        uint8_t color = (row_byte1 & 1<<(8-pixel_within_row)) + ((row_byte2 & (8-pixel_within_row)) << 1);
        //NOTE: some palatte stuff would go here. not implementing it.
        set_pixel(color, abs_x, abs_y);
    }
}
