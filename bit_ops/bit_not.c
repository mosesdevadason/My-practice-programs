#include <stdio.h>

int main(int argc, char *argv[])
{
    int a = 0x00000002;
    int b = 0x00000003;

    printf("Not of a : 0x%08x\n", ((~a) & b));
    
    return 0;
}
