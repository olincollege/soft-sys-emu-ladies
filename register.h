#include <stdint.h>    

class Register {
    public: 
        uint8_t get_lo();
        uint8_t get_hi();
        uint16_t get_all();

        void set_lo(uint8_t val);
        void set_hi(uint8_t val);
        void set_all(uint16_t val);

        Register() {
            reg = 0x0000;
        }
    
    protected:
        uint16_t reg;
};