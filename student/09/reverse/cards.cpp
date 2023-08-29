#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ), bottom_(nullptr) {
}


void Cards::add(int id) {

    // set bottom card if only one card exists
    if (top_ == nullptr) {
        std::shared_ptr<Card_data> new_card
                = std::make_shared<Card_data>(Card_data{id, top_, top_});
        bottom_ = new_card;

    }

    std::shared_ptr<Card_data> old_card = top_;
    std::shared_ptr<Card_data> new_card
            = std::make_shared<Card_data>(Card_data{id, top_, old_card});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int& id) {
    if (top_ == nullptr) {
        return false;
    }

    id = top_->data;
    top_ = top_->next;

     return true;
}


// invert card stack
void Cards::reverse()
{
    std::shared_ptr<Card_data> to_be_printed = top_;
    int nr = 1;

    while( to_be_printed != 0 ) {
       to_be_printed = to_be_printed->next;
       ++nr;
    }
}

// Tip for writing code more efficiently:
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp
