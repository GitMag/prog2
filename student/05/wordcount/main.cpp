#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

vector <string> split_text(string text, char split_char) {

    // loop trough string and split string when split_char is
    // detected

    vector <string> words = {};
    string word = "";

    for (string::size_type i = 0; i < text.length(); ++i) {

        char current_char = text.at(i);
        // check if text at i is split char
        if (current_char == split_char) {
            // add word to wors
            words.push_back(word);
            word = "";
            continue;
        }
        // add current char to word
        word += current_char;

    }
    words.push_back(word);
    return words;
}
bool is_processed(string processed_word, vector <string> words) {
    for (string &word : words) {
        if (word == processed_word) {
            return true;
        }
    }
    return false;
}

string rowlist_to_string(vector <int> rowlist) {

    string formatted_rows = "";
    int i = 0;
    for (int row : rowlist) {
        if (i != 0) {
           formatted_rows += ", ";
        }
        formatted_rows += to_string(row);
        ++i;
    }
    return formatted_rows;
}

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

        // string word, vector with rows where the word has occurred
        map <string, vector <int>> words = {};

        int current_row = 1;
        while (getline(input_file, row)) {
            // define processed words in a row vector
            vector <string> processed_words = {};
            vector <string> words_in_row = split_text(row, ' ');

                for (string &word : words_in_row) {
                    if (not is_processed(word, processed_words)) {
                        // not yet processed, add current row to map or edit if already exists
                        if ( words.find(word) != words.end() ) {
                            // word already found, append current line to repetitions vector
                            map<string, vector <int>>::iterator word_loc = words.find(word);
                            word_loc->second.push_back(current_row);
                        } else {
                            // word does not exist, create it
                            vector <int> row_num = {current_row};
                            words.insert({word, row_num});
                        }
                        processed_words.push_back(word);
                    }

            }
                ++current_row;
        }
        // to do: print words map and count the amount of elements in the second element vector
        for (auto &word : words) {

            int repetitions = word.second.size();
            string formatted_rows = rowlist_to_string(word.second);

            cout << word.first << " " << repetitions << ": " << formatted_rows << endl;
        }

    }
}
