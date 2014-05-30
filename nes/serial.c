// This is based on one of Shiru's CC65 NES examples
// and uses his neslib and init code

#include "neslib.h"

#define NTADR(x,y) ((NAMETABLE_A|((y)<<5)|x))

#define MSB(x)        (((x)>>8))
#define LSB(x)        (((x)&0xff))

// variables
static unsigned char val;

// the update list, it is for 6 tiles, 3 bytes per tile
static unsigned char list[6*3+1];

// init data for the update list, it contains MSB and LSB of a tile address
// in the nametable, then the tile number
const unsigned char list_init[6*3+1]={
    MSB(NTADR(9,4)), LSB(NTADR(9,4)), 0, // non-sequental updates
    MSB(NTADR(10,4)), LSB(NTADR(10,4)), 0,
    MSB(NTADR(11,4)), LSB(NTADR(11,4)), 0,

    NT_UPD_EOF
};

// put a string into the nametable
void put_str(unsigned int adr,const char *str)
{
    vram_adr(adr);

    while(1)
    {
        if (!*str) break;
        vram_put((*str++) - 0x20); //-0x20 because ASCII code 0x20 is placed in tile 0 of the CHR
    }
}


void main(void)
{
    pal_col(1, 0x30); // white

    // initialize update list
    memcpy(list, list_init, sizeof(list_init));

    set_vram_update(list);

    put_str(NTADR(2, 2), "NES-SERIAL");
    put_str(NTADR(2, 4), "VALUE: ");

    ppu_on_all(); // enable rendering

    while(1)
    {
        ppu_wait_frame(); // wait for next TV frame

        val = pad_poll(0);  // poll joystick 0, i contains 8bit value

        if (val > 0) {
            // change update list to reflect new value
            list[2]= val / 100     + 0x10;
            list[5]= val / 10 % 10 + 0x10;
            list[8]= val      % 10 + 0x10;
        }
    }
}
