#include <stdint.h>
#include "start.h"

#include "cogdata.inc"

#include "swis.h"

#define MAX_ROTATION (sizeof(paths) / sizeof(paths[0]))

#define XOFFSET (640)
#define YOFFSET (480)


int start(const char *cli, uint64_t ramlimt, uint8_t *starttime_quin)
{
    int rotation;

    os_screenmode(0, 27);

    //colourtrans_setgcol(0x00660000, 0, 0); /* Green */
    os_setcolour(0, 2);

    for (rotation = 0; rotation < MAX_ROTATION; rotation++)
    {
        uint32_t style = (1<<4) | (1<<5); // interior pixels
        int32_t flatness = 0;
        int32_t *path = paths[rotation];
        int32_t *base_matrix = matrixes[rotation];
        int32_t matrix[6];

        matrix[0] = base_matrix[0] * 4;
        matrix[1] = base_matrix[1] * 4;
        matrix[2] = base_matrix[2] * 4;
        matrix[3] = base_matrix[3] * 4;
        matrix[4] = base_matrix[4] * 4 + XOFFSET * 0x100;
        matrix[5] = base_matrix[5] * 4 + YOFFSET * 0x100;

        draw_fill(path, style, matrix, flatness);
        //os_write0("Rotate");
        //os_newline();
        //os_inkey(25);
    }
    //os_readc();
    return 1;
}
