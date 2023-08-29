#include "book.hh"

// constructor
Book::Book() {

}

// destructor
Book::~Book()
{
    // free memory
    for (auto &chapter : bookChapters) {
        chapter.second = nullptr;
    }
    for (auto &chapter : bookChaptersFullname) {
        chapter.second = nullptr;
    }
    for (auto &chapter : bookChaptersUnsorted) {
        chapter = nullptr;
        delete chapter;
    }
}

// add new chapter to database(es)
void Book::addNewChapter(const std::string &id, const std::string &fullName, int length)
{

    //add chapter to database if it doesnt already exist
    if (bookChapters.find(id) == bookChapters.end()) {
        // create new chapter and add data to it
        Chapter* newChapter = new Chapter;
        newChapter->id_ = id;
        newChapter->fullName_ = fullName;
        newChapter->length_ = length;

        // insert pointer to different databases
        bookChapters.insert({id, newChapter});
        bookChaptersFullname.insert({fullName, newChapter});
        bookChaptersUnsorted.push_back(newChapter);
    } else {
        std::cout << "Error: Already exists." << std::endl;
        return;
    }
}

// link chapters together, adds pointer to subchapter and parentchapter
void Book::addRelation(const std::string &subchapter, const std::string &parentChapter)
{

    // find the chapters
    Chapter* child = findChapter(subchapter);
    Chapter* parent = findChapter(parentChapter);

    // check that parent is found and add relations
    if (parent != nullptr) {
        child->parentChapter_ = parent;
        parent->subchapters_.push_back(child);
    }
}

void Book::printIds(Params params) const
{
    // just to get rid of compiler errror
    params.size();

    std::cout << "Book has "<< bookChapters.size() << " chapters:" << std::endl;

    // print ids sorted by chapter fullname
    for (auto &chapter : bookChaptersFullname) {
        std::cout << chapter.second->fullName_<< " --- "
                  << chapter.second->id_ << std::endl;
    }
}

// recursion function to print all the subchapters
// from given parent chapter.
void Book::printSubchapters(Chapter *parent, int depth, int subchapNum) const
{
    // iterate parent pointer's subchapters
    for (auto subchapter : parent->subchapters_) {

        // print indentation to prettiy the printed out text
        // each iteration adds 2 more empty spaces
        std:: string indent = "";
        for (int i = 0; i < depth*2; ++i) {
            indent += ' ';
        }

        // pretty print the current subchapter details
        std::cout << subchapter->statusSym << indent << subchapNum << ". "
                  << subchapter->fullName_ << " ( " << subchapter->length_
                  << " )" << std::endl;

        // if subchapter is in opened print it's subchapters with recursion
        if (subchapter->isOpen) {
            printSubchapters(subchapter, depth + 1);
        }
        subchapNum++;
    }
}

// changes all subchapter states from given parent to wanted action.
// action=0 closed subchater, action=1 open subchapter.
void Book::setSubchapterStates(Chapter *parent, int action) const
{
    // iterate trough all subchapters
    for (auto &subchapter : parent->subchapters_) {
        // set subhcapter state to closed if it has more subcchapters
        if (action == 0 and subchapter->subchapters_.size() != 0) {
            subchapter->isOpen = false;
            subchapter->statusSym = "+ ";

        } else if (action == 1) {
            subchapter->isOpen = true;
            subchapter->statusSym = "- ";
        }
        // set state for subchapters subchapters recursively
        setSubchapterStates(subchapter, action);
    }
}

// sort all chapters from given vector and return them in a vector
// that is sorted by chapter id (A-Z)
std::vector<std::string> Book::getSortedIds(std::vector<Chapter *> chapters) const
{
    // create vector with subchapter id strings
    std::vector <std::string> sortedIds = {};
    for (auto &chapter: chapters) {
        sortedIds.push_back(chapter->id_);
    }
    // sort list in alphabetical order
    //print parent chapters
    sort(sortedIds.begin(), sortedIds.end());

    return sortedIds;
}

// get all subchapters from given parent pointer and return all the subchapter
// pointers in a vector
std::vector<Chapter *> Book::getAllSubchapters(Chapter *parent,
                       std::vector<Chapter *> chapters, int maxIterations,
                       int &iterationsDone) const
{
    iterationsDone++;
    // iterate all subchapters from given subchapter
    for (auto &subchapter : parent->subchapters_) {
        // iterate to next level (selected subchapters subchapters) if desired
        // level set by param maxIterations has not been reached
        if (iterationsDone < maxIterations) {
        chapters = getAllSubchapters(subchapter, chapters, maxIterations,
                                     iterationsDone);
        }
        chapters.push_back(subchapter);
    }

    return chapters;
}

