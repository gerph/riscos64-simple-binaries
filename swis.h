#include <stdint.h>

void os_writec(char c);
char os_readc(void);
void os_screenmode(int reason, uint32_t modespec);
void colourtrans_setgcol(uint32_t palentry, uint32_t flags, uint32_t gcol);
void draw_fill(int32_t *path, uint32_t style, int32_t *matrix, int32_t flatness);
void os_setcolour(uint32_t flags, uint32_t gcol);
int os_inkey(int32_t value);
void os_write0(const char *str);
void os_newline(void);
