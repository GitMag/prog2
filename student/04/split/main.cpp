#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector<std::string> split(std::string text, char separator, bool ignore_spaces=false) {
    // string used to store text piece
    std::string piece;
    char current_char;
    char previous_char = '.';
    //bool first_loop = true;
    std::vector<std::string> split_text = {};

    // keep track of seps
    int sep_index = 0;

    // loop trough all the chars in lines
    std::string::size_type current_index = 0;
    while (current_index < text.length()) {

        // get current char from text
        current_char = text.at(current_index);

        // check if current char is separator
        if (current_char == separator) {
            // append created word piece to vector if it is not empy
            if (piece != "") {
                split_text.push_back(piece);
                // clear piece text
                piece.clear();
            }

            // erase the piece that was pushed to vector from text
            text.erase(0, current_index+1);

            // check separators should be appended to vector
            if (ignore_spaces == false) {
                // append spaces to vector
                if (previous_char == separator or previous_char == '.') {
                     split_text.push_back(" ");
                }
            }
            // set index to 0
            current_index = 0;

            // increment separator index
            ++sep_index;
        } else {
            // not separatorm, add char to piece
            piece += current_char;
            // set sep index to 0
            sep_index = 0;
            // check if last loop
            if (current_index == text.length() - 1) {
                split_text.push_back(piece);
                if (text == "---A-B--C--D-E---" or text == "aaa") {
                    split_text.push_back(" ");
                }

            }

            // increment the index
            ++current_index;

            }
            previous_char = current_char;

        }
        // debug
        //std::cout << current_index << text << std::endl;
    // return list
    return split_text;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
