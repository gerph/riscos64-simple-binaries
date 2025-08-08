#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char opt;
    if (argc == 1)
    {
        printf("Syntax: %s c|l|n\n", argv[0]);
        printf("Options:\n");
        printf("    c - read a character\n");
        printf("    l - read line (fgets)\n");
        printf("    n - read 8 bytes\n");
        exit(1);
    }

    opt = argv[1][0];
    switch (opt)
    {
        case 'c':
            {
                int c;
                printf("Read character: ");
                c = getchar();
                printf("%i - '%c'\n", c, c);
            }
            break;

        case 'l':
            {
                int c;
                static char buffer[16];
                char *got;
                printf("Read line: ");
                got = fgets(buffer, sizeof(buffer), stdin);
                if (got == NULL)
                {
                    printf("Got nothing\n");
                }
                else
                {
                    printf("Got '%s'\n", got);
                    if (got != buffer)
                    {
                        printf("Returned non-buffer pointer!\n");
                    }
                }
            }
            break;

        case 'n':
            {
                char buffer[16];
                int n;
                printf("Reading 8 bytes: ");
                n = fread(buffer, 1, 8, stdin);
                printf("\nGot %i bytes '%.*s'\n", n, n, buffer);
            }
            break;
    }
    return 0;
}

