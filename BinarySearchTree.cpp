#include <iostream>
#include <stdio.h>

using namespace std;

template <typename T>
struct Node
{
    int key;
    T data;
    Node *left;
    Node *right;
    Node *parent;

    Node(int key, T data)
        : key(key), data(data), left(nullptr), right(nullptr), parent(nullptr)
    {
    }
};

template <typename T>
class BST
{
private:
    static Node<T> *insert_recursive(Node<T> *root, int key, T data);
    static Node<T> *remove_recursive(Node<T> *root, int key);
    Node<T> *search_recursive(Node<T> *root, int key);

public:
    Node<T> *root = nullptr;
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

    static Node<T> *get_min(Node<T> *root)
    {
        if (root == nullptr)
            return nullptr;

        while (root->left != nullptr)
            root = root->left;

        return root;
    }

    static void print_inorder(Node<T> *root)
    {
        if (root == nullptr)
            return;

        print_inorder(root->left);
        printf("%d ", root->key);
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

    ~BST()
    {
        delete_tree(root);
    }
};

template <typename T>
Node<T> *BST<T>::insert_recursive(Node<T> *root, int key, T data)
{
    if (root == nullptr)
        return new Node<T>(key, data);

    else
    {
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
    }

    return root;
}

template <typename T>
Node<T> *BST<T>::remove_recursive(Node<T> *root, int key)
{
    if (root == nullptr)
        return nullptr;

    else if (key < root->key)
        root->left = remove_recursive(root->left, key);

    else if (key > root->key)
        root->right = remove_recursive(root->right, key);

    else // Found
    {
        // Case 1: No children
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            root = nullptr; // Because the pointer still exists
        }

        // Case 2: One child
        else if (root->left == nullptr)
        {
            auto temp = root;
            root = root->right;
            delete temp;
        }

        else if (root->right == nullptr)
        {
            auto temp = root;
            root = root->left;
            delete temp;
        }

        // Case3: Two children
        else
        {
            auto min_right = get_min(root->right);
            root->key = min_right->key;
            root->data = min_right->data;
            root->right = remove_recursive(root->right, min_right->key);
        }
    }

    return root;
}

template <typename T>
Node<T> *BST<T>::search_recursive(Node<T> *root, int key)
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

int main()
{
    BST<int> bst;
    bst.insert(5, 5);
    bst.insert(3, 3);
    bst.insert(7, 7);
    bst.insert(2, 2);
    bst.insert(4, 4);
    bst.insert(6, 6);
    bst.insert(8, 8);

    printf("Inorder: ");
    bst.print_inorder(bst.root);
    printf("\n");

    auto node = bst.search(3);
    if (node != nullptr)
    {
        printf("Found: %d\n", node->data);
    }

    else
    {
        printf("Not found\n");
    }

    // delete
    printf("Deleting 5 and 8\n");
    bst.remove(5);
    bst.remove(8);

    printf("Inorder: ");
    bst.print_inorder(bst.root);
}