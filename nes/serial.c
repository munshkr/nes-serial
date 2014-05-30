// This is based on one of Shiru's CC65 NES examples
// and uses his neslib and init code

#include "neslib.h"


// macro to calculate nametable address from X,Y in compile time

#define NTADR(x,y) ((NAMETABLE_A|((y)<<5)|x))


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
    // rendering is disabled at the startup, the palette is all black

    pal_col(1, 0x30); // set while color

    // you can't put data into vram through vram_put while rendering is enabled
    // so you have to disable rendering to put things like text or a level map
    // into the nametable

    // there is a way to update small number of nametable tiles while rendering
    // is enabled, using set_vram_update and an update list

    put_str(NTADR(2, 2),"HELLO, WORLD!");

    ppu_on_all(); // enable rendering

    while(1); // do nothing, infinite loop
}