// prints all chapters and its subchapters in a pretty print form where each
// new subchapter is intented with spaces.
void Book::printContents(Params params) const
{
    // to get rid of compiler warning
    params.size();

    int chapterNum = 1;
    for (auto &chapter : bookChaptersUnsorted) {
        if (chapter->parentChapter_ == nullptr) {
            // no parent chapter so we print name and possible subchapters
            //  1. Introduction to the Basic Concepts ( 2 )
            std::cout << chapter->statusSym << chapterNum << ". "
                      << chapter->fullName_ << " ( " <<chapter->length_ << " )"
                      << std::endl;

            // print all subchapters if chapter state is opened
            if (chapter->isOpen) {
                printSubchapters(chapter);
            }
            chapterNum++;
        }
    }
}

// closes chapter and all its subchapters
void Book::close(Params params) const
{
    std::string chapterId = params.at(0);
    Chapter* chapterToClose = findChapter(chapterId);

    // check if chapter is valid
    if (chapterToClose == nullptr) {
        std::cout << "Error: Not found: " << chapterId << std::endl;
        return;
    }

    // set chapter state to closed
    chapterToClose->isOpen = false;
    chapterToClose->statusSym = "+ ";
    setSubchapterStates(chapterToClose, 0);
}

// open chapter
void Book::open(Params params) const
{
    std::string chapterId = params.at(0);
    Chapter* chapterToOpen = findChapter(params.at(0));

    // check if chapter is valid
    if (chapterToOpen == nullptr) {
        std::cout << "Error: Not found: " << chapterId << std::endl;
        return;
    }

    // set chapter state to opened
    chapterToOpen->isOpen = true;
    chapterToOpen->statusSym = "- ";

}

// opens all chapters and subchapters
void Book::openAll(Params params) const
{
    // to get rid of compiler warning
    params.size();

    for (auto &chapter : bookChaptersUnsorted) {
        // check if chapter has parent chapter
        if (chapter->parentChapter_ == nullptr) {
            // open chapter and its subchapters recursively
            open(std::vector <std::string> {chapter->id_});
            setSubchapterStates(chapter, 1);
        }
    }
}

// prints subchapter's parents to a level N set by params.
void Book::printParentsN(Params params) const
{
    std::string chapterId = params.at(0);
    Chapter* chapterToIterate = findChapter(params.at(0));
    int iterations = stoi(params.at(1));


    if (iterations < 1) {
        std::cout << "Error. Level can't be less than 1." << std::endl;
        return;
    } else if (chapterToIterate == nullptr) {
        std::cout << "Error: Not found: " << chapterId << std::endl;
        return;
    } else if (chapterToIterate->parentChapter_ == nullptr) {
        std::cout << chapterId << " has no parent chapters." << std::endl;
        return;
    }

    std::vector <std::string> parent_chapters = {};
    int done_iterations = 0;
    while (chapterToIterate->parentChapter_ != nullptr
           and done_iterations < iterations) {
        // add parent to parent chapters and get next parent
        chapterToIterate = chapterToIterate->parentChapter_;
        parent_chapters.push_back(chapterToIterate->id_);
        done_iterations++;
    }

    // sort list in alphabetical order by ID
    sort(parent_chapters.begin(), parent_chapters.end());

    std::cout << chapterId << " has " << parent_chapters.size()
              << " parent chapters:" << std::endl;
    for (auto parentChapter : parent_chapters) {
        std::cout << parentChapter << std::endl;
    }
}

// prints parent's subchapters to a level N set by params.
void Book::printSubchaptersN(Params params) const
{
    std::string chapterId = params.at(0);
    Chapter* parent = findChapter(params.at(0));
    int iterations = stoi(params.at(1));


    if (iterations < 1) {
        std::cout << "Error. Level can't be less than 1." << std::endl;
        return;
    } else if (parent == nullptr) {
        std::cout << "Error: Not found: " << chapterId << std::endl;
        return;
    } else if (parent->subchapters_.size() == 0) {
        std::cout << chapterId << " has no subchapters." << std::endl;
        return;
    }

    std::vector <Chapter*> subchapters = {};
    std::vector <std::string> subchaptersId = {};

    // get all subchapters and sort them by id
    subchapters = getAllSubchapters(parent, subchapters, iterations);
    subchaptersId = getSortedIds(subchapters);

    // print all subchapters
    std::cout << chapterId << " has " << subchaptersId.size()
              << " subchapters:" << std::endl;
    for (std::string &id : subchaptersId) {
        std::cout << id << std::endl;
    }
}

