/// @author Benjamin Alcocer
/// github: https://github.com/benalcocer

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>

template <class Type>
struct Node
{
    Type item;
    Node * left;
    Node * right;
};

template <class Type>
class BinarySearchTree
{
public:
    // Constructors
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(const Type& value);
    void clear();

    void inorder()
    {
        inorder(root);
    }
    void preorder()
    {
        preorder(root);
    }
    void postorder()
    {
        postorder(root);
    }

private:
    void inorder(Node<Type> * r);
    void preorder(Node<Type> * r);
    void postorder(Node<Type> * r);

    void insert(Node<Type>*& r, const Type& value);
    void destroyTree(Node<Type> * r);
    Node<Type> * root;
};

template <class Type>
BinarySearchTree<Type>::BinarySearchTree()
{
    root = nullptr;
}

template <class Type>
BinarySearchTree<Type>::~BinarySearchTree()
{
    destroyTree(root);
}

template <class Type>
void BinarySearchTree<Type>::insert(Node<Type>*& r, const Type& value)
{
    if (r == nullptr)
    {
        Node<Type> * newNode = new Node<Type>;

        newNode->item = value;
        newNode->left = nullptr;
        newNode->right = nullptr;

        r = newNode;
        return;
    }

    if (value < r->item)
    {
        insert(r->left, value);
    }
    else
    {
        insert(r->right, value);
    }
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type& value)
{
    insert(root, value);
}

template <class Type>
void BinarySearchTree<Type>::clear()
{
    destroyTree(root);
}

template <class Type>
void BinarySearchTree<Type>::destroyTree(Node<Type> * r)
{
    if (r == nullptr)
    {
        return;
    }

    destroyTree(r->left);
    destroyTree(r->right);
    delete r;
}

template <class Type>
void BinarySearchTree<Type>::inorder(Node<Type> * r)
{
    if (r == nullptr)
    {
        return;
    }

    inorder(r->left);
    std::cout << r->item << std::endl;
    inorder(r->right);
}

template <class Type>
void BinarySearchTree<Type>::preorder(Node<Type> * r)
{
    if (r == nullptr)
    {
        return;
    }

    std::cout << r->item << std::endl;
    preorder(r->left);
    preorder(r->right);
}

template <class Type>
void BinarySearchTree<Type>::postorder(Node<Type> * r)
{
    if (r == nullptr)
    {
        return;
    }

    postorder(r->left);
    postorder(r->right);
    std::cout << r->item << std::endl;
}

#endif      // BINARYSEARCHTREE_H
