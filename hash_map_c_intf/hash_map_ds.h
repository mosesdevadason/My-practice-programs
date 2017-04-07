#ifndef _HASH_MAP_DS_H
#define _HASH_MAP_DS_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef void * handle_t;

handle_t unordered_hash_map_create(void);

void unordered_hash_map_element_insert(const char *key, int value, 
                                       handle_t handle);

int unordered_hash_map_element_find(const char *key, handle_t handle);

void unordered_hash_map_element_delete(const char *key, handle_t handle);

void unordered_hash_map_dump(handle_t handle);

#ifdef __cplusplus
}
#endif

#endif
