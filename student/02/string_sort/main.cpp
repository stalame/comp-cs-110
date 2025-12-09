#include <iostream>
#include <vector>

#ifndef RECURSIVE_FUNC_SORT
#define RECURSIVE_FUNC_SORT
#endif

#ifndef RECURSIVE_FUNC_IOS
#define RECURSIVE_FUNC_IOS
#endif

using namespace std;

// Returns the index of the smallest character in the given string s.
// The parameter current_ind holds the current index of the string,
// and result_ind holds the index of the smallest characters so far
// (until the current_ind).
unsigned int index_of_smallest(const string& s, unsigned int current_ind = 0,
                               unsigned int result_ind = 0)
{
    // -------------------------------------------------------------------------
    // This macro definition is needed for the unit testing of your solution, so 
    // don't touch it!
       RECURSIVE_FUNC_IOS
    // Write your solution below, please.
    // -------------------------------------------------------------------------
               // returns the index of the smallest character in the string

               // base case, when we rreach the end of the string, return the index of the smallest found value
               if (current_ind == s.length()){
                   return result_ind;
               }

               // if value of current index is smaller than current smallest, update current smallest index of whole string
               if (s[result_ind] > s[current_ind]){
                   result_ind = current_ind;
               }

               return index_of_smallest(s, current_ind+1, result_ind);

}

// Sorts the given string s based on the ASCII codes of the characters.
// The parameter current_ind holds the end index of the sorted substring so far.
void sort(string& s, unsigned int current_ind = 0)
{
    // -------------------------------------------------------------------------
    // This macro definition is needed for the unit testing of your solution, so 
    // don't touch it!
       RECURSIVE_FUNC_SORT
    // Write your solution below, please.
    // -------------------------------------------------------------------------
               // sorts string from smallest ascii to largest
               if (s.length() == current_ind){
                   return;
               }

               // Find smallest character in unsorted part of the string
               unsigned int smallest_ind = index_of_smallest(s, current_ind, current_ind);

               // swap smallest char with current position
               char temporary = s[current_ind];
               s[current_ind] = s[smallest_ind];
               s[smallest_ind] = temporary;

               // Recurse to sort remaining part of string
               sort(s, current_ind+1);

}

#ifndef UNIT_TESTS
// Main function asks input, calls other functions, and prints results.
int main()
{
    cout << "Enter a string: ";
    string input_str = "";
    cin >> input_str;
    cout << "Index of smallest character: " << index_of_smallest(input_str)
         << endl;
    sort(input_str);
    cout << "Sorted string: " << input_str << endl;
    return EXIT_SUCCESS;
}
#endif

