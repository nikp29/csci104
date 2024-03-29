/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even
numbers and the other contains the odd numbers. Students
will receive no credit for non-recursive solutions.
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens) {
    // recursively go through all the items until you reach the end of the list, switching odd and even every time
    if (in->next) {
        split(in->next, evens, odds);
    }
    // take in and set it as the first link in odds
    in->next = odds;
    odds = in;
}