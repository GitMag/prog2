#include "colorrow.hh"
#include <iostream>
#include <vector>
#include <cctype>
#include <random>

using namespace std;

/* MasterMind
 *
 * A briedf Description:
 *  MasterMind is game where your goal is to correctly guess all the colors in a secret
 *  row (or series) of colors. For example a row of four colors can be: rgbv that corresponds to red, green blue
 *  and violet. For each guess the player makes, the program displays two numbers that help the player to come up
 *  with the correct color row and win the game. The first number is simple. It is the amount of colors the player
 *  guessed that are exactly at the same position in the secret color row series. For example if an user guesses
 *  "vrrr" and the secret color row is "rrrv" the first number will be 2 (as colors in index 1 and 2 are at exactly
 *  the same spot. The second number is the number of colors that the player has guessed correctly, but are not located
 *  at the same spot in the guess color row and secret color row. To learn more about the game algorithm you can look
 *  at the function <compare_color_pos> located in the colorrow.cpp class.
 *
 * Usage:
 *
 *  The amount of colors in a color row can be defined by chaning the integer value of <SIZE>. Colors in the game can
 *  be tweaked by chaning the <VALID_COLORS> string. Each letter corresponds to an initial of a  color. Remember also
 *  to change the <VALID_COLORS_AMOUNT> variable accordingly. The lenght of the color row is set by the <SIZE> varaiable.
 *  By chaninging the value <GUESS_MAX> the amount of guesses the player has to try and guess the correct secret color
 *  row can and win the game can be altered.
 *
 *  When the game launches, it asks the player to selet the secret color row creation method. Two options are provided:
 *  type r (random) and provide a random generator seed to create a random secret color row. You can also type l (list)
 *  to manually enter a secret color row string. After the color row is created either randomly or by the player, the
 *  game begins. Now the player can enter a color row string to try and guess the correct secret row. The program checks
 *  for a valid color row input, and displays an error message if an incorrect color row is entered. If a valid row is
 *  entered, the color row is compared to the secret color row and the game progess is printed, where the current guess
 *  and all the previous color row guesses can bee seen. If a correct row is entered, the game will end and display
 *  a victory message. The game will also exit if the user runs out of guesses, or the user types in q or Q to quit.
 *
 *  Program author
 *  Name: Magnus Forsblom
 *  Student number: 150794761
 *  UserID: cgmafo
 *  E-Mail: magnus.forsblom@tuni.fi
 **/

// Maximum number of guesses
// (Not used in the template code)
const unsigned int GUESS_MAX = 10; // Not in use, yet

// Number of colors in a series
const unsigned int SIZE = 4;

// valid colors in the game, each char is the first letter of the color
//(blue, red, yellow, green, orange, violet)
const string VALID_COLORS = "BRYGOV"; //

// amount of valid colors
const int VALID_COLORS_AMOUNT = 6;

// Length of the suffix part when printing a row.
// The suffix consists of three vertical lines ('|') and two digits, where one
// tells the amount of totally correct colors and the other tells the amount
// of correct colors in incorrect positions.
const unsigned int SUFFIX_LENGTH_IN_PRINT = 5;

// Text printed at the beginning of the program
const string INFO_TEXT = "Colors in use: \
B = Blue, R = Red, Y = Yellow, G = Green, O = Orange, V = Violet";

// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Prints all color series.
// (Not called in the template code.)
void print_all(/* a vector including color series */)
{
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
    //for(/* go through the vector */)
    {
        // TODO: print each vector element (color series)
    }
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
}

// prints the game status (all color rows that have been played so far)
void print_game_status(vector <ColorRow> guessed_rows) {
    // used for pretty top banner, same for the bottom banner at the last
    // row of this function
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);

    // loop trough all the user guessed color rows and print the color rows
    // in a pretty way
    for (ColorRow guessed_row : guessed_rows) {
        // pretty print formatting
        cout << "| ";
        // pos of color in guessed_rows vector
        int color_pos = 0;

        // pretty print the colors in the color row so that there is a space between
        // each color (eg: R R R R). SIZE is multiplied by 2 because there are spaces for
        // each color so we need to iterate "twice" to get all the colors printed correctly.
        for (unsigned int i = 0; i < 2 * SIZE; ++i) {
            // easy way to alternate between printing spaces and a color for each iteration
            if (i % 2 == 0) {
                // even number prints color
                cout << guessed_row.get_row_string().at(color_pos);
                ++color_pos;
            } else {
                // odd number prints a space
                cout << " ";
            }
        }

        // pretty print the color row exact color match amount and same color match amount
        cout << "| " << guessed_row.get_guess_score(0) << " | ";
        cout << guessed_row.get_guess_score(1) << " |" << endl;
    }

    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
}

