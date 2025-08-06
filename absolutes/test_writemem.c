#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char opt;
    if (argc == 1)
    {
        printf("Syntax: %s c|l|n\n", argv[0]);
        printf("Options:\n");
        printf("    c - write a character (fputc)\n");
        printf("    l - write a line (fwrite)\n");
        printf("    h - write a huge amount (fwrite)\n");
        exit(1);
    }

    char *str = (char *)0x88990088; /* will crash if not updated */
    size_t size = -1;

    FILE *fh = open_memstream(&str, &size);
    if (!fh)
    {
        printf("Could not open memstream\n");
        exit(1);
    }

    opt = argv[1][0];
    switch (opt)
    {
        case 'c':
            {
                printf("Write character (A, \\n, B): ");
                fputc(65, fh);
                fputc(10, fh);
                fputc(66, fh);
            }
            break;

        case 'l':
            {
                static char buffer[] = "A\nB";
                int wrote;
                printf("Write line (A, \\n, B): ");
                wrote = fwrite(buffer, 1, 3, fh);
                printf("\n");
                printf("Wrote %i bytes\n", wrote);
            }
            break;

        case 'h':
            {
                int i;
                for (i=0; i<200; i++)
                {
                    const char *str = "this is a test line to fill the buffer\n";
                    fwrite(str, 1, strlen(str), fh);
                }
            }
            break;
    }

    fclose(fh);

    printf("Memstream: at %p size %zi\n", str, size);
    printf("String: %s\n", str);

    return 0;
}

