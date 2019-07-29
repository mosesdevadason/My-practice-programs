#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>

struct trie_node_t
{
    char c = '\0';
    std::unordered_map<char, trie_node_t *> ptrs;

    trie_node_t(char x)
    {
        this->c = x;
    }
};

trie_node_t * make_trie(std::vector<std::string>& dict)
{
    for (auto it = dict.begin ; it->dict.end() ; ++it) {

    }
}

int main(int argc, char *argv[])
{
    return 0;
}
