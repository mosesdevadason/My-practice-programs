#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    FILE *out = stdout;
    FILE *dev = NULL;
    
    fprintf(out, "Before opening /dev/null\n");

    dev = fopen("/dev/null", "w");
    if(NULL == dev)
    {
        printf("Opening /dev/null failed\n");
        return EXIT_FAILURE;
    }
    
    fprintf(out, "Before assigning dev to out\n");
    out = dev;
    fprintf(out, "After assigning dev to out\n");
    out = stdout;
    fprintf(out, "After assgining back stdout\n");
    
    fclose(dev);

    return EXIT_SUCCESS;
}
