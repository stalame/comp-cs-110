#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string input_file;
    cout << "Input file: ";
    getline(cin, input_file);

    string output_file;
    cout << "Output file: ";
    getline(cin, output_file);

    // Attempt to open input file
    ifstream infile(input_file);
    if (not infile){
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    // Attempt to open output file
    ofstream outfile(output_file);
    if (not outfile){
        cout << "Error! The file " << output_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    int line_number = 1;
    string row;

    while (getline(infile, row)){
        outfile << line_number << " " << row << endl;
        line_number++;
    }

    infile.close();
    outfile.close();

    return EXIT_SUCCESS;
}
