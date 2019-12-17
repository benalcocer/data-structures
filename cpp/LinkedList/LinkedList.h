/// @author Benjamin Alcocer
/// github: https://github.com/benalcocer

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstdlib>

template <class Type>
class LinkedList
{
public:
    struct Node
    {
        Type item;
        Node * prev;
        Node * link;
    };

    class LLIterator
    {
    public:
        friend class LinkedList;
        LLIterator();
        LLIterator(Node * ptr);
        LLIterator operator++(int);
        Type operator*();
        bool operator==(const LLIterator&);
        bool operator!=(const LLIterator&);
    private:
        Node * current;
    };

    // construct/copy/destroy
    LinkedList();
    LinkedList(const LinkedList<Type>& copy);
    ~LinkedList();
    const LinkedList& operator=(const LinkedList& rhs);

    void push_front(Type value);
    void push_back(Type value);
    void pop_front();
    void pop_back();

    Type front() const
    {
        return head->item;
    }
    Type back() const
    {
        return tail->item;
    }

    void reverse();
    void clear();

    // iterators
    LLIterator begin();
    LLIterator end();

    // capacity
    size_t size() const
    {
        return length;
    }

private:
    Node * head;
    Node * tail;
    size_t length;
};

template <class Type>
typename LinkedList<Type>::LLIterator LinkedList<Type>::begin()
{
    LLIterator iterator(head);
    return iterator;
}

template <class Type>
typename LinkedList<Type>::LLIterator LinkedList<Type>::end()
{
    LLIterator iterator(nullptr);
    return iterator;
}


// LLIterator class functions
///-----------------------------------------------------------------------------
/// @brief LLIterator()
///-----------------------------------------------------------------------------
template <class Type>
LinkedList<Type>::LLIterator::LLIterator()
{
    current = nullptr;
}

///-----------------------------------------------------------------------------
/// @brief LLIterator(Node *)
///-----------------------------------------------------------------------------
template <class Type>
LinkedList<Type>::LLIterator::LLIterator(LinkedList<Type>::Node * ptr)
{
    current = ptr;
}

///-----------------------------------------------------------------------------
/// @brief LLIterator::operator++()
///-----------------------------------------------------------------------------
template <class Type>
typename LinkedList<Type>::LLIterator LinkedList<Type>::LLIterator::operator++(int)
{
    if (current != NULL)
    {
        current = current->link;
    }
    return *this;
}

///-----------------------------------------------------------------------------
/// @brief LLIterator::operator*()
///-----------------------------------------------------------------------------
template <class Type>
Type LinkedList<Type>::LLIterator::operator*()
{
    return (current == NULL) ? Type() : current->item;
}

///-----------------------------------------------------------------------------
/// @brief LLIterator::operator==()
///-----------------------------------------------------------------------------
template <class Type>
bool LinkedList<Type>::LLIterator::operator==(const LinkedList<Type>::LLIterator& rhs)
{
    return current == rhs.current;
}

///-----------------------------------------------------------------------------
/// @brief LLIterator::operator!=()
///-----------------------------------------------------------------------------
template <class Type>
bool LinkedList<Type>::LLIterator::operator!=(const LinkedList<Type>::LLIterator& rhs)
{
    return !(*this == rhs);
}   // LLIterator class functions


// LinkedList class functions
///-----------------------------------------------------------------------------
/// @brief LinkedList Default Constructor
///-----------------------------------------------------------------------------
template <class Type>
LinkedList<Type>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    length = 0;
}

///-----------------------------------------------------------------------------
/// @brief LinkedList Copy Constructor
///-----------------------------------------------------------------------------
template <class Type>
LinkedList<Type>::LinkedList(const LinkedList<Type>& copy)
{
    *this = copy;
}

///-----------------------------------------------------------------------------
/// @brief LinkedList assignment operator (=) overload
///-----------------------------------------------------------------------------
template <class Type>
const LinkedList<Type>& LinkedList<Type>::operator=(const LinkedList<Type>& rhs)
{
    if (this != &rhs)
    {
        clear();

        Node *ptr = rhs.head;
        while (ptr != nullptr)
        {
            push_front(ptr->item);
            ptr = ptr->link;
        }
    }

    return *this;
}

///-----------------------------------------------------------------------------
/// @brief LinkedList Destructor
///-----------------------------------------------------------------------------
template <class Type>
LinkedList<Type>::~LinkedList()
{
    clear();
}

///-----------------------------------------------------------------------------
/// @brief LinkedList push_front
///-----------------------------------------------------------------------------
template <class Type>
void LinkedList<Type>::push_front(Type value)
{
    Node *newNode = new Node;

    newNode->item = value;
    newNode->link = head;
    newNode->prev = nullptr;
    head = newNode;

    if (head->link == nullptr)
    {
        tail = head;
    }

    length++;
}

///-----------------------------------------------------------------------------
/// @brief LinkedList push_back
///-----------------------------------------------------------------------------
template <class Type>
void LinkedList<Type>::push_back(Type value)
{
    Node *newNode = new Node;

    newNode->item = value;
    newNode->link = nullptr;
    newNode->prev = tail;

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        tail->link = newNode;
    }
    tail = newNode;

    length++;
}

///-----------------------------------------------------------------------------
/// @brief LinkedList pop_front
///-----------------------------------------------------------------------------
template <class Type>
void LinkedList<Type>::pop_front()
{
    Node *ptr = head;
    head = head->link;
    head->prev = nullptr;
    delete ptr;

    length--;
}

///-----------------------------------------------------------------------------
/// @brief LinkedList pop_back
///-----------------------------------------------------------------------------
template <class Type>
void LinkedList<Type>::pop_back()
{
    Node *ptr = tail;
    tail = tail->prev;
    tail->link = nullptr;
    delete ptr;

    length--;
}

///-----------------------------------------------------------------------------
/// @brief LinkedList reverse
///-----------------------------------------------------------------------------
template <class Type>
void LinkedList<Type>::reverse()
{
    if (length == 1 || length == 0)
    {
        return;
    }

    const size_t MIDPOINT = length / 2;
    size_t position = 0;
    Node * front = head;
    Node * back = tail;
    Type buffer;

    while (position < MIDPOINT)
    {
        // swap
        buffer = front->item;
        front->item = back->item;
        back->item = buffer;

        // traverse
        front = front->link;
        back = back->prev;
        position++;
    }
}

///-----------------------------------------------------------------------------
/// @brief LinkedList clear
///-----------------------------------------------------------------------------
template <class Type>
void LinkedList<Type>::clear()
{
    Node *ptr;
    while (head != nullptr)
    {
        ptr = head;
        head = head->link;
        delete ptr;
    }

    head = nullptr;
    tail = nullptr;
    length = 0;
}   // LinkedList class functions

#endif      // LINKEDLIST_H
