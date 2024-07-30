#include <stdbool.h>
#include <stdint.h>
#include "start.h"

#include "cogdata.inc"

#include "swis.h"

#define MAX_ROTATION (sizeof(cog_matrixes) / sizeof(cog_matrixes[0]))

#define XOFFSET (640)
#define YOFFSET (480)


#define os_set_visible_bank(bank) os_byte_out1(113, bank, 0)
#define os_set_output_bank(bank) os_byte_out1(112, bank, 0)


int main(int argc, char *argv[])
{
    int bank = 1;
    int rotation;
    bool quit = false;

    os_screenmode(0, 27);

    //colourtrans_setgcol(0x00660000, 0, 0); /* Green */
    os_setcolour(0, 2);

    os_set_output_bank(bank);
    os_cls();
    os_set_output_bank(2 - bank);
    os_cls();

    while (!quit)
    {
        for (rotation = 0; rotation < MAX_ROTATION; rotation++)
        {
            uint32_t style = (1<<4) | (1<<5); // interior pixels
            int32_t flatness = 0;
            int32_t *base_matrix = cog_matrixes[MAX_ROTATION - 1 - rotation];
            int32_t matrix[6];

            matrix[0] = base_matrix[0] * 4;
            matrix[1] = base_matrix[1] * 4;
            matrix[2] = base_matrix[2] * 4;
            matrix[3] = base_matrix[3] * 4;
            matrix[4] = base_matrix[4] * 4 + XOFFSET * 0x100;
            matrix[5] = base_matrix[5] * 4 + YOFFSET * 0x100;

            os_set_visible_bank(bank);
            bank = 3 - bank;
            os_set_output_bank(bank);
            os_cls();
            draw_fill(cog_path, style, matrix, flatness);

            /* Exit when 'q' pressed */
            int c = os_inkey(5);
            if ((c | 32) == 'q' || c==-2)
            {
                quit = true;
                break;
            }
        }
    }
    return 1;
}
