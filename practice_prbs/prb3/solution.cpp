#include <cstdio>
#include <string>
#include <vector>
#include <queue>

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

TreeNode * deserialize_level_order(std::string serialized_string)
{
    if (serialized_string.length() == 0) return nullptr;

    std::vector<std::string> items;
    items = split_serialized_string(serialized_string);

    /* 1. Insert first node.
     * 2. Push node into Queue
     * 3. For every item in front of the queue,
     *     4. Left = 2*i + 1 and Right = 2*i + 2.
     *     6. If left or right position is out of bounds insert whatever is
     *        inside bounds alone.
     *     5. Push the left and right (whatever is in-bounds) children into the
     *        queue.
     *     6. Delete the processed node (in front) from the queue.
     *     7. Repeat from step 4 for item in front of queue until queue is
     *        empty.
     */
    std::queue<std::string> q;
    
    return nullptr;
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