// print all subchapters siblingchapters (chapters that share the same parent)
void Book::printSiblingChapters(Params params) const
{
    std::string chapterId = params.at(0);
    Chapter* siblingChapter = findChapter(params.at(0));

    if (siblingChapter == nullptr) {
        std::cout << "Error: Not found: " << chapterId << std::endl;
        return;
    } else if (siblingChapter->parentChapter_ == nullptr) {
        std::cout << chapterId << " has no sibling chapters." << std::endl;
        return;
    }

    // get sibling chapters
    std::vector <Chapter*> &siblingsList = siblingChapter->
                                            parentChapter_->subchapters_;
    std::vector <std::string> siblingsIds = {};

    // sort sibling chapters by id
    siblingsIds = getSortedIds(siblingsList);

    // -1 because subchapter itself does not count to siblingchapters
    std::cout << chapterId << " has " << siblingsIds.size()-1
              << " sibling chapters:" << std::endl;
    for (auto &sibling : siblingsIds) {
        // print if not same as subchapter
        if (sibling != siblingChapter->id_) {
            std::cout << sibling << std::endl;
        }
    }
}

// prints total lenght of all subchapters from given parent
void Book::printTotalLength(Params params) const
{
    std::string chapterId = params.at(0);
    Chapter* parent = findChapter(params.at(0));

    if (parent == nullptr) {
        std::cout << "Error: Not found: " << chapterId << std::endl;
        return;
    }

    // get all subchaptets
   std::vector <Chapter*> chapters = {};
   chapters = getAllSubchapters(parent, chapters);

   int lenght = parent->length_;
   for (auto chapter: chapters) {
       lenght += chapter->length_;
   }
   std::cout << "Total length of " << chapterId << " is " << lenght
             << "." << std::endl;
}

// prints longest chapter from all subchapters from a given parent
void Book::printLongestInHierarchy(Params params) const
{
    std::string chapterId = params.at(0);
    Chapter* parent = findChapter(params.at(0));

    if (parent == nullptr) {
        std::cout << "Error: Not found: " << chapterId << std::endl;
        return;
    }

   std::vector <Chapter*> chapters = {};
   chapters = getAllSubchapters(parent, chapters);

   // form pair with info from parent chapter
   std::pair <std::string, int> longestChapter = {parent->id_, parent->length_};
   for (auto chapter: chapters) {
       if (chapter->length_ > longestChapter.second) {
           longestChapter = {chapter->id_, chapter->length_};
        }
    }

   if (longestChapter.second > parent->length_) {
       std::cout << "With the length of " << longestChapter.second << ", "
                 << longestChapter.first << " is the longest chapter in "
                 << chapterId<<"'s hierarchy." << std::endl;
   } else {
       std::cout << "With the length of " << parent->length_ << ", "
                 << chapterId <<" is the longest chapter in their hierarchy."
                 << std::endl;
   }
}

// prints shortest chapter from all subchapters from a given parent
void Book::printShortestInHierarchy(Params params) const
{
    std::string chapterId = params.at(0);
    Chapter* parent = findChapter(params.at(0));

    if (parent == nullptr) {
        std::cout << "Error: Not found: " << chapterId << std::endl;
        return;
    }

   std::vector <Chapter*> chapters = {};
   chapters = getAllSubchapters(parent, chapters);

  // form pair with info from parent chapter
   std::pair <std::string, int> shortestChapter = {parent->id_, parent->length_};
   for (auto chapter: chapters) {
       if (chapter->length_ < shortestChapter.second) {
           shortestChapter = {chapter->id_, chapter->length_};
        }
    }

   // print shortest
   if (shortestChapter.second < parent->length_) {
       std::cout << "With the length of " << shortestChapter.second << ", "
                 << shortestChapter.first << " is the shortest chapter in "
                 << chapterId<<"'s hierarchy." << std::endl;
   } else {
       std::cout << "With the length of " << parent->length_ << ", "
                 << chapterId <<" is the shortest chapter in their hierarchy."
                 << std::endl;
   }
}

// do not implement
void Book::printParent(Params params) const
{
    params.size();
}

// do not implement
void Book::printSubchapters(Params params) const
{
    // just to get rid of complier warning
    params.size();
}

// finds pointer for chapter id
Chapter *Book::findChapter(const std::string &id) const
{
    if (bookChapters.find(id) != bookChapters.end()) {
        // return pointer
        Chapter* returnchap = *(&bookChapters.at(id));
        return returnchap;
    } else {
        // not found, return nullptr
        return nullptr;
    }
}


