#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string key = " ";
    cout << "Enter the encryption key: ";
    getline(cin, key);

    string::size_type key_length = 0;

    key_length = key.length();

    // Error message when key != 26 chars
    if (key_length != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }

    // Error message when string has uppercase letters
    for (char c : key){
        if (!islower(c)){
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
    }

    // Error message when string doesn't contain all letters a-z
    for (char c = 'a'; c < 'z'; ++c){
        if (key.find(c) == string::npos){
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return EXIT_FAILURE;
        }
    }

    // When encryption key passes these challenges, user enters text to be encrypted
    string text = " ";
    cout << "Enter the text to be encrypted: ";
    getline(cin, text);

    string encrypted_text = "";

    // the encryption is based on substituting the letters in the text with the letters in the encrypton key that are the
    // encrypted alphabet, so key[0] = a in text and so on.
    for (char c : text ){
        encrypted_text += key[c-'a'];
    }

    cout << "Encrypted text: " << encrypted_text << endl;
    return EXIT_SUCCESS;
}
