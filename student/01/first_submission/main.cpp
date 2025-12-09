#include <iostream>
#include <string>

using namespace std;

int main()
{
    string name = "";
    cout << "Enter your name: ";
    getline(cin, name);

    int age;
    cout << "Enter your age: ";
    cin >> age;

    cout << "Pleased to meet you, " << name << "!" << endl;
    cout << "In your next birthday you'll be " << age + 1 << " years old!" << endl;

    return EXIT_SUCCESS;
}
