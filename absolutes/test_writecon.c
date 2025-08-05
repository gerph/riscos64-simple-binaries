#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char opt;
    if (argc == 1)
    {
        printf("Syntax: %s c|l|n\n", argv[0]);
        printf("Options:\n");
        printf("    c - write a character (putchar)\n");
        printf("    l - write a line (fwrite)\n");
        printf("    s - write a line (fputs)\n");
        exit(1);
    }

    opt = argv[1][0];
    switch (opt)
    {
        case 'c':
            {
                int c;
                printf("Write character (A, \\n, B): ");
                putchar(65);
                putchar(10);
                putchar(66);
            }
            break;

        case 'l':
            {
                static char buffer[] = "A\nB";
                int wrote;
                printf("Write line (A, \\n, B): ");
                wrote = fwrite(buffer, 1, 3, stdout);
                printf("\n");
                printf("Wrote %i bytes\n", wrote);
            }
            break;

        case 's':
            {
                static char buffer[] = "A\nB";
                int wrote;
                printf("Write line (A, \\n, B): ");
                wrote = puts(buffer);
                printf("\n");
                printf("Wrote %i bytes\n", wrote);
            }
            break;
    }
    return 0;
}

