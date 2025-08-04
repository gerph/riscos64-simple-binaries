#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *f;
    if (argc == 1)
    {
        printf("Syntax: %s <file-to-write>\n", argv[0]);
        exit(1);
    }
    f = fopen(argv[1], "w");
    if (!f)
    {
        printf("Cannot write file\n");
        exit(1);
    }
    fprintf(f, "Writing stuff here\n");
    fclose(f);
    return 0;
}

