#include "hash_map_ds.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    handle_t umap = NULL;

    umap = unordered_hash_map_create();
    if (NULL == umap) {
        printf("Unordered hash map creation failed\n");
        return EXIT_FAILURE;
    }

    unordered_hash_map_element_insert("Moses", 1000, umap);
    unordered_hash_map_element_insert("Raj", 1001, umap);
    unordered_hash_map_element_insert("Nirmal", 1002, umap);

    unordered_hash_map_dump(umap);

    unordered_hash_map_element_insert("Safia", 1003, umap);

    unordered_hash_map_dump(umap);

    int id = unordered_hash_map_element_find("Raj", umap);
    if (-1 == id) {
        printf("Raj not found in hash map\n");
    } else {
        printf("Raj's ID : %d\n", id);
    }

    unordered_hash_map_element_delete("Nirmal", umap);

    unordered_hash_map_dump(umap);

    return EXIT_SUCCESS;
}
