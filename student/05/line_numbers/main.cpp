#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    // define vars
    string input = "";
    string output = "";
    string row = "";
    vector <string> output_rows = {};

    // get input and output filename
    cout << "Input file: ";
    getline(cin, input);

    cout << "Output file: ";
    getline(cin, output);

    // try to open file
    ifstream input_file(input);

    int row_index  = 1;
    if (input_file) {
        // valid file, read lines and create output file
        ofstream output_file(output);
        while (getline(input_file, row)) {
            // append row to with row index to output file
            output_file << row_index << " " << row << endl;

            // incerement row index
            ++row_index;
        }
        output_file.close();
    } else {
        // invalid file, display error message and exit with EXIT_FAILURE
        cout << "Error! The file " << input << " cannot be opened." << endl;
        return 1;
    }

    input_file.close();

}
