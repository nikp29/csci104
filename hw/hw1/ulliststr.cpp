#include "ulliststr.h"

#include <cstddef>
#include <stdexcept>

ULListStr::ULListStr() {
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

ULListStr::~ULListStr() { clear(); }

bool ULListStr::empty() const { return size_ == 0; }

size_t ULListStr::size() const { return size_; }

void ULListStr::set(size_t loc, const std::string& val) {
    std::string* ptr = getValAtLoc(loc);
    if (ptr == NULL) {
        throw std::invalid_argument("Bad location");
    }
    *ptr = val;
}

std::string& ULListStr::get(size_t loc) {
    std::string* ptr = getValAtLoc(loc);
    if (ptr == NULL) {
        throw std::invalid_argument("Bad location");
    }
    return *ptr;
}

std::string const& ULListStr::get(size_t loc) const {
    std::string* ptr = getValAtLoc(loc);
    if (ptr == NULL) {
        throw std::invalid_argument("Bad location");
    }
    return *ptr;
}

void ULListStr::clear() {
    while (head_ != NULL) {
        Item* temp = head_->next;
        delete head_;
        head_ = temp;
    }
    tail_ = NULL;
    size_ = 0;
}

void ULListStr::push_back(const std::string& val) {
    if (tail_) {                       // if the list isn't empty
        if (tail_->last == ARRSIZE) {  // if tail is full
            // create new tail
            Item* next_tail = new Item();
            next_tail->prev = tail_;
            tail_->next = next_tail;
            tail_ = next_tail;
        }
    } else {  // list is empty
        tail_ = new Item();
        head_ = tail_;
    }
    // append string onto end of val arr, update size and last
    tail_->val[tail_->last] = val;
    tail_->last += 1;
    size_ += 1;
}

void ULListStr::push_front(const std::string& val) {
    if (head_) {                  // if head exists
        if (head_->first == 0) {  // if the there is no space in the front of head
            // create new head
            Item* next_head = new Item();
            next_head->next = head_;
            head_->prev = next_head;
            head_ = next_head;
            head_->first = ARRSIZE;
            head_->last = ARRSIZE;
        }
    } else {  // list is empty
        tail_ = new Item();
        head_ = tail_;
        head_->first = ARRSIZE;
        head_->last = ARRSIZE;
    }
    // push string to front of val arr, update size and front
    head_->first -= 1;
    head_->val[head_->first] = val;
    size_ += 1;
}

void ULListStr::pop_back() {
    if (tail_) {
        // remove last element
        tail_->last -= 1;
        size_ -= 1;
        if (tail_->first == tail_->last) {  // if tail is empty delete the tail
            if (head_ == tail_) {           // if its the only item in the array  set head and tail to null
                head_ = NULL;
                delete tail_;
                tail_ = NULL;
            } else {  // else set the item before tail to tail
                Item* new_tail = tail_->prev;
                new_tail->next = NULL;
                delete tail_;
                tail_ = new_tail;
            }
        }
    }
}

void ULListStr::pop_front() {
    if (head_) {                            // if there is a tail element
        head_->first += 1;                  // remove the element from the list
        size_ -= 1;                         // update size
        if (head_->first == head_->last) {  // head is empty, delete head
            if (head_ == tail_) {           // if its the only item in the array  set head and tail to null
                head_ = NULL;
                delete tail_;
                tail_ = NULL;
            } else {  // LList has more than 1 item, remove head from list
                Item* new_head = head_->next;
                new_head->prev = NULL;
                delete head_;
                head_ = new_head;
            }
        }
    }
}

std::string const& ULListStr::front() const { return head_->val[head_->first]; }

std::string const& ULListStr::back() const { return tail_->val[tail_->last - 1]; }

std::string* ULListStr::getValAtLoc(size_t loc) const {
    if (head_) {                    // if list isn't empty
        Item* currentItem = head_;  // set head as current item
        while (loc >= (currentItem->last - currentItem->first)) {
            /* if loc is greater than or equal the number of elements in the current item, set the current head to the
             * next item until we find the item that contains the desired value */
            if (currentItem->next == NULL) {
                // if the next item is NULL, the specified index does not have an associated object, thus return null
                return NULL;
            }
            loc -= (currentItem->last - currentItem->first);  // substract the number of items in currentItem from loc
            currentItem = currentItem->next;                  // set currentItem to the next item
        }
        return &(currentItem->val[loc + currentItem->first]);  // return the correct value
    }
    return NULL;
}