// create random color row to be used in the game
string create_random_color_series(int seed) {
    // create random int between 0 and COLOR_AMOUNT
    // get the corresponding color from VALID_COLORS index <random int>
    // give random engine seed the number
    default_random_engine gen(seed);
    // set random engine params, generate random numbers so that max number is not higher than valid colors amount.
    //VALID_COLORS_AMOUNT-1 because index starts from 0 (not 1)
    uniform_int_distribution<int> distr(0, VALID_COLORS_AMOUNT-1);

    // create VALID_COLORS amount of random colors for the colors series string
    string color_series = "";
    int color_index = 0;

    for (unsigned int i = 0; i < SIZE; ++i) {
        // get the color index
        color_index = distr(gen);
        // get color with corresponding color index from valid colors and append it to color_series
        color_series += VALID_COLORS.at(color_index);
    }

    // after completion return random color series
    return color_series;
}

// validate if the colors entered are valid for the game
// if invalid colors are detected, display corresponding error message
// and return false, because the input is invalid. If valid colors are detected
// just returns true without any messages.
bool validate_colors(string colors) {
    // first check the lenght of the colors series
    if (colors.length() != SIZE) {
        // colors series has wrong size, return false and display error messge
        cout << "Wrong size" << endl;
        return false;
    }

    // check that the colors in the color series are valid colors
    for (string::size_type i  =0; i < colors.size(); ++i) {
        // loop through the chars in colors string and compare if the char is found in valid colors string
        if (VALID_COLORS.find(colors.at(i)) == string::npos) {
            // invalid color char found, display error message and return false
            cout << "Unknown color" << endl;
            return false;
        }
    }
    // no problems with color row was found so it is valid, return true
    return true;
}

// convert input string to uppercase
string string_toupper(string input) {
    string output = "";
    for (string::size_type i = 0; i < input.length(); ++i) {
        // append the to lower converted letter to output string
        output += toupper(input.at(i));
    }
    // return lowercase string
    return output;
}

// checks if game has been won
bool has_won(string secret, string guess) {
    if (guess == secret) {
        return true;
    } else {
        return false;
    }
}

// Gets secret color row filling method. It can either be random (R as random) or user defined
//(L as list) (string of colors). Repeats the loop until valid input has been inputted by user.
string get_input()
{
    string colors = "";

    cout << "Enter an input way (R = random, L = list): ";
    string input_str = "";
    cin >> input_str;
    if(input_str == "R" or input_str == "r")
    {
        cout << "Enter a seed value: ";
        int seed = 0;
        cin >> seed;
        colors = create_random_color_series(seed);

    }
    else if(input_str == "L" or input_str == "l")
    {
        bool accepted = false;
        while(not accepted)
        {
            cout << "Enter four colors (four letters without spaces): ";

            cin >> colors;

            // convert colors string to lowercase
            colors = string_toupper(colors);

            if (validate_colors(colors)) {
                accepted = true;

            }
            // not valid colors, continue
        }
    }
    else
    {
        cout << "Bad input" << endl;
        // loop function until walid inpus has been inputted.
        get_input();
    }

        // valid input, return the secret color row string
        return colors;
}

// main function for the game. Handles the main game loop and also checking of game win conditions. Returns and
// exits the game when user has won the game or run out of guesses
int main()
{
    cout << INFO_TEXT << endl;
    print_line_with_char('*', INFO_TEXT.size());

    string secret_row_colors = "";
    secret_row_colors = get_input();
    // create color row object with specified colors
    ColorRow row_to_guess(secret_row_colors);

    //vector of guessed color_rows
    vector <ColorRow> guessed_rows;

    // main game loop
    unsigned int guesses = 0;
    string input = "";

    while (guesses < GUESS_MAX) {
        cout << "ROW> ";

        // get user input and make it uppercase
        cin >> input;
        input = string_toupper(input);

        // check if input is quit command
        if (input == "Q") {
            // quit the program gracefully
            return 0;
        }

        // validate colors from input
        if (validate_colors(input)) {
            // valid colors, continue with game
            // create guess color row
            ColorRow guessed_row(input);

            // compare guessed color row to secret color row
            guessed_row.compare_color_pos(row_to_guess);
            // add guessed row to vector of guessed rows
            guessed_rows.push_back(guessed_row);

            // print game status (previously guessed rows and the guess resoults)
            print_game_status(guessed_rows);

            // check if game has been won with new guess
            if (has_won(secret_row_colors, input)) {
                // display victory message and quit
                cout << "You won: Congratulations!" << endl;
                return 0;
            }
            // increment guesses
            ++guesses;
        }
    }
    // out of guesses, game lost
    cout << "You lost: Maximum number of guesses done" << endl;
    return 0;
}



