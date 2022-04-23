#include <stdint.h>
#include "cpu.h"

class Screen {
    public:
        Screen(Cpu* cpu_ptr);

        uint32_t get_pixel();
        void set_pixel(uint8_t color, int x, int y);
        uint32_t bit_color_to_SDL_color(uint8_t);
        uint8_t SDL_color_to_bit_color(uint32_t);
        uint32_t* get_window();

        void load_tile(uint8_t tile_id, uint8_t tileset);

    private:
        uint32_t window[160][144];
        Cpu* cpu;
};
