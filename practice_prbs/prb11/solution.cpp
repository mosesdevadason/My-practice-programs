#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>

struct trie_node_t
{
    char c = '\0';
    bool end_of_word = false;
    std::unordered_map<char, trie_node_t *> ptrs;

    trie_node_t(char x)
    {
        this->c = x;
    }
};

void get_suggestions__(trie_node_t *root, std::string& s,
        std::vector<std::string>& suggestions)
{
    std::string ws = s; // working string.

    if (root->end_of_word) suggestions.push_back(s);

    if (root->ptrs.empty()) return;

    for (auto it = root->ptrs.begin() ; it != root->ptrs.end() ; ++it) {
        ws = ws + it->second->c;
        std::printf("s = %s\n", s.c_str());
        get_suggestions__(it->second, ws, suggestions);
        ws = s;
    }
}

std::vector<std::string> get_suggestions(trie_node_t *root, std::string& s)
{
    trie_node_t *p = root;
    std::vector<std::string> suggestions;

    for (size_t ix = 0; ix < s.size() ; ++ix) {
        auto it = p->ptrs.find(s[ix]);
        if (it == p->ptrs.end()) return suggestions;
        else p = it->second;
    }

    // Completed walking the prefix. Every possibility from here must be added
    // to suggestions list.
    get_suggestions__(p, s, suggestions);
    
    return suggestions;
}

void trie_insert_word(trie_node_t *root, std::string& s)
{
    trie_node_t *p = root;

    for (size_t ix = 0 ; ix < s.size() ; ++ix) {
        auto it = p->ptrs.find(s[ix]);
        if (it == p->ptrs.end()) { // Char not present in pointer set.
            // Create new node and traverse to it. Move on with next char.
            trie_node_t *n = new trie_node_t(s[ix]);
            p->ptrs.emplace(s[ix], n);
            p = n;
        } else { // Char present in pointer set.
            // Traverse to next node and move on to next char.
            p = it->second;
        }
    }
    // Mark the last node as end of word.
    p->end_of_word = true;
}


trie_node_t * trie_construct(std::vector<std::string>& dict)
{
    trie_node_t *root = new trie_node_t('\0');

    for (auto it = dict.begin() ; it != dict.end() ; ++it)
        trie_insert_word(root, *it);

    return root;
}

std::vector<std::string> get_suggestions_for_dict_and_query(
        std::vector<std::string>& dict, std::string& query
        )
{
    trie_node_t *root = trie_construct(dict);

    return get_suggestions(root, query);
}

int main(int argc, char *argv[])
{
    std::vector<std::string> dict = {"dog", "deal", "deer", "doom", "dome",
        "domain", "door", "dong"};
    std::string query = "doo";

    std::vector<std::string> suggestions =
        get_suggestions_for_dict_and_query(dict, query);

    std::printf("Suggestions:\n");
    for (auto it = suggestions.begin() ; it != suggestions.end() ; ++it)
        std::printf("%s\n", it->c_str());

    return 0;
}
