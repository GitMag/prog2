#include "colorrow.hh"

/*
 *  Program author
 *  Name: Magnus Forsblom
 *  Student number: 150794761
 *  UserID: cgmafo
 *  E-Mail: magnus.forsblom@tuni.fi
 **/

ColorRow::ColorRow(const string colors):
    colors_str_(colors) {

    // initialize ColorRow
    // convert the str color row colors string to vector where each color is own
    // char type item in the vector

    vector <char> color_row = {};
    // loop trough string and add each char to vector
    for (string::size_type i = 0; i < colors.length(); ++i) {
        color_row.push_back(colors.at(i));
    }
    // set color_row_ vector to created vector
    color_row_ = color_row;
}
// get the color row as string
string ColorRow::get_row_string() const{
    //cout << "color:" << endl;
    return colors_str_;
}

// get the color row as a vector
vector <char> ColorRow::get_row_vector() {
    return color_row_;
}
int ColorRow::get_guess_score(int score_type) {
    if (score_type == 0) {
        return color_comparision_same_pos_;
    } else if (score_type == 1) {
        return color_coparision_same_color;
    } else {
        // invalid function call
        return 0;
    }
}

// compares own color row colors to other color row colors and creates wanted
// similarity values based on an algorithm
void ColorRow::compare_color_pos(ColorRow other) {

    // get the other color row colors vector
    vector <char> other_row = other.get_row_vector();
    //get own colors row vector
    vector <char> own_row = ColorRow::get_row_vector();

    // help vectors for algorithm in step 2
    vector <char> leftower_colors_guess = {};
    vector <char> leftower_colors_other = {};

    // step 1: compare direct color pos (if same color at same pos in own color row an other color row)
    int same_pos = 0;
    int i = 0;
    for (char color : other_row) {
        if (color == own_row.at(i)) {
            // increment same pos value
            ++same_pos;
        } else {
            // the color is not at the same pos, add to leftower colors vector for later processing (step 2)
            leftower_colors_guess.push_back(own_row.at(i));
            leftower_colors_other.push_back(color);
        }
        ++i;
    }

    // step 2: compare if same color exists in leftower guessed color row and leftover other color row
    int same_color = 0;
    // loop trough leftowers guessed colors (from previous step)
    for (char color : leftower_colors_guess) {
        // check if the guessed row color is in the letfower other colors row
        for (char &guess_color : leftower_colors_other) {
            if (guess_color == color) {
                // "remove" the leftover other row color from it's index in the vector. I have chosen to set the char value as 0
                // as I don't yet know how iterators work. It doesn't affect anything in this case, as we only need it to be
                // something else than the initials of the colors in the game.
                guess_color = 0;
                ++same_color;
                break;
            }
        }
    }

    // store comparision values, used later to display color row guess progress in pretty printing in the main file
    color_comparision_same_pos_ = same_pos;
    color_coparision_same_color = same_color;
}
