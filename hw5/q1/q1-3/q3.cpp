#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

int get_rand(int maxN)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL));
        first = false;
    }
    return rand() % maxN;
}

struct node
{
    int pri;
    char c;
    node *lc, *rc;
    int size;

    node(char c) : pri(get_rand(10000000)), c(c), lc(nullptr), rc(nullptr), size(1) {}
};

// 更新節點大小
void update_size(node *root)
{
    if (root)
        root->size = 1 + (root->lc ? root->lc->size : 0) + (root->rc ? root->rc->size : 0);
}

// 分裂函數
pair<node *, node *> split(node *root, int k)
{
    if (!root)
        return make_pair(nullptr, nullptr);

    int leftSize = root->lc ? root->lc->size : 0;

    if (leftSize < k)
    {
        pair<node *, node *> right_subtree_split = split(root->rc, k - leftSize - 1);
        root->rc = right_subtree_split.first;
        update_size(root);
        return make_pair(root, right_subtree_split.second);
    }
    else
    {
        pair<node *, node *> left_subtree_split = split(root->lc, k);
        root->lc = left_subtree_split.second;
        update_size(root);
        return make_pair(left_subtree_split.first, root);
    }
}

// 合併函數
node *merge(node *left, node *right)
{
    if (!left)
        return right;
    if (!right)
        return left;

    if (left->pri > right->pri)
    {
        left->rc = merge(left->rc, right);
        update_size(left);
        return left;
    }
    else
    {
        right->lc = merge(left, right->lc);
        update_size(right);
        return right;
    }
}

// 輸出 Treap
void printTree(node *root)
{
    if (!root)
        return;
    printTree(root->lc);
    cout << root->c;
    printTree(root->rc);
}

int main()
{
    int n, m;
    cin >> n >> m;
    string chars;
    cin >> chars;
    node *root = new node(chars[0]);
    for (int i = 1; i < n; i++)
    {
        node *newNode = new node(chars[i]);
        root = merge(root, newNode);
    }

    int left, right;
    while (m--)
    {
        cin >> left >> right;
        pair<node *, node *> first_cut = split(root, left - 1);
        pair<node *, node *> second_cut = split(first_cut.second, right - left + 1);
        root = merge(first_cut.first, second_cut.second);
        root = merge(root, second_cut.first);
    }

    printTree(root);
    cout << endl;
}
