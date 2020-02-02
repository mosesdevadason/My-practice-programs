#include <cstdio>
#include <string>
#include <queue>
#include <sstream>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr)
    {
    }
};

std::string serialize_level_order(TreeNode *root)
{
    if (nullptr == root) {
        return "";
    }

    std::string ser_str = "";
    std::queue<TreeNode*> q;

    q.push(root);
    while (!q.empty()) {
        if (nullptr == q.front()) {
            /* using ser_str = ser_str + "n " causes memory exceeded error in
             * leetcode */
            ser_str += "n ";
        } else {
            ser_str += std::to_string(q.front()->val) + " ";
            q.push(q.front()->left);
            q.push(q.front()->right);
        }
        q.pop();
    }

    // Remove trailing whitespace
    while (ser_str[ser_str.length() - 1] == ' ') {
        ser_str.erase(ser_str.length() - 1);
    }

    return ser_str;
}

TreeNode* deserialize_level_order(std::string &serialized_str)
{
    if (0 == serialized_str.length()) {
        return nullptr;
    }

    std::istringstream ser_stream(serialized_str);
    std::string token = "";

    ser_stream >> token;
    TreeNode *root = new TreeNode(std::stoi(token));
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        // Left child.
        ser_stream >> token;
        if (token != "n") {
            q.front()->left = new TreeNode(std::stoi(token));
            q.push(q.front()->left);
        }
        // Right child.
        ser_stream >> token;
        if (token != "n") {
            q.front()->right = new TreeNode(std::stoi(token));
            q.push(q.front()->right);
        }
        q.pop();
    }

    return root;
}

void print_inorder(TreeNode *root)
{
    if (nullptr == root)
        return;

    print_inorder(root->left);
    std::printf("INORDER NODE DATA : %d\n", root->val);
    print_inorder(root->right);
}

int main(int argc, char *argv[])
{
    // [5,2,3,null,null,2,4,3,1]
    TreeNode *n1 = new TreeNode(5);

    TreeNode *n2 = n1->left = new TreeNode(2);
    TreeNode *n3 = n1->right = new TreeNode(3);
    TreeNode *n4 = n3->left = new TreeNode(2);
    TreeNode *n5 = n3->right = new TreeNode(4);
    TreeNode *n6 = n4->left = new TreeNode(3);
    TreeNode *n7 = n4->right = new TreeNode(1);

    std::string serialized_str = serialize_level_order(n1);
    std::printf("Level order serialized tree : %s\n", serialized_str.c_str());
    TreeNode *root = deserialize_level_order(serialized_str);
    print_inorder(root);

    return 0;
}
