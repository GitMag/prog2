/*
 * COMP.CS.110 Programming 2, Autumn 2022
 * Project3: Book contents
 *
 * Description:
 * A program that loads book data (Chapter id (string); Chapter full name
 * (string); chapter lenght (int)) to a datastructure from a csv file. Links the
 * chapters together with pointers so that a chapter can have parents
 * (pointer to parent chapter) and subchapters (a vector of pointers to
 * subcahpters). A commandline based ui allows the user to perform various
 * commands to see different kinds of info of the chapters. For example, you can
 * print all th chapters, or see which of the chapters is the longest. For more
 * detailed usage-instructions see the usage section down below.
 *
 * Usage: (command - info)
 * QUIT - Closes the program
 *
 * IDS - Prints all the ids for the chapters that are stored in the datastructure.
 *
 * CONTENTS - Prints the table of contents for the book
 *
 * CLOSE <ID> Closes the given chapter by <ID> and all it' subchapters except
 *
 * subchapters that dont contain any more subchapters.
 * OPEN <ID> Opens the given chapter by <ID>
 *
 * OPEN_ALL Opens all the chapters (chapters and all subchapters)
 *
 * PARENTS <ID> <N> Prints all the parent chapters for a given chapter <ID> in an
 * alphabetical order to a depth of N (where N is an integer). If a chapter has
 * less than N parents chapters then iteration is stopped at the last parent
 * chapter (no empty/non existing chapters are printed).
 *
 * SUBCHAPTERS <ID> <N> Prints all the subchapters for a given chapters in
 * alphabetical order to a depth of <N> (so N=1 prints all direct subchapters,
 * N=2 Prints all direct subchapters and also all subchapters subchapters etc..)
 *
 * SIBLINGS <ID> Prints all the siblings for a given chapter <ID> (all the
 * chapters that have the same parent chapter, where <ID> is not a part of this
 * group)
 *
 * LENGTH <ID> Prints the lenght of chapter <ID> and all its subhcapters
 * combined.
 *
 * LONGEST <ID> Prints the longest chapter from chapter <ID>'s hierarcy taking
 * into account all subchapters.
 *
 * SHORTEST <ID> Prints the shortest chapter from chapter <ID>'s hierarcy taking
 * into account all subchapters.
 *
 * HELP [<CMD>] - Prints information about the commands: name, aliases, required
 * parameters. If no parameter is given for the HELP command, it prints
 * information about all the commands. If a command name is given as a
 *
 * parameter, it prints aforementioned information only about the given command.
 * READ <FILE> - Reads commands from the given file instead of reading them from
 * the command line one by one. In the given file, each command is listed in a
 * line of its own, and the last command must be QUIT.
 *
 * Author: Magnus Forsblom
 * Student ID: 150794761
 * Username: cgmafo
 * E-mail: magnus.forsblom@tuni.fi
 *
 */

#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <map>
#include <algorithm>


// Named constants to improve readability in other modules
const std::string EMPTY = "";
const int NO_LENGTH = -1;
const int MAX_INT = 99999;

// Command parameters have been collected into a vector. In this way each
// method implementing a command has the same parameters (amount and type).
// If a command has no parameters, the vector is empty.

//REMOVE _ FROM CODE USE camelCase
using Params = const std::vector<std::string>&;

// Struct for a book chapter
struct Chapter
{
    std::string id_ = EMPTY;
    std::string fullName_ = EMPTY;
    std::string statusSym = "- ";
    bool isOpen = true;
    int length_ = 0;
    Chapter* parentChapter_ = nullptr;
    std::vector<Chapter*> subchapters_;
};

using IdSet = std::set<std::string>;

// Book class, a datastucture for Chapter structs
class Book
{
public:
    // Constructor
    Book();

    // Destructor
    ~Book();

    // Adds a new Chapter to the datastructure.
    void addNewChapter(const std::string& id, const std::string& fullName,
                       int length);

    // Adds a new chapter-subchapter relation.
    void addRelation(const std::string& subchapter,
                     const std::string& parentChapter);

    // Prints all stored chapters: ID, full name and length
    void printIds(Params params) const;

    // Prints the contents page of the book. Chapters are printed in the order,
    // they are in the book, subchapters are indented appropriately.
    // Either '-' or '+' is printed before each chapter, '-' for open chapters
    // and '+' for closed one. If a chapter is open, its subchapters are
    // also listed.
    void printContents(Params params) const;

    // Closes the given chapter and its subchapters.
    void close(Params params) const;

    // Opens the given chapter.
    void open(Params params) const;

    // Opens all chapters.
    void openAll(Params params) const;

    // Prints the amount and names of parent chapters in given distance from
    // the given chapter. Parent chapters are printed in alphabethical order.
    void printParentsN(Params params) const;

    // Prints the amount and names of subchapters in given distance from
    // the given chapter. Subchapters are printed in alphabethical order.
    void printSubchaptersN(Params params) const;

    // Prints the sibling chapters of the given chapter, i.e. the chapters
    // sharing the parent chapter with the given one.
    void printSiblingChapters(Params params) const;

    // Prints the total length of the given chapter, i.e. the sum of lengths
    // of the given chapter and its subchapters.
    void printTotalLength(Params params) const;

    // Prints the longest chapter in the hierarchy of the given chapter.
    void printLongestInHierarchy(Params params) const;

    // Prints the shortest chapter in the hierarchy of the given chapter.
    void printShortestInHierarchy(Params params) const;

    // Prints the direct parent chapter of the given chapter.
    // Students will not implement this method.
    void printParent(Params params) const;

    // Prints the direct subchapters of the given chapter.
    // Students will not implement this method.
    void printSubchapters(Params params) const;

private:
    /* The following functions are meant to make project easier.
     * You can implement them if you want and/or create your own.
     * Anyway it would be a good idea to implement more functions
     * to make things easier and to avoid "copy-paste-coding".
     */

    // Returns a pointer for ID.
    Chapter* findChapter(const std::string& id) const;

    // book chapters database to store all chapters
    // key=id, value=Book chapter struct
    std::map <std::string, Chapter*> bookChapters;

    // book chapters database to store all chapters
    // key=fullname, value=Book chapter struct
    std::map <std::string, Chapter*> bookChaptersFullname;

    // vector of chapters in the order they were added
    std::vector <Chapter*> bookChaptersUnsorted;

    // prints all subchapters for parent chapter
    void printSubchapters(Chapter* parent, int depth=1, int subchapNum=1) const;

    //change chapter opened state (opened/closed) to chapter and all subchapters
    //action 0 = close, action 1 = open
    void setSubchapterStates(Chapter* parent, int action) const;

    // sort all chapters from given vector and return them in a vector
    // that is sorted by chapter id (A-Z)
    std::vector <std::string> getSortedIds(std::vector <Chapter*> chapters) const;

    // iterates down from parent to child recursively, returns all chapter pointers
    // as vector. max iterations can be set with param maxIterations
    std::vector <Chapter*> getAllSubchapters(Chapter* parent,
                           std::vector <Chapter*> chapters,
                           int maxIterations=MAX_INT,
                           int& iterationsDone = *(new int(0))) const;
};

#endif // BOOK_HH
