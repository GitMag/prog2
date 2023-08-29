#ifndef COLORROW_HH
#define COLORROW_HH

#include <iostream>
#include <vector>

using namespace std;

/*
 *  Program author
 *  Name: Magnus Forsblom
 *  Student number: 150794761
 *  UserID: cgmafo
 *  E-Mail: magnus.forsblom@tuni.fi
 **/

class ColorRow
{
public:
    // constructor
    ColorRow(string colors);
    string get_row_string() const;
    vector <char> get_row_vector();
    int get_guess_score(int score_type);
    void compare_color_pos(ColorRow other_row);



private:
    // required values
    string colors_str_ = "";
    vector <char> color_row_ = {};
    int color_comparision_same_pos_ = 0;
    int color_coparision_same_color = 0;
};

#endif // COLORROW_HH
