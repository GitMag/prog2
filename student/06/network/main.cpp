#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

int global_depth = 0;
int global_network_size = 0;

std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

std::string print_dot_indent(int amount) {

    std:: string indent = "";
    for (int i = 0; i < amount; ++i) {
        indent += '.';
    }
    return indent;
}

// iterate trough the vector of recruited people, print the people they have recruited
int iterate_recruited(std::string name, std::map <std::string, std::vector<std::string>> database,int indent_level=1, bool no_print=false) {

    if (indent_level > global_depth) {
        global_depth = indent_level;
    }

    std::map <std::string, std::vector<std::string>>::iterator person = database.find(name);
    // get the recruited people
    std::vector <std::string> recruited_people = person->second;
    // recursion
    if (recruited_people.size() == 0) {
        return 0;
        }

        for (std::string &recruited_name : recruited_people) {
            // print recruited name
            if (not no_print) {
                std::cout << print_dot_indent(indent_level*2) << recruited_name << std::endl;
            }
            // print recruited peoples recruited people
            // increase indent level by 1
            ++global_network_size;
            iterate_recruited(recruited_name, database, indent_level+1, no_print);



        }
        return 0;

}

int main()
{
    // person1: tring master, vector person 2[name, master name]
    std::map <std::string, std::vector<std::string>> name_database;
    // TODO: Implement the datastructure here


    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            //id 1 is master (recruiter)
            //id2 is slave (recruited)

            //find master person from map
            // check if recruiter exists
            if ( name_database.find(id1) != name_database.end() ) {
                // master found, master is slave to found master
                std::map <std::string, std::vector<std::string>>::iterator master_pos = name_database.find(id1);
                // set recruited to master recruited people vector
                master_pos->second.push_back(id2);
                // create recruited map pair with empty recruited people vector
                name_database.insert({id2, std::vector<std::string> {}});


            } else {
                // create new map pair where key is master and value is recruited people vector that contains slave
                name_database.insert({id1, std::vector<std::string> {id2}});
                // create new map pair where key is slave and value is recruited people vector that is empty
                name_database.insert({id2, std::vector<std::string> {}});
            }
            continue;

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // find tartget person
            std::map <std::string, std::vector<std::string>>::iterator person = name_database.find(id);
            std::cout << person->first << std::endl;

            // recurive function
            global_network_size = 0;
            global_depth = 0;
            iterate_recruited(id, name_database);


        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            global_network_size = 0;
            global_depth = 0;
            iterate_recruited(id, name_database, 1, true);
            std::cout << global_network_size << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            global_depth = 0;
            global_network_size = 0;
            iterate_recruited(id, name_database, 1, true);
            std::cout << global_depth << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
