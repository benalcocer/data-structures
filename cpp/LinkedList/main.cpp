/// @author Benjamin Alcocer
/// github: https://github.com/benalcocer

#include <iostream>
#include <vector>
#include <string>
#include "LinkedList.h"

using namespace std;

void sizeOut(int size)
{
    cout << "Size: " << size << endl;
}

template <class T>
void test(const vector<T>& inputData)
{
    if (inputData.empty())
    {
        return;
    }
    
    LinkedList<T> list;
    for (unsigned int i = 0; i < inputData.size(); ++i)
    {
        list.push_back(inputData[i]);
    }

    // Output list
    cout << "Original list...\n";
    list.printList();
    sizeOut(list.size());
    cout << endl;

    // Reverse list
    cout << "Reverse original list...\n";
    list.reverse();
    list.printList();
    sizeOut(list.size());
    cout << endl;

    // Copy list and attempt to output
    cout << "Copy list and attempt to output...\n";
    LinkedList<T> copy = list;
    cout << "Original: ";
    list.printList();
    cout << "Copy: ";
    copy.printList();
    cout << endl;
    
    
    cout << "Reverse copy and display...\n";
    copy.reverse();
    cout << "Original: ";
    list.printList();
    cout << "Copy: ";
    copy.printList();
    cout << endl;
    
    cout << "Front of list: " << list.front() << endl;
    cout << "Back of list:  " << list.back() << endl;
    cout << "Front of copy: " << copy.front() << endl;
    cout << "Back of copy:  " << copy.back() << endl;
    cout << "END OF TEST FUNCTION CALL-----------------------\n";
}

int main()
{
    vector<int> int_data = {1, 10, 9, 8, 7};
    vector<string> string_data = {"ben", "benji", "Benjamin", "benal", "GITHUB"};
    test(int_data);
    test(string_data);

    return 0;
}
