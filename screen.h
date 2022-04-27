#include <stdint.h>
#include "cpu.h"

#define LCDC 0xFF40
#define STAT 0xFF41
#define SCY 0xFF42
#define SCX 0xFF43
#define LY 0xFF44
#define LYC 0xFF45
#define WX 0xFF4A
#define WY 0xFF4B

class Screen {
    public:
        Screen(Cpu* cpu_ptr);
        
        static const int width = 160;
        static const int height = 144;
        static const int row_size = sizeof(uint32_t) * width;

        uint32_t get_pixel();
        void set_pixel(uint8_t color, int x, int y);
        uint32_t bit_color_to_SDL_color(uint8_t);
        uint8_t SDL_color_to_bit_color(uint32_t);
        uint32_t* get_window();

        void draw_all_scanlines(int cycles);
        void draw_scanline();
        void set_lcd_status();

    private:
        uint32_t window[160 * 144];
        Cpu* cpu;
};
