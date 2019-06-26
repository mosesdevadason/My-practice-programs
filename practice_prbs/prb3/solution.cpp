#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

size_t tree_height(TreeNode *root)
{
    if (nullptr == root) return 0;

    return std::max((1 + tree_height(root->left)),
            (1 + tree_height(root->right)));
}

std::string serialize_level(TreeNode *root, size_t curr_depth, size_t req_depth)
{
    std::string retval = "";

    if (nullptr == root) return "n,";

    if (curr_depth == req_depth) return std::to_string(root->val) + ",";

    if ((curr_depth + 1) <= req_depth) {
        retval = retval +
            serialize_level(root->left, (curr_depth + 1), req_depth);
        retval = retval +
            serialize_level(root->right, (curr_depth + 1), req_depth);
    }

    return retval;
}

std::string serialize_level_order(TreeNode *root)
{
    std::string retval = "";

    if (nullptr == root) return "";

    size_t height = tree_height(root);
    for (size_t ix = 0 ; ix < height ; ++ix) {
        retval = retval + 
            serialize_level(root, 0 /* curr_depth */, ix /* req_depth*/);
    }

    if (',' == retval.at(retval.size() - 1)) retval.erase(retval.size() - 1);
    return retval;
}

std::vector<std::string> split_serialized_string (std::string& serialized_str)
{
    std::vector<std::string> result;
    std::string local_serialized_str = {serialized_str}, delimiter = ",";

    size_t pos = 0;
    std::string token;
    while ((pos = local_serialized_str.find(delimiter)) != std::string::npos) {
        token = local_serialized_str.substr(0, pos);
        result.push_back(token);
        local_serialized_str.erase(0, pos + delimiter.length());
    }
    // Add the final token
    result.push_back(local_serialized_str);

    return result;
}

// Requires first node alone to be created.
void insert_nodes_from_serialized_list(
        TreeNode *root,
        std::vector<std::string>& nodes,
        std::vector<std::string>::iterator start_it,
        std::vector<std::string>::iterator end_it)
{
    auto it = std::find(start_it, end_it, std::to_string(root->val));
    size_t i = it - nodes.begin();

    if ((((2 * i) + 1) >= nodes.size()) || (((2 * i) + 2) >= nodes.size())) {
        return;
    }

    size_t lpos = (2 * i) + 1;
    size_t rpos = (2 * i) + 2;
    std::string lchild = nodes[lpos];
    std::string rchild = nodes[rpos];

    if (lchild != "n") {
        root->left = new TreeNode(std::stoi(lchild));
        TreeNode *node = root->left;
        insert_nodes_from_serialized_list(node, nodes, nodes.begin() + lpos,
                nodes.end());
    }
    if (rchild != "n") {
        root->right = new TreeNode(std::stoi(rchild));
        TreeNode *node = root->right;
        insert_nodes_from_serialized_list(node, nodes, nodes.begin() + rpos,
                nodes.end());
    }
}

TreeNode * deserialize_level_order(std::string serialized_string)
{
    TreeNode *root = nullptr;

    if (serialized_string.length() == 0) return nullptr;

    std::vector<std::string> nodes = split_serialized_string(serialized_string);
    if (nodes.size() == 0) return nullptr;

    // Create first node alone.
    root = new TreeNode(std::stoi(nodes[0]));
    insert_nodes_from_serialized_list(root, nodes, nodes.begin(), nodes.end());

    return root;
}

void print_inorder(TreeNode *root)
{
    if (nullptr == root) return;

    print_inorder(root->left);
    std::printf("INORDER NODE DATA : %d\n", root->val);
    print_inorder(root->right);
}

int main(int argc, char *argv[])
{
    // [1,2,3,1,3,2,4] - PASS
    // [5,2,3,null,null,2,4,3,1] - FAIL
    TreeNode *n1 = new TreeNode(1);

    TreeNode *n2 = n1->left = new TreeNode(2);
    TreeNode *n3 = n1->right = new TreeNode(3);

    TreeNode *n4 = n2->left = new TreeNode(1);
    TreeNode *n5 = n2->right = new TreeNode(3);

    TreeNode *n6 = n3->left = new TreeNode(2);
    TreeNode *n7 = n3->right = new  TreeNode(4);

    std::printf("Height of the tree : %lu\n", tree_height(n1));
    std::string serialized_string = serialize_level_order(n1);
    std::printf("Level order serialized tree : %s\n",
            serialized_string.c_str());
    TreeNode *result = deserialize_level_order(serialized_string);
    print_inorder(result);

    return 0;
}
