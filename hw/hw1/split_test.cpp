#include "split.h"
#include <cstddef>  // Note: I only added this line here because I was getting errors with the NULL term without it
#include <iostream>
using namespace std;

void printList(Node*& list) {
    cout << list->value << " ";
    if (list->next) {
        printList(list->next);
    }
}

int main() {
    Node* linked_list = new Node(10, NULL);
    for (int i = 9; i > 0; i--) {
        Node* temp = new Node(i, linked_list);
        linked_list = temp;
    }
    Node* odds = NULL;
    Node* evens = NULL;
    split(linked_list, odds, evens);
    printList(odds);
    cout << endl;
    printList(evens);
}