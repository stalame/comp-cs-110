#include <cstdlib>
#include <iostream>

using namespace std;

// Write your swap function here.
void swap(int& a, int& b){
    // swaps the integers a and b

    // a copy of a is made into c, b into d
    int c = a;
    int d = b;

    // a is assigned the value of b = c
    a = d;

    // b is assigned a
    b = c;
}

#ifndef UNIT_TESTING
int main()
{
    cout << "Enter an integer: ";
    int i = 0;
    cin >> i;

    cout << "Enter another integer: ";
    int j = 0;
    cin >> j;

    swap(i, j);
    cout << "The integers are " << i << " and " << j << endl;

    return EXIT_SUCCESS;
}
#endif
