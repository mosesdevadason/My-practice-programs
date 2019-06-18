#include <cstdio>
#include <string>

typedef struct _tree_node_t
{
    int data;
    _tree_node_t *left;
    _tree_node_t *right;
}tree_node_t;

size_t tree_height(tree_node_t *root)
{
    if (nullptr == root) return 0;

    return std::max((1 + tree_height(root->left)),
            (1 + tree_height(root->right)));
}

void print_level(tree_node_t *root, size_t curr_depth, size_t req_depth)
{
    if (nullptr == root) return;

    if (curr_depth == req_depth) std::printf("Depth %lu | Node %d\n", curr_depth,
            root->data);

    print_level(root->left, (curr_depth + 1), req_depth);
    print_level(root->right, (curr_depth + 1), req_depth);
}

void print_level_order(tree_node_t *root)
{
    if (nullptr == root) return;

    size_t height = tree_height(root);
    for (size_t ix = 0 ; ix < height ; ++ix) {
        print_level(root, 0 /* curr_depth */, ix /* req_depth*/);
    }
}

std::string serialize_level_wise(tree_node_t *root)
{
    std::string retval = "";
    if (nullptr == root) {
        return "null,";
    }
    retval = std::to_string(root->data) + ",";
    std::printf("%s\n", retval.c_str());
    retval = retval + serialize_level_wise(root->left);
    retval = retval + serialize_level_wise(root->right);

    return retval;
}

int main(int argc, char *argv[])
{
    tree_node_t *n1 = new tree_node_t;
    n1->data = 10;
    n1->left = new tree_node_t;
    tree_node_t *n2 = n1->left;
    n2->data = 20;
    n1->right = new tree_node_t;
    tree_node_t *n3 = n1->right;
    n3->data = 30;

    std::printf("Height of the tree : %lu\n", tree_height(n1));
    print_level_order(n1);
    std::printf("Serialized string : %s\n", serialize_level_wise(n1).c_str());
    return 0;
}
