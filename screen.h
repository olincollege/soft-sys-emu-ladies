#include <stdint.h>
class Screen {
    public:
        Screen();

        uint32_t get_pixel();
        void set_pixel(uint8_t color, int x, int y);
        uint32_t bit_color_to_SDL_color(uint8_t);
        uint8_t SDL_color_to_bit_color(uint32_t);
        uint32_t* get_window();

    private:
        uint32_t window[160][144];
};