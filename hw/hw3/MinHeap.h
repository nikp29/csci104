#ifndef MINHEAP_H
#define MINHEAP_H
#include <stdexcept>
#include <utility>  // std::pair, std::make_pair
#include <vector>

template<class T>
class MinHeap {
public:
    MinHeap(int d);
    /* Constructor that builds a d-ary Min Heap
       This should work for any d >= 2,
       but doesn't have to do anything for smaller d.*/

    ~MinHeap() {}

    void add(T item, int priority);
    /* adds the item to the heap, with the given priority. */

    const T& peek() const;
    /* returns the element with smallest priority.
       Break ties however you wish.
       Throws an exception if the heap is empty. */

    void remove();
    /* removes the element with smallest priority.
       Break ties however you wish.
       Throws an exception if the heap is empty. */

    std::vector<std::pair<T, int>> getHeap();
    bool isEmpty();
    /* returns true iff there are no elements on the heap. */

private:
    // whatever you need to naturally store things.
    // You may also add helper functions here.
    std::vector<std::pair<T, int>> heap_arr;
    int max_children_;
    void trickleUp(int loc);
    void trickleDown(int loc);
};

template<class T>
MinHeap<T>::MinHeap(int d) : max_children_(d) {
    // throw error if trying to create a heap with a tree with a max of <2 children
    if (d < 2)
        throw std::invalid_argument("heap can only be 2 or greater - ary");
}

// template<class T>
// MinHeap<T>::~MinHeap() {}

template<class T>
std::vector<std::pair<T, int>> MinHeap<T>::getHeap() {
    return heap_arr;
}

template<class T>
void MinHeap<T>::add(T item, int priority) {
    // add to back of array
    heap_arr.push_back(std::make_pair(item, priority));
    // take this node and trickle it up
    trickleUp(heap_arr.size() - 1);
}

template<class T>
bool MinHeap<T>::isEmpty() {
    // we know the heap is empty of the vector size is xero
    return (heap_arr.size() == 0);
}

template<class T>
const T& MinHeap<T>::peek() const {
    // return the first item in the heap if such an item exists
    if (heap_arr.size() == 0) {
        throw std::length_error("empty heap, you can't peek an empty heap");
    }
    return heap_arr[0].first;
}

template<typename T>
void MinHeap<T>::remove() {
    // swap the first and last elements
    std::pair<T, int> temp = heap_arr[heap_arr.size() - 1];
    heap_arr[heap_arr.size() - 1] = heap_arr[0];
    heap_arr[0] = temp;
    // delete last (previously min) element
    heap_arr.pop_back();
    trickleDown(0);
    // trickleDown the element at the top
}

template<typename T>
void MinHeap<T>::trickleUp(int loc) {
    // get the parent loc
    int parent = (loc - 1) / max_children_;
    while (parent >= 0 && heap_arr[loc].second < heap_arr[parent].second) {
        // swap parent with loc, update loc to parent and update parent
        // until we reach the top or loc is less than its parent
        std::pair<T, int> temp = heap_arr[parent];
        heap_arr[parent] = heap_arr[loc];
        heap_arr[loc] = temp;
        loc = parent;
        parent = (loc - 1) / max_children_;
    }
}

template<typename T>
void MinHeap<T>::trickleDown(int loc) {
    // get the child loc
    int child = loc * max_children_ + 1;
    while ((unsigned int)child < heap_arr.size() && heap_arr[loc].second > heap_arr[child].second) {
        // swap child with loc, update loc to child and update child
        // until we reach the top or loc is more than than its child
        int min_loc = 0;
        int min = INT8_MAX;
        for (int i = 0; i < max_children_; i++) {
            if (child + i < heap_arr.size() && min > heap_arr[child + i].second) {
                min = heap_arr[child + i].second;
                min_loc = child + i;
            }
        }
        child = min_loc;
        std::pair<T, int> temp = heap_arr[child];
        heap_arr[child] = heap_arr[loc];
        heap_arr[loc] = temp;
        loc = child;
        child = loc * max_children_ + 1;
    }
}

#endif