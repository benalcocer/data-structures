/// @author Benjamin Alcocer
/// @file myHash.h
/// github: https://github.com/benalcocer

#ifndef MYHASH_H
#define MYHASH_H

#include <iostream>
#include <cstdlib>

using namespace std;

template <class Type1, class Type2>
class myHash
{
public:
    // Constructors
    myHash();
    myHash(const myHash<Type1, Type2>&);

    // Destructor
    ~myHash();

    // Operator overloads
    myHash<Type1, Type2>& operator=(const myHash<Type1, Type2>&);
    Type2& operator[](Type1);

private:
    // hashFunction
    size_t hashFunction(int) const;

    // binarySearch() for myHash's list
    size_t binarySearch(const size_t& index, size_t l, size_t r,
        const Type1& key);

    struct entry
    {
        Type1 key;
        Type2 item;
    };

    struct tableItem
    {
        size_t amount;
        size_t capacity;
        entry * list;
    };

    tableItem * table;
    size_t capacity;
};

///-----------------------------------------------------------------------------
/// @brief binarySearch(): This function binary searches through the hash
/// structure and returns the size_t position of the key if it is found.
/// If the key is not found, then it inserts it at the correct position while
/// maintaining a sorted list.
///
/// @param index    The specific table index we are working with
/// @param l        The left index used in binarySearch
/// @param r        The right index used in binarySearch
/// @param key      The key value that will be searched for in the hash
///-----------------------------------------------------------------------------
template <class Type1, class Type2>
size_t myHash<Type1, Type2>::binarySearch(const size_t& index, size_t l,
    size_t r, const Type1& key)
{
    size_t mid;     // size_t mid index used in binary search

    // initial binary search
    while (l < r)
    {
        mid = l + (r - l) / 2;

        // key has been found at middle
        if (table[index].list[mid].key == key)
            return mid;

        if (table[index].list[mid].key > key)
        {
            r = mid - 1;

            if (r == -1)    // since r is not a signed integer
            {
                r = 0;
                break;
            }
        }
        else
        {
            l = mid + 1;
        }
    }

    // key has been found at r (or l)
    if (table[index].list[r].key == key)
        return r;

    // Else locate the position and insert at that position
    size_t position = (table[index].list[r].key > key) ? r : r + 1;

    // shift all entry types over if needed
    for (int i = table[index].amount; i > position; i--)
    {
        table[index].list[i] = table[index].list[i - 1];
    }

    // create new entry and return position
    table[index].list[position].key = key;
    table[index].list[position].item = Type2(0);
    table[index].amount++;
    return position;
}

///-----------------------------------------------------------------------------
/// @brief myHash Default Constructor
///-----------------------------------------------------------------------------
template <class Type1, class Type2>
myHash<Type1, Type2>::myHash()
{
    capacity = 10;
    table = new tableItem[10];

    for (int i = 0; i < 10; i++)
    {
        table[i].amount = 0;
        table[i].capacity = 5;
        table[i].list = new entry[table[i].capacity];
    }
}

///-----------------------------------------------------------------------------
/// @brief myHash Copy Constructor
///-----------------------------------------------------------------------------
template <class Type1, class Type2>
myHash<Type1, Type2>::myHash(const myHash<Type1, Type2>& copy)
{
    capacity = 10;
    table = new tableItem[10];

    for (int i = 0; i < 10; i++)
    {
        table[i].amount = 0;
        table[i].capacity = 5;
        table[i].list = new entry[table[i].capacity];
    }

    *this = copy;
}

///-----------------------------------------------------------------------------
/// @brief operator = overload (assignment operator)
///
/// @param rhs  The rhs of the = sign, which is a myHash object
///-----------------------------------------------------------------------------
template <class Type1, class Type2>
myHash<Type1, Type2>& myHash<Type1, Type2>::operator=(const myHash<Type1,
    Type2>& rhs)
{
    if (this != &rhs)
    {
        for (int i = 0; i < 10; i++)
        {
            delete [] table[i].list;
            table[i].amount = rhs.table[i].amount;
            table[i].capacity = rhs.table[i].capacity;
            table[i].list = new entry[rhs.table[i].capacity];
            
            for (int j = 0; j < table[i].amount; j++)
            {
                table[i].list[j].key = rhs.table[i].list[j].key;
                table[i].list[j].item = rhs.table[i].list[j].item;
            }
        }
    }

    return *this;
}

///-----------------------------------------------------------------------------
/// @brief myHash destructor
///-----------------------------------------------------------------------------
template <class Type1, class Type2>
myHash<Type1, Type2>::~myHash()
{
    for (int i = 0; i < 10; i++)
    {
        delete [] table[i].list;
    }
    capacity = 0;
    delete [] table;
}

///-----------------------------------------------------------------------------
/// @brief overloads operator [] (array subscript operator).
/// This function inserts if needed and resizes the list if needed.
///
/// @param key  The key that will be used to search in the hash structure.
///-----------------------------------------------------------------------------
template <class Type1, class Type2>
Type2& myHash<Type1, Type2>::operator[](Type1 key)
{
    size_t indexValue = hashFunction(key);
    size_t position = 0;

    if (table[indexValue].amount != 0)
    {
        position =
            binarySearch(indexValue, 0, table[indexValue].amount - 1, key);
    }
    else
    {
        table[indexValue].list[0].key = key;
        table[indexValue].list[0].item = Type2(0);

        table[indexValue].amount++;
    }

    // if amount reaches capacity, then resize to 5 more items
    if (table[indexValue].amount == table[indexValue].capacity)
    {
        entry *ptr;
        entry *copyList;
        copyList = new entry[table[indexValue].capacity + 5];

        for (int i = 0; i < table[indexValue].amount; i++)
        {
            copyList[i] = table[indexValue].list[i];
        }

        ptr = table[indexValue].list;
        table[indexValue].list = copyList;
        delete [] ptr;

        table[indexValue].capacity += 5;
    }

    return table[indexValue].list[position].item;
}

///-----------------------------------------------------------------------------
/// @brief hashFunction(): This function returns the hashFunction.
/// The hashFunction "that takes in a key value (in the form of
/// an integer) and returns an index to be used to store/find items into
/// table[index].list[j], the hash function is: sumOfDigitsOfKey % capacity."
///
/// @param key  The key value that will be used to determine the hash value
///-----------------------------------------------------------------------------
template <class Type1, class Type2>
size_t myHash<Type1, Type2>::hashFunction(int key) const
{
    key = abs(key);     // mod will be the same besides being negative
    int sum = 0;

    // calculate sum of digits of key
    while (key != 0)
    {
        sum += key % 10;
        key /= 10;
    }

    return sum % capacity;
}

#endif      // MYHASH_H
