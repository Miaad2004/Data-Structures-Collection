#include <iostream>

using namespace std;

template <class T>
class Node
{
public:
    T data;
    int key;
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    Node<T> *parent = nullptr;
    int height;

    Node(int key, T data)
    {
        this->data = data;
        this->key = key;
        this->height = 1;
    }
};

template <class T>
class AVL
{
private:
    static Node<T> *insert_recursive(Node<T> *root, int key, T data);
    static Node<T> *remove_recursive(Node<T> *root, int key);
    static Node<T> *search_recursive(Node<T> *root, int key);
    static Node<T> *right_rotate(Node<T> *node);
    static Node<T> *left_rotate(Node<T> *node);

public:
    Node<T> *root = nullptr;

    static int height(Node<T> *root)
    {
        if (root == nullptr)
            return 0;

        return root->height;
    }

    template <class T>
    Node<T> *AVL<T>::left_rotate(Node<T> *x)
    {
        auto y = x->right;
        auto t2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = t2;

        // Update heights
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    template <class T>
    Node<T> *AVL<T>::right_rotate(Node<T> *y)
    {
        auto x = y->left;
        auto t2 = x->right;

        // Perform rotation
        x.right = y;
        y.left = t2;

        // Update heights
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    static int get_balance(Node<T> *root)
    {
        if (root == nullptr)
            return 0;

        return height(root->left) - height(root->right);
    }

    void insert(int key, T data)
    {
        this->root = insert_recursive(this->root, key, data);
    }

    Node<T> *remove(int key)
    {
        this->root = remove_recursive(this->root, key);
        return root;
    }

    Node<T> *search(int key)
    {
        return search_recursive(this->root, key);
    }

    static void print_inorder(Node<T> *root)
    {
        if (root == nullptr)
            return;

        print_inorder(root->left);
        cout << root->data << " ";
        print_inorder(root->right);
    }

    void delete_tree(Node<T> *root)
    {
        if (root == nullptr)
            return;

        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }

    ~AVL()
    {
        delete_tree(this->root);
    }
};

template <class T>
Node<T> *AVL<T>::search_recursive(Node<T> *root, int key)
{
    if (root == nullptr)
        return nullptr;

    if (root->key == key)
        return root;

    else if (key < root->key)
        return search_recursive(root->left, key);

    else
        return search_recursive(root->right, key);
}

template <class T>
Node<T> *AVL<T>::insert_recursive(Node<T> *root, int key, T data)
{
    if (root == nullptr)
        return new Node<T>(key, data);

    // Usual BST insertion
    if (root->key == key)
    {
        root->data = data;
        return root;
    }

    else if (key < root->key)
    {
        root->left = insert_recursive(root->left, key, data);
        root->left->parent = root;
    }

    else
    {
        root->right = insert_recursive(root->right, key, data);
        root->right->parent = root;
    }

    // Update the height
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor
    int balance = get_balance(root);

    // Balance the tree

    // Case 1: left heavy
    if (balance > 1)
    {
        if (key < root->left)
            return right_rotate(root);

        else
        {
            // convert to the top case
            root->left = left_rotate(root->left);
            return right_rotate(root);
        }
    }

    // Case 2: right heavy
    else if (balance < -1)
    {
        if (key > root->right->key)
            return left_rotate(root);

        else
        {
            // convert to the top case
            root->right = right_rotate(root->right);
            return left_rotate(root);
        }
    }

    return root;
}

int main()
{
}