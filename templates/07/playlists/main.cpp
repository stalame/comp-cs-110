#include "cli.hh"

#include <iostream>

using namespace std;

int main() {

    shared_ptr<Music> music_db = make_shared<Music>();

    cout << "Input file: ";
    string input_file;
    getline(cin, input_file);
    if (!music_db->read_from_file(input_file)) {
        return EXIT_FAILURE;
    }
    cout << endl;

    shared_ptr<Cli> cli = make_shared<Cli>(music_db);

    bool exit_program = false;
    while (!exit_program) {
        exit_program = cli->exec_prompt();

        if (!exit_program) {
            cout << endl;
        }
    }

    return EXIT_SUCCESS;
}
