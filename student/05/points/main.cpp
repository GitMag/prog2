#include <fstream>
#include <iostream>
#include <map>

using namespace std;

int main()
{
    string filename = "";

    // read filename
    cout << "Input file: ";
    getline(cin, filename);

    // try to open file:
    ifstream input_file(filename);

    // check if file is valid
    if (not input_file) {
        // error
        cout << "Error! The file " << filename << " cannot be opened." << endl;
        return 1;
    } else {
        //iterate trough each line
        string row = "";
        string name = "";
        int score = 0;

        map <string, int> students = {};
        while (getline(input_file, row)) {
            // get the name and score for each row in string
            name = row.substr(0, row.find(":"));
            score = stoi(row.substr(row.find(":")+1));

            if ( students.find(name) != students.end() ) {
                // student found, append score
                map<string, int>::iterator student_loc = students.find(name);
                student_loc->second += score;
            } else {
                // not in map, create new stundent
                students.insert( { name, score } );
            }
        }

        //after loop trough the students
        cout << "Final scores:" << endl;
        for (auto &student : students) {
            cout << student.first << ": " << student.second << endl;
        }
    }

}
