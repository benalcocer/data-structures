/// @author Benjamin Alcocer
/// @file vertex.h
/// @version 2019-11-25
/// @brief The header file for the vertex class.

#ifndef VERTEX_H
#define VERTEX_H

template <class Type>
class vertex
{
    struct node
    {
        Type item;
        node * link;
    };

public:
    class edgeIterator
    {
    public:
        friend class vertex;
        edgeIterator();
        edgeIterator(node *);
        edgeIterator operator++(int);
        Type operator*();
        bool operator==(const edgeIterator&);
        bool operator!=(const edgeIterator&);
    private:
        node * current;
    };

    // vertex class functions
    vertex();
    vertex(const vertex &);
    const vertex& operator=(const vertex&);
    ~vertex();
    edgeIterator begin();
    edgeIterator end();
    void addEdge(const Type&);

private:
    node * neighbors;
};

// edgeIterator class function definitions--------------------------------------
///-----------------------------------------------------------------------------
/// @brief edgeIterator(): The default constructor; sets the iterator to NULL.
///-----------------------------------------------------------------------------
template <class Type>
vertex<Type>::edgeIterator::edgeIterator()
{
    current = NULL;
}

///-----------------------------------------------------------------------------
/// @brief edgeIterator(node*): Constructor that assigns edge to current.
///-----------------------------------------------------------------------------
template <class Type>
vertex<Type>::edgeIterator::edgeIterator(vertex<Type>::node * edge)
{
    current = edge;
}

///-----------------------------------------------------------------------------
/// @brief Operator overload for increment (++) operator
///-----------------------------------------------------------------------------
template <class Type>
typename vertex<Type>::edgeIterator vertex<Type>::edgeIterator::operator++(int)
{
    if (current != NULL)
    {
        current = current->link;
    }
    return *this;
}

///-----------------------------------------------------------------------------
/// @brief Operator overload for dereference (*) operator
///-----------------------------------------------------------------------------
template <class Type>
Type vertex<Type>::edgeIterator::operator*()
{
    return (current == NULL) ? Type() : current->item;
}

///-----------------------------------------------------------------------------
/// @brief Operator overload for equivalence (==) binary boolean operator.
/// Compares two iterators, if they point to the same node, then return true
/// else false.
///
/// @param rhs  The second or right hand side iterator
///
/// @return     A boolean indicating if two iterators point to the same node.
///-----------------------------------------------------------------------------
template <class Type>
bool vertex<Type>::edgeIterator::operator==(const vertex<Type>::edgeIterator& rhs)
{
    return current == rhs.current;
}

///-----------------------------------------------------------------------------
/// @brief Operator overload for equivalence (!=) binary boolean operator.
/// Compares two iterators, if they point to different nodes, then return true
/// else false.
///
/// @param rhs  The second or right hand side iterator
///
/// @return     A boolean indicating if two iterators point to different nodes.
///-----------------------------------------------------------------------------
template <class Type>
bool vertex<Type>::edgeIterator::operator!=(const vertex<Type>::edgeIterator& rhs)
{
    return !(*this == rhs);
}

// vertex class function definitions--------------------------------------------
template <class Type>
typename vertex<Type>::edgeIterator vertex<Type>::begin()
{
    edgeIterator iterator(neighbors);
    return iterator;
}

template <class Type>
typename vertex<Type>::edgeIterator vertex<Type>::end()
{
    edgeIterator iterator;
    return iterator;
}

///-----------------------------------------------------------------------------
/// @brief vertex(): The default constructor; sets an empty linked list.
///-----------------------------------------------------------------------------
template <class Type>
vertex<Type>::vertex()
{
    neighbors = NULL;
}

///-----------------------------------------------------------------------------
/// @brief Copy constructor for the vertex class
///-----------------------------------------------------------------------------
template <class Type>
vertex<Type>::vertex(const vertex& rhs)
{
    neighbors = NULL;
    *this = rhs;
}

///-----------------------------------------------------------------------------
/// @brief Assignment operator (=) overload for the vertex class
///-----------------------------------------------------------------------------
template <class Type>
const vertex<Type>& vertex<Type>::operator=(const vertex& rhs)
{
    if (this != &rhs)
    {
        node *ptr;
        if (neighbors != NULL)  // if not empty, destroy linked list
        {
            while (neighbors != NULL)
            {
                ptr = neighbors;
                neighbors = neighbors->link;
                delete ptr;
            }
        }

        node *current = NULL;
        ptr = rhs.neighbors;    // let ptr point to right hand side's head
        while (ptr != NULL)
        {
            node *newNode = new node;

            // perform copy
            newNode->item = ptr->item;
            newNode->link = NULL;

            if (current == NULL)    // special head ptr case
            {
                neighbors = newNode;
            }
            else                    // else link up new node
            {
                current->link = newNode;
            }
            current = newNode;
            ptr = ptr->link;
        }
    }

    return *this;
}

///-----------------------------------------------------------------------------
/// @brief Adds a new node to the front of the neighbors list.
///-----------------------------------------------------------------------------
template <class Type>
void vertex<Type>::addEdge(const Type& edge)
{
    node *newNode = new node;

    newNode->item = edge;
    newNode->link = NULL;

    if (neighbors == NULL)   // special head ptr case
    {
        neighbors = newNode;
    }
    else                    // else link up new node
    {
        newNode->link = neighbors;
        neighbors = newNode;
    }
}

///-----------------------------------------------------------------------------
/// @brief Destructor for the vertex class
///-----------------------------------------------------------------------------
template <class Type>
vertex<Type>::~vertex()
{
    node *ptr;  // temporary pointer that will delete the head

    while (neighbors != NULL)
    {
        ptr = neighbors;
        neighbors = neighbors->link;
        delete ptr;
    }
    ptr = NULL;
}

#endif  // VERTEX_H
