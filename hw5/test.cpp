#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <time.h>
#include <vector>
#include <map>
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
    node *lc, *rc, *p;
    int l_sz, r_sz;
    node(char c) : pri(get_rand(10000000)), c(c), lc(nullptr), rc(nullptr), p(nullptr), l_sz(0), r_sz(0) {}
};
node *rotate_dir(node *r, bool dir)
{
    if (dir)
    { // right rotation
        node *leftNode = r->lc;
        r->lc = leftNode->rc;
        if (leftNode->rc)
            leftNode->rc->p = r;

        leftNode->p = r->p;
        if (r->p)
        {
            if (r->p->lc == r)
                r->p->lc = leftNode;
            else
                r->p->rc = leftNode;
        }

        leftNode->rc = r;
        r->p = leftNode;

        // update size
        return leftNode;
    }
    else
    { // left rotation
        node *rightNode = r->rc;
        r->rc = rightNode->lc;
        if (rightNode->lc)
            rightNode->lc->p = r;

        rightNode->p = r->p;
        if (r->p)
        {
            if (r->p->lc == r)
                r->p->lc = rightNode;
            else
                r->p->rc = rightNode;
        }

        rightNode->lc = r;
        r->p = rightNode;

        return rightNode;
    }
}

int get_size(node *root)
{
    if (root == nullptr)
        return 0;
    root->l_sz = get_size(root->lc);
    root->r_sz = get_size(root->rc);
    return root->l_sz + root->r_sz + 1;
}

void update_size(node *node)
{
    if (node == nullptr)
        return;
    node->l_sz = get_size(node->lc);
    node->r_sz = get_size(node->rc);
}

// pair<node *, node *> split(node *root, int k)
// {
//     if (root == nullptr)
//         return {nullptr, nullptr};

//     if (root->l_sz + 1 == k)
//     {
//         node *left = root->lc;
//         node *right = root;
//         if (left != nullptr)
//         {
//             left->p = nullptr;
//             update_size(left);
//         }
//         return {left, right};
//     }
//     else if (root->l_sz + 1 < k)
//     {
//         // 根節點和左子樹的節點總數小於等於 k，因此根節點應該屬於左子樹
//         pair<node *, node *> right_subtree_split = split(root->rc, k - root->l_sz - 1);
//         root->rc = right_subtree_split.first;
//         if (right_subtree_split.first != nullptr)
//             right_subtree_split.first->p = root;
//         update_size(root);
//         if (right_subtree_split.second != nullptr)
//         {
//             right_subtree_split.second->p = nullptr;
//             update_size(right_subtree_split.second);
//         }
//         return {root, right_subtree_split.second};
//     }
//     else
//     {
//         // 根節點和左子樹的節點總數大於 k，因此根節點應該屬於右子樹
//         pair<node *, node *> left_subtree_split = split(root->lc, k);
//         root->lc = left_subtree_split.second;
//         if (left_subtree_split.second != nullptr)
//             left_subtree_split.second->p = root;
//         update_size(root);
//         if (left_subtree_split.first != nullptr)
//         {
//             left_subtree_split.first->p = nullptr;
//             update_size(left_subtree_split.first);
//         }
//         return {left_subtree_split.first, root};
//     }
// }

// node *merge(node *left, node *right)
// {
//     if (!left)
//         return right;
//     if (!right)
//         return left;
//     if (left->pri > right->pri)
//     {
//         left->rc = merge(left->rc, right);
//         left->rc->p = left;
//         return left;
//     }
//     else
//     {
//         right->lc = merge(left, right->lc);
//         right->lc->p = right;
//         return right;
//     }
// }
pair<node *, node *> split(node *root, int k)
{
    if (!root)
        return make_pair(nullptr, nullptr);

    int leftSize = get_size(root->lc);

    if (leftSize + 1 <= k) // k在右子樹
    {
        pair<node *, node *> right_subtree_split = split(root->rc, k - leftSize - 1);
        root->rc = right_subtree_split.first;
        update_size(root);
        return make_pair(root, right_subtree_split.second);
    }
    else // k在左子樹
    {
        pair<node *, node *> left_subtree_split = split(root->lc, k);
        root->lc = left_subtree_split.second;
        update_size(root);
        return make_pair(left_subtree_split.first, root);
    }
}

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

void printTree(node *root)
{
    // // print each node and show its parent and direction in each line
    // // turn val into priority
    // if (root == nullptr)
    //     return;
    // cout << root->c << "(" << root->pri << ") ";
    // if (root->p != nullptr)
    //     cout << "p: " << root->p->c << "(" << root->p->pri << ")";
    // if (root->lc != nullptr)
    //     cout << "l: " << root->lc->c << "(" << root->lc->pri << ")";
    // if (root->rc != nullptr)
    //     cout << "r: " << root->rc->c << "(" << root->rc->pri << ")";
    // cout << "---------------------------------" << endl;
    // cout << "l_sz: " << root->l_sz << " r_sz: " << root->r_sz << endl;
    // printTree(root->lc);
    // printTree(root->rc);
    if (root == nullptr)
        return;
    printTree(root->lc);
    cout << root->c;
    printTree(root->rc);
}

int main()
{
    // turn char into this string AYBABTU
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
    while (root->p != nullptr)
        root = root->p;
    node *cur = root;
    update_size(cur);
    // printTree(cur);
    while (m--)
    {
        cin >> left >> right;
        pair<node *, node *> first_cut = split(root, left - 1);
        pair<node *, node *> second_cut = split(first_cut.second, right - left + 1);
        root = merge(first_cut.first, second_cut.second);
        root = merge(root, second_cut.first);
        // while (root->p != nullptr)
        //     root = root->p;
        // update_size(root);
        // printTree(root);
        // cout << endl;
    } // print tree
    printTree(root);
    // how to maintain root as the real root?
}