#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node *left;
    Node *right;

    Node(int val)
    {
        value = val;
        left = right = nullptr;
    }
};

class BST
{
private:
    Node *root;

    Node *insertRecursive(Node *node, int value)
    {
        if (node == nullptr)
        {
            return new Node(value);
        }

        if (value < node->value)
        {
            node->left = insertRecursive(node->left, value);
        }
        else
        {
            node->right = insertRecursive(node->right, value);
        }

        return node;
    }

    void inOrderRecursive(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        inOrderRecursive(node->left);
        cout << node->value << " ";
        inOrderRecursive(node->right);
    }

public:
    BST()
    {
        root = nullptr;
    }

    void insert(int value)
    {
        root = insertRecursive(root, value);
    }

    void printInOrder()
    {
        inOrderRecursive(root);
        cout << endl;
    }
};

int main()
{
    int n;
    cin >> n; // input size of tree

    BST tree;
    for (int i = 0; i < n; i++)
    {
        int value;
        cin >> value;
        tree.insert(value);
    }
    // Print the tree in-order
    tree.printInOrder();
    return 0;
}