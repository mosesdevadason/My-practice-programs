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

std::string serialize_level(tree_node_t *root, size_t curr_depth, size_t req_depth)
{
    std::string retval = "";

    if (nullptr == root) return "null,";

    if (curr_depth == req_depth) return std::to_string(root->data) + ",";

    retval = retval +
        serialize_level(root->left, (curr_depth + 1), req_depth);
    retval = retval +
        serialize_level(root->right, (curr_depth + 1), req_depth);

    return retval;
}

std::string serialize_level_order(tree_node_t *root)
{
    std::string retval = "";

    if (nullptr == root) return "null";

    size_t height = tree_height(root);
    for (size_t ix = 0 ; ix < height ; ++ix) {
        retval = retval + 
            serialize_level(root, 0 /* curr_depth */, ix /* req_depth*/);
    }

    if (',' == retval.at(retval.size() - 1)) retval.erase(retval.size() - 1);
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
    tree_node_t *n4 = new tree_node_t;
    n4->data = 40;
    n3->left = n4;

    std::printf("Height of the tree : %lu\n", tree_height(n1));
    std::printf("Level order serialized tree : %s\n",
            serialize_level_order(n1).c_str());

    return 0;
}
