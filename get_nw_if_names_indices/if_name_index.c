#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct if_nameindex *if_ni, *ptr;
    int count = 0;

    if_ni = if_nameindex();
    if (NULL == if_ni) {
        perror("if_nameindex");
        exit(EXIT_FAILURE);
    }

    for (ptr = if_ni; !((0 == ptr->if_index) && (NULL == ptr->if_name));
            ptr++) {
        count++;
        printf("Device number %d:\n", count);
        printf("if_name : %s, if_index : %u\n", ptr->if_name, ptr->if_index);
    }

    if_freenameindex(if_ni);

    exit(EXIT_SUCCESS);
}
