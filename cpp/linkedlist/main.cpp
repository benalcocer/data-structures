#include <iostream>
#include "LinkedList.h"

using namespace std;

template <class Type>
void sizeOut(const LinkedList<Type>& list)
{
    cout << "Size: " << list.size() << endl;
}

int main()
{
    LinkedList<int> list;

    list.push_back(10);
    list.push_back(9);
    list.push_back(8);
    list.push_back(7);
    list.push_front(1);

    // Output list
    cout << "Original list...\n";
    for (auto it = list.begin(); it != list.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    sizeOut(list);
    cout << endl;

    // Reverse list
    cout << "Reverse original list...\n";
    list.reverse();
    for (auto it = list.begin(); it != list.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    sizeOut(list);
    cout << endl;

    // Clear and try to output
    cout << "Clear list and attempt to output...\n";
    LinkedList<int> copy(list);
    list.clear();
    for (auto it = list.begin(); it != list.end(); it++)
    {
        cout << *it << endl;
    }
    sizeOut(list);
    cout << endl;

    // Reset to original list and print front and back
    cout << "Reset to original list and print front and back...\n";
    list = copy;
    cout << "Front of list: " << list.front() << endl;
    cout << "Back of list:  " << list.back() << endl;

    return 0;
}
