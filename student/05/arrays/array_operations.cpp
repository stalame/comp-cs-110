#include "array_operations.hh"
#include <algorithm>

#include <algorithm> // for std::swap

// Returns the greatest element of the array using pointer + size
int greatest_v1(int* itemptr, int size) {
    if (!itemptr || size <= 0) return 0; // handle invalid input

    int max_val = *itemptr;
    for (int i = 1; i < size; ++i) {
        if (*(itemptr + i) > max_val) {
            max_val = *(itemptr + i);
        }
    }
    return max_val;
}

// Returns the greatest element of the array using pointer range
int greatest_v2(int* itemptr, int* endptr) {
    if (!itemptr || !endptr || itemptr >= endptr) return 0; // handle invalid input

    int max_val = *itemptr;
    for (int* p = itemptr + 1; p < endptr; ++p) {
        if (*p > max_val) {
            max_val = *p;
        }
    }
    return max_val;
}

// Copies the content of one array to another
void copy(int* itemptr, int* endptr, int* targetptr) {
    if (!itemptr || !endptr || !targetptr) return;

    while (itemptr < endptr) {
        *targetptr = *itemptr;
        ++itemptr;
        ++targetptr;
    }
}

// Reverses the elements of an array in place
void reverse(int* leftptr, int* rightptr) {
    if (!leftptr || !rightptr || leftptr >= rightptr) return;

    --rightptr; // make rightptr point to last element
    while (leftptr < rightptr) {
        std::swap(*leftptr, *rightptr);
        ++leftptr;
        --rightptr;
    }
}
