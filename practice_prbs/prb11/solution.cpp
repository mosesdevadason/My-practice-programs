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

void trie_insert_word(trie_node_t *root, std::string& s)
{
    tree_node_t *p = root;

    for (size_t ix = 0 ; ix < s.size() ; ++ix) {
        auto it = p->ptrs.find(s[ix]);
        if (it == p->ptrs.end()) { // Char not present in pointer set.
            // Create new node and traverse to it. Move on with next char.
            tree_node_t *n = new tree_node_t(s[ix]);
            root->ptrs.emplace(s[ix], n);
            p = n;
        } else { // Char present in pointer set.
            // Traverse to next node and move on to next char.
            p = it->second;
        }
    }
}

std::vector<std::string> get_suggestions(trie_node_t *root, std::string& s)
{
    tree_node_t *p = root;
    std::vector suggestions;

    for (size_t ix = 0; ix < s.size() ; ++ix) {
        auto it = p->ptrs.find(s[ix]);
        if (it == p->ptrs.end()) return suggestions;
        else p = it->second;
    }

    // Completed walking the prefix. Every possibility from here must be added
    // to suggestions list.
}

trie_node_t * trie_construct(std::vector<std::string>& dict)
{
    trie_node_t *root = new trie_node_t('\0');

    for (auto it = dict.begin ; it->dict.end() ; ++it) {
        trie_insert_word(root, *it);
    }

    return root;
}

int main(int argc, char *argv[])
{
    return 0;
}
