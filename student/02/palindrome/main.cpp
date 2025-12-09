#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

using namespace std;

bool palindrome_recursive(string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------

  // Add your implementation here
    // a string with one letter in it is automatically a palindrome
    if (s.length() == 1){
      return true;
  }
      char first = s.at(0);
      char last = s.at(s.size()-1);
      if (first != last){
          return false;
      }
    if (s.length() == 2){
    return true;
    }

      string substr = s.substr(1, s.size()-2);
      return palindrome_recursive(substr);
  }

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    cout << "Enter a word: ";
    string word;
    cin >> word;

    if(palindrome_recursive(word)){
        cout << word << " is a palindrome" << endl;
    } else {
        cout << word << " is not a palindrome" << endl;
    }

    return EXIT_SUCCESS;
}
#endif
