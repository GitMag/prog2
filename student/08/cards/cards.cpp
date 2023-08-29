#include "cards.hh"

// constructor
Cards::Cards(): top_(nullptr){

}

// destructor
Cards::~Cards() {
    while (top_ != nullptr) {
        break;
    }
}

void Cards::add(const int id) {

    Card_data* new_item = new Card_data{id, nullptr};

    if (top_ == nullptr ) {
        top_ = new_item;
    } else {
        Card_data* old_item = top_;
        top_ = new_item;
        top_->next = old_item;

    }
}

Card_data* Cards::get_topmost() {
    return top_;
}

void Cards::print_from_bottom_to_top(std::ostream& s) {
    s << "";
    return;
}


bool Cards::remove(int& id) {
    if (top_ == nullptr) {
        return false;
    }

     Card_data* to_be_removed= top_;
     top_ = top_->next;

     id = to_be_removed->data;
     delete to_be_removed;

     return true;
}

bool Cards::top_to_bottom() {


    if (top_->next == nullptr or top_ == nullptr) {
        return false;
    }
    // set old top point to nullptr
    Card_data* old_top = top_;
    top_ = top_->next;
    old_top->next = nullptr;

    // new top is next in deck

    // iterate and find last card in deck
    Card_data* item_to_be_printed = top_;

    while (item_to_be_printed != nullptr) {
        if (item_to_be_printed->next != nullptr) {
            item_to_be_printed = item_to_be_printed->next;
        } else {
            // set pointer to the correct one
            item_to_be_printed->next = old_top;
            break;
        }
    }

    return true;

}
// moves bottom card to top
bool Cards::bottom_to_top() {
   Card_data* item_to_be_printed = top_;

   // check if deck contains atleast 2 cards
   if (item_to_be_printed == nullptr) {
       return false;
   }

   // find last card
   while (item_to_be_printed != nullptr) {
       if (item_to_be_printed->next != nullptr) {
           item_to_be_printed = item_to_be_printed->next;
       } else {
           // last item
           break;
       }
   }

   // set last card to first card
   Card_data* last_card= item_to_be_printed;
   last_card->next = top_;
   top_ = last_card;

  item_to_be_printed = top_;


  // find last card and set its pointer to nullptr
   while (item_to_be_printed != nullptr) {
       if (item_to_be_printed->next != top_) {
           item_to_be_printed = item_to_be_printed->next;
       } else {
           // set nullpointer
           item_to_be_printed->next = nullptr;
           break;
       }
   }

   return true;
}

void Cards::print_from_top_to_bottom(std::ostream& s) {
    Card_data* item_to_be_printed = top_;

    if (item_to_be_printed != nullptr) {
    }
    int running_number = 1;

    while ( item_to_be_printed != nullptr ) {
       s << running_number << ": " << item_to_be_printed->data << std::endl;
       ++running_number;
       item_to_be_printed = item_to_be_printed->next;
    }
}
