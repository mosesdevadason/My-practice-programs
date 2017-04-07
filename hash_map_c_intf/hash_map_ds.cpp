#include <unordered_map>
#include <string>
#include <cstdio>

#include "hash_map_ds.h"

extern "C"
{

handle_t unordered_hash_map_create (void)
{
    std::unordered_map <std::string, int> *umap = 
                                new std::unordered_map <std::string, int> ();

    return (handle_t)umap;
}

void unordered_hash_map_element_insert (const char *key, int value, 
                                        handle_t handle)
{
    std::unordered_map <std::string, int> *umap = 
                                (std::unordered_map <std::string, int> *)handle;
    std::string s(key);

    printf("Key : %s, value : %d\n", s.c_str(), value);

    umap->insert(make_pair(s, value));
}

int unordered_hash_map_element_find (const char *key, handle_t handle)
{
    std::unordered_map <std::string, int> *umap = 
                                (std::unordered_map <std::string, int> *)handle;
    std::string s(key);

    if(umap->find(s) == umap->end())
    {
        return -1;
    }
    
    return (umap->find(s)->second);
}

void unordered_hash_map_element_delete (const char *key, handle_t handle)
{
    std::unordered_map <std::string, int> *umap = 
                                (std::unordered_map <std::string, int> *)handle;
    std::string s(key);

    if(umap->find(s) == umap->cend())
    {
        printf("Element for key %s not present\n", s.c_str());
        return;
    }
    else
    {
        umap->erase(umap->find(s));
    }
}

void unordered_hash_map_dump (handle_t handle)
{
    std::unordered_map <std::string, int> *umap = 
                                (std::unordered_map <std::string, int> *)handle;
    std::unordered_map <std::string, int> :: const_iterator it = umap->cbegin();
    
    printf("******************************************\n");
    printf("            Unordered map dump            \n");
    printf("******************************************\n");
    for(; it != umap->cend(); it++)
    {
        printf("Key : %s, value : %d\n", it->first.c_str(), it->second);
    }
    printf("Map size : %zu\n", umap->size());
    printf("==========================================\n");
}

}/* extern c */
