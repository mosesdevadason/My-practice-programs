#include <cstdio>

struct tree_node_t
{
    tree_node_t *left = nullptr;
    tree_node_t *right = nullptr;
    int val = 0;

    tree_node_t(int val)
    {
        this->val = val;
    }
};

int count_unival_subtrees(tree_node_t *root)
{
    if (nullptr == root) return 0;
    
    // If leaf node.
    if ((nullptr == root->left) && (nullptr == root->right)) return 1;

    int cnt = 0;
    if (nullptr != root->left)
        cnt = cnt +  count_unival_subtrees(root->left);
    if (nullptr != root->right)
        cnt = cnt + count_unival_subtrees(root->right);

    // If current root only has left child.
    if ((nullptr != root->left) && (nullptr == root->right) &&
            (root->val == root->left->val)) return cnt + 1;
    // If current root only has right child.
    else if ((nullptr != root->right) && (nullptr == root->left) &&
            (root->val == root->right->val)) return cnt + 1;
    
    // Current root has both left and right children.
    else if ((root->val == root->left->val) && (root->val == root->right->val))
        return cnt + 1;

    return cnt;
}

int main(int argc, char *argv[])
{
    tree_node_t *n1 = new tree_node_t(0);
    tree_node_t *n2 = n1->left = new tree_node_t(1);
    tree_node_t *n3 = n1->right = new tree_node_t(0);
    tree_node_t *n4 = n3->left = new tree_node_t(1);
    tree_node_t *n5 = n3->right = new tree_node_t(0);
    tree_node_t *n6 = n4->left = new tree_node_t(1);
    tree_node_t *n7 = n4->right = new tree_node_t(1);

    std::printf("Number of unival subtrees : %d\n", count_unival_subtrees(n1));

    tree_node_t *t1 = new tree_node_t(5);
    tree_node_t *t2 = t1->left = new tree_node_t(1);
    tree_node_t *t3 = t1->right = new tree_node_t(5);
    tree_node_t *t4 = t2->left = new tree_node_t(5);
    tree_node_t *t5 = t2->right = new tree_node_t(5);
    tree_node_t *t6 = t3->left = new tree_node_t(5);

    std::printf("Number of unival subtrees : %d\n", count_unival_subtrees(t1));

    return 0;
}
