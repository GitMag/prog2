/* COMP.CS.110 Project 2: GIGS
 *
 * Description:
 * A simple program that acts a gig calendrar. Reads gig data from a specified
 * file. File format must be according to the specifications below. Once the
 * file is read the main menu is displayed with a "gigs > " prompt. Here the
 * user can choose from various actions that are explained more in detail in
 * the usage section below. In short the user can display artists, stages,
 * certain artists gigs and certains stages gigs. The user can also add new
 * artists, add new gigs and also cancel gigs from a certain date onwards.
 * All necessary checking is done by the program, so that no invalid input
 * is accepted.
 *
 *
 * USAGE:
 * ARTISTS - Prints all known artist names
 * ARTIST <artist name> - Prints single artist's gigs
 * STAGES - Prints all known stage names and their locations
 * STAGE <stage name> - Prints all artists having a gig at the given stage
 * ADD_ARTIST <artist name> - Adds a new artist
 * ADD_GIG <artist name> <date> <town name> <stage name> - Adds a new gig for
 * an artist with the given date, town, and stage (the artist can't already
 * have a gig on the same date and there can't be other gigs at the same stage
 * at the same time)
 * CANCEL <artist name> <date> - Cancels artist's gigs after the given date
 * QUIT - Quits the program.
 *
 * The data file's lines should be in format
 * artist_name;date;town_name;stage_name.
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 *  Program author
 *  Name: Magnus Forsblom
 *  Student number: 150794761
 *  UserID: cgmafo
 *  E-Mail: magnus.forsblom@tuni.fi
 * */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// define main gig_database to store gigs in:
// map <string (artist name),
// map <string (gig date),
// <vector (gig venue, gig city)>>>
std::map <std::string, std::map<std::string,
std::vector<std::string>>> gig_database;

// Farthest year for which gigs can be allocated
const std::string FARTHEST_POSSIBLE_YEAR = "2030";

// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split(const std::string& str, char delim = ';')
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for ( char current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quotation = not inside_quotation;
        }
        else if ( current_char == delim and not inside_quotation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

// Checks if the given date_str is a valid date, i.e. if it has the format
// dd-mm-yyyy and if it is also otherwise possible date.
bool is_valid_date(const std::string& date_str)
{
    std::vector<std::string> date_vec = split(date_str, '-');
    if ( date_vec.size() != 3 )
    {
        return false;
    }

    std::string year = date_vec.at(0);
    std::string month = date_vec.at(1);
    std::string day = date_vec.at(2);
    std::vector<std::string> month_sizes
            = { "31", "28", "31", "30", "31", "30",
                "31", "31", "30", "31", "30", "31" };

    if ( month < "01" or month > "12" )
    {
        return false;
    }
    if ( year < "0001" or year > FARTHEST_POSSIBLE_YEAR )
    {
        return false;
    }
    unsigned int year_int = stoi(year);
    bool is_leap_year = (year_int % 400 == 0) or
                        (year_int % 100 != 0 and year_int % 4 == 0);
    if ( day >= "01" and
        (day <= month_sizes.at(stoi(month) - 1) or
        (month == "02" and is_leap_year and day <= "29")) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// combines two elements from venue location vector and returns readable string
std::string combine_venue_location(std::vector <std::string> location_parts) {
    return location_parts.at(0) + ", " + location_parts.at(1);
}

// checks if specified artist exists in gig_database. Returns the result.
bool artist_exists(std::string artist_name) {
    return (gig_database.find(artist_name) != gig_database.end());
}

// adds artist to database. If artists already exists displays error message
//if not in silent mode. Silent mode = no printouts.
void add_artist(std::string artist_name, bool silent_mode=false) {

    if (not artist_exists(artist_name)) {
        gig_database.insert({artist_name, {}});
        if (not silent_mode) {
            std::cout << "Artist added." << std::endl;
        }
    } else if (not silent_mode) {
        std::cout << "Error: Already exists." << std::endl;

    }
}

// validates that a gig specified gig specifitactions are valid.
// used to read gig data from gig_file and also when adding or canceling gig
// mode is set with params file_read_mode and cancel_mode respectively.
// returns if gig is valid or not
bool validate_gig_input(std::string gig_artist, std::string gig_date,
                        bool file_read_mode = false, bool cancel_mode = false) {

    // check that the artist does not have double bookings if artist exists:
    if (artist_exists(gig_artist)) {
        for (auto &gig : gig_database.at(gig_artist)) {
            if (gig.first == gig_date and not cancel_mode) {
                std::cout << "Error: Already exists." << std::endl;
                return false;
            }
        }
    } else if (not file_read_mode) {
        std::cout << "Error: Not found." << std::endl;
        return false;
    }

    // check that the date is valid
    if (not is_valid_date(gig_date)) {
        std::cout << "Error: Invalid date." << std::endl;
        return false;
    }
    return true;
}

// makes a gig booking (adds gig to main gig_database) if the gig information
// is valid. Returns bool value depending on if booking was successfull.
bool make_booking(std::string gig_artist, std::string gig_date,
                  std::vector <std::string> gig_location,
                  bool file_read_mode = false) {

    // validate gig input
    bool is_valid = false;
    is_valid = validate_gig_input(gig_artist, gig_date, file_read_mode);

    if (not is_valid) {
        return false;
    }

    // create a pair with key date and value gig location vector
    std::pair <std::string, std::vector <std::string>>
            date_and_venue = {gig_date, gig_location};

    // check that the venue does not have double bookings for the same day
    std::string venue_location = "";
    std::string venue_date = "";
    for (auto &artist : gig_database) {
        // iterate
        for (auto &gig : artist.second) {

            // check if gig venue has double bookings
            if (gig.first == gig_date and gig.second == gig_location) {
                std::cout << "Error: Already exists." << std::endl;
                return false;
            }
        }
    }

    // insert date and venue to specified artist
    gig_database.at(gig_artist).insert(date_and_venue);

    if (not file_read_mode) {
        std::cout << "Gig added." << std::endl;
    }

    return true;
}

// reads the gig information from specified file. Adds the gigs from the
// file to main database. Returns true or false depending on if file processing
// was successfull
bool process_file(std::string filename) {

    // try to open specified file
    std::ifstream gigs_file(filename);

    // check if file is valid
    if (not gigs_file) {
        std::cout << "Error: File could not be read." << std::endl;
        return false;

    } else {

        //file opened, check if contents are valid
        // itrearte trough each line in file and read data to gigs_database
        std::string file_row = "";
        std::vector <std::string> row_contents = {};
        while (std::getline(gigs_file, file_row)) {
            // split the row separated by semicolon and get the row contens
            //as vector
            row_contents = split(file_row);

            // check that the row contents are valid, each row should have
            //artist name, date, venue city and venue name so lenght of vector
            //needs to be 4
            if (row_contents.size() != 4) {
                // invalid size vector, error
                std::cout << "Error: Invalid format in file." << std::endl;
                return false;
            } else {
                //check that no row is empty
                for (auto &gig_data : row_contents) {
                    if (gig_data == "") {
                        std::cout << "Error: Invalid format in file."
                                  << std::endl;
                        return false;
                    }
                }
            }

            // get gig info
            std::string gig_artist = row_contents.at(0);
            std::string gig_date = row_contents.at(1);
            std::vector <std::string> gig_location = {row_contents.at(2),
                                                      row_contents.at(3)};
            std::pair <std::string, std::vector <std::string>>
                    date_and_venue = {gig_date, gig_location};

            // try to add artist to gig_list
            add_artist(gig_artist, true);

            // try to make booking
            bool is_success = false;
            is_success = make_booking(gig_artist, gig_date, gig_location, true);

            if (not is_success) {
                return false;
            }
        }
    }
    return true;
}

// convert passed string to lowercase, returns the lowercase string
std::string string_tolower(std::string input) {
    std::string output = "";
    for (std::string::size_type i = 0; i < input.length(); ++i) {
        // append the to lower converted letter to output string
        output += tolower(input.at(i));
    }
    // return lowercase string
    return output;
}

// prints all the artists in alphabetical order from gig_database
void print_all_artists() {
    std::cout << "All artists in alphabetical order:" << std::endl;
    for (auto &artist : gig_database) {
        std::cout << artist.first << std::endl;
    }
}

// prints all the artist's gigs in ASCII date ordr
void print_artist_gigs(std::string artist_name) {

    // print the artist gigs if artist exists in gigs_database
    if (gig_database.find(artist_name) != gig_database.end()) {

        std::cout << "Artist " << artist_name
                  << " has the following gigs in the order they are listed:"
                  << std::endl;

        // print gigs for artist sorted by date
        std::string gig_full_location = "";
        for (auto &gig : gig_database.at(artist_name)) {
            gig_full_location = combine_venue_location(gig.second);
            std::cout << " - " << gig.first << " : " << gig_full_location
                      << std::endl;
        }
    } else {
        std::cout << "Error: Not found." << std::endl;
    }
}

// prints all gig stage locations in alphabetical order
void print_all_stages() {

    std::vector <std::string> stages = {};

    // iterate trough all artist and get the stages they perform in.
    //Add stage to vector stages if it does not exist in stages vector
    std::string venue_full_location = "";
    for (auto &artist : gig_database) {
        // iterate
        for (auto &gig : artist.second) {
            venue_full_location = combine_venue_location(gig.second);

            // check if gig venue exists in stages vector
            if ((std::find(stages.begin(), stages.end(),
                 venue_full_location) != stages.end()) == false) {
                // does not exist, add to vector
                stages.push_back(venue_full_location);
            }
        }
    }
    // sort stages vector to ASCII alphabetical order
    std::sort(stages.begin(), stages.end());

    std::cout << "All gig places in alphabetical order:" << std::endl;
    for (std::string &stage : stages) {
        std::cout << stage << std::endl;
    }

}

// prints all artists performing on specified stage
void print_artists_on_stage(std::string stage) {

    std::vector <std::string> artists = {};

    // iterate trough artists and check if stage is specified stage
    for (auto &artist : gig_database) {
        for (auto &gig : artist.second) {
            // get the venue name
            if (gig.second.at(1) == stage) {

                artists.push_back(artist.first);
            }
        }
    }

    // print all artists performing on stage. If vector is empty display error
    if (artists.size() != 0) {
        std::cout << "Stage " << stage << " has gigs of the following artists:"
                  << std::endl;
        for (auto &artist : artists) {
            std::cout << " - " << artist << std::endl;
        }
    } else {
        std::cout << "Error: Not found." << std::endl;
    }
}

// cancel all artists gigs from specified date onwards. If date is invalid
// or no gigs are after the date an error is displayed.
void cancel_gigs_from_date_onwards(std::string artist_name, std::string date) {

    // validate artist and date
    bool is_success = false;
    // validate_gig_input is called with cancel_mode = true
    is_success = validate_gig_input(artist_name, date, false, true);

    if (not is_success) {
        return;
    }

    // try to cancel all gigs from date <date> onwards
    // dates to cancel
    std::vector <std::string> dates_to_cancel = {};

    for (auto &gig : gig_database.at(artist_name)) {
        if (gig.first > date) {
            dates_to_cancel.push_back(gig.first);
        }
    }

    // cancel the dates in vector
    for (auto &date : dates_to_cancel) {
        gig_database.at(artist_name).erase(date);
    }

    // display message to user
    if (dates_to_cancel.size() != 0) {
        std::cout << "Artist's gigs after the given date cancelled."
                  << std::endl;
    } else {
        std::cout << "Error: No gigs after the given date."
                  << std::endl;
    }
}

int main()
{
    // file to read gigs from
    std::string gigs_file = "";

    std::cout << "Give a name for input file: ";
    std::getline(std::cin, gigs_file);

    // try to process gigs file
    bool is_success = false;
    is_success= process_file(gigs_file);

    // handle process result action
    if (is_success == false) {
        return EXIT_FAILURE;
    }

    // gigs file read successfully
    // main loop
    std::string input = "";
    std::string command = "";
    std::vector <std::string> input_parts = {};
    while (true) {

        // variable to store how many  parts the command contains
        int command_parts = 1;

        // wait for user input
        std::cout << "gigs> ";
        std::getline(std::cin, input);

        // if input contains many words separated by spaces then
        //split input to parts separated by empty space ' '.
        if (input.find(" ") != std::string::npos) {
            input_parts = split(input, ' ');

            // get main command action and set it to lowercase
            command = string_tolower(input_parts.at(0));
            // set command parts to size of input_parts vector
            command_parts = input_parts.size();
        } else {
            // input does not contain spaces, set input as command and set it
            //to lowercase
            command = string_tolower(input);

        }

        // proceed according to command:
        if (command == "quit") {
            break;

        } else if (command == "artists") {
            // print all artists
            print_all_artists();

        } else if (command == "artist" and command_parts > 1) {
            // get artist name and print artist gigs by date order
            std::string artist_name = input_parts.at(1);
            print_artist_gigs(artist_name);

        } else if (command == "stages") {
            // print all stages where artists perform
            print_all_stages();

        } else if (command == "stage" and command_parts > 1) {
            // print all artists performing on specified stage
            std::string stage = input_parts.at(1);
            print_artists_on_stage(stage);

        } else if (command == "add_artist" and command_parts > 1) {
            std::string artist_name = input_parts.at(1);
            add_artist(artist_name);

        } else if (command == "add_gig" and command_parts > 4) {
            std::string artist_name = input_parts.at(1);
            std::string gig_date = input_parts.at(2);
            std::vector <std::string> gig_venue = {input_parts.at(3),
                                                   input_parts.at(4)};
            make_booking(artist_name, gig_date, gig_venue);

        } else if (command == "cancel" and command_parts > 2) {
            std::string artist_name = input_parts.at(1);
            std::string gig_date = input_parts.at(2);
            cancel_gigs_from_date_onwards(artist_name, gig_date);

        } else {
            // input was invalid, display error
            std::cout << "Error: Invalid input." << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
