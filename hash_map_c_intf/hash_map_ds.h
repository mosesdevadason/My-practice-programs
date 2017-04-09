#ifndef _HASH_MAP_DS_H
#define _HASH_MAP_DS_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Pointer to the hash map. Will be used for all operations after creating it */
typedef void * handle_t;

/* Creates the hash map and returns the handle to be used for future operations 
 */
handle_t unordered_hash_map_create(void);

/* Inserts element ir. key, value pair into the hash map */
void unordered_hash_map_element_insert(const char *key, int value, 
                                       handle_t handle);

/* Finds the value corresponding to the input key */
int unordered_hash_map_element_find(const char *key, handle_t handle);

/* Deletes the element corresponding to the input key */
void unordered_hash_map_element_delete(const char *key, handle_t handle);

/* Dumps the entire hash map */
void unordered_hash_map_dump(handle_t handle);

#ifdef __cplusplus
}
#endif

#endif
