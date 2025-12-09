#include <iostream>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    minstd_rand generator;

    cout << "Enter some text. Quit by entering the word \"END\"." << endl;
    string word;

    while (cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

        // a word that is less than 3 chars can't really be shuffled.
        if (word.size() > 3){
            shuffle(word.begin()+1, word.end()-1,generator); // TODO: implement your solution here
        }
	
        cout << word << endl;
    }

    return EXIT_SUCCESS;
}
