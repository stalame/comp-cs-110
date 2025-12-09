#include <iostream>
#include "cards.hh"

using namespace std;

Cards::Cards(): top_(nullptr)
{
    cout << "constructor" << endl;
}

Cards::~Cards()
{
    cout << "destructor" << endl;
}

void Cards::add(int id){
    std::shared_ptr<Card_data> top_card = std::make_shared<Card_data>(id); // next defaults to nullptr

    // if the first pointer is nullptr, then deck of cards is empty
    if (top_ == nullptr){
        top_ = top_card;
    }

    else{
        std::shared_ptr<Card_data> current = top_; // top card's pointer is currently nullptr

        // replace top card with new top_card and update pointer to old top_card.
        top_card->next = top_;
        top_ = top_card;
    }
}

bool Cards::remove(int& id){
    if(top_ == nullptr){
        return false;
    }

    id = top_->data; // store removed card id
    top_ = top_->next;
    return true;
    // top card is card to be removed
}

void Cards::print_from_top_to_bottom(ostream &s){
    std::shared_ptr<Card_data> printable_ptr = top_;
    int running_number = 1;

    while(printable_ptr){
        s << running_number << ": " << printable_ptr->data << endl;
        printable_ptr = printable_ptr->next;
        running_number++;
    }
}

void Cards::print_from_bottom_to_top(ostream &s){
    recursive_print(top_, s);
}

bool Cards::top_to_bottom(){
    if(top_ == nullptr || top_->next == nullptr){
        return false;
    }

    std::shared_ptr<Card_data> top_ptr = top_; // store old top
    top_ = top_->next; // update top card

    std::shared_ptr<Card_data> current = top_; // start looping through cards
    while(current->next){ // let's traverse to the last node that points to nullptr
        current = current->next;
    }
    current->next = top_ptr;
    top_ptr->next = nullptr;
    return true;
}

void Cards::reverse(){
    std::shared_ptr<Card_data> prev;
    std::shared_ptr<Card_data> current = top_;
    std::shared_ptr<Card_data> next;

    while(current){
        next = current->next; // store next value
        current->next = prev; // reverse pointer
        prev = current; // move prev forward
        current = next; // move current forward
    }

    top_ = prev; // update top card
}

int Cards::recursive_print(std::shared_ptr<Card_data> top, ostream &s){
    // base case: top_ == nullptr
    if(top == nullptr){
        return 0;
    }

    int running_number = recursive_print(top->next, s); // print rest of the list first

    running_number++; // increment for current node
    s << running_number << ": " << top->data << endl; // print current node

    return running_number;
}
