#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *f;
    if (argc == 1)
    {
        printf("Syntax: %s <file-to-read>\n", argv[0]);
        exit(1);
    }
    f = fopen(argv[1], "r");
    if (!f)
    {
        printf("Cannot read file\n");
        exit(1);
    }
    char buffer[256];
    while (!feof(f))
    {
        size_t read = fread(buffer, 1, sizeof(buffer), f);
        fwrite(buffer, 1, read, stdout);
    }
    fclose(f);
    return 0;
}

