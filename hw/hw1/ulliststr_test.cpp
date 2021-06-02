/* Write your test code for the ULListStr in this file */

#include "ulliststr.h"
#include <iostream>
using namespace std;

/* To test the ULListstr class, please enter a test mode. Test modes are as follows
 * 0: push_back()
 * 1: push_front()
 * 2: pop_back()
 * 3: pop_front()
 * 4: back()
 * 5: front() */

int main(int argc, char* argv[]) {
    ULListStr dat;

    // push_back checks
    dat.push_back("test1");
    cout << boolalpha << "push_back to empty list check: " << ("test1" == dat.back()) << endl;
    dat.push_back("test2");
    cout << boolalpha << "push_back to list with space in tail item check: " << ("test2" == dat.back()) << endl;
    dat.pop_back();
    dat.pop_back();
    dat.push_front("ignore");
    dat.push_back("test3");
    cout << boolalpha << "push_back to list where tail has no space at the end check: " << ("test3" == dat.back())
         << endl;
    // clear list
    dat.pop_back();
    dat.pop_back();
    cout << boolalpha << "empty list check: " << (dat.size() == 0) << endl;

    // push_front checks
    dat.push_front("test1");
    cout << boolalpha << "push_front to empty list check: " << ("test1" == dat.front()) << endl;
    dat.push_front("test2");
    cout << boolalpha << "push_front to list with space in head item check: " << ("test2" == dat.front()) << endl;
    dat.pop_back();
    dat.pop_back();
    dat.push_back("ignore");
    dat.push_front("test3");
    cout << boolalpha
         << "push_front to list where head has no space at the front of item check: " << ("test3" == dat.front())
         << endl;
    // clear list
    dat.pop_back();
    dat.pop_back();

    cout << boolalpha << "empty list check: " << (dat.size() == 0) << endl;

    // pop_back checks
    dat.push_back("test1");
    dat.push_back("ignore");
    dat.push_front("test2");
    dat.pop_back();
    cout << boolalpha << "pop_back when there are multiple items left in tail check: " << ("test1" == dat.back())
         << endl;
    dat.pop_back();
    cout << boolalpha << "pop_back when there is one item left in tail check: " << ("test2" == dat.back()) << endl;
    dat.pop_back();
    cout << boolalpha << "pop_back when there is only one item left in list check: " << (0 == dat.size()) << endl;
    dat.pop_back();
    cout << boolalpha << "pop_back when list is empty check: " << (0 == dat.size()) << endl;

    // pop_front checks
    dat.push_front("test1");
    dat.push_front("ignore");
    dat.push_back("test2");
    dat.pop_front();
    cout << boolalpha << "pop_front when there are multiple items left in head check: " << ("test1" == dat.front())
         << endl;
    dat.pop_front();
    cout << boolalpha << "pop_front when there is one item left in head check: " << ("test2" == dat.front()) << endl;
    dat.pop_front();
    cout << boolalpha << "pop_front when there is only one item left in list check: " << (0 == dat.size()) << endl;
    dat.pop_front();
    cout << boolalpha << "pop_front when list is empty check: " << (0 == dat.size()) << endl;

    // front check
    dat.push_back("test1");
    dat.push_back("ignore");
    cout << boolalpha << "front check: " << ((dat.front()) == "test1") << endl;
    // clear list
    dat.pop_back();
    dat.pop_back();

    cout << boolalpha << "empty list check: " << (dat.size() == 0) << endl;

    // back checks
    dat.push_front("test1");
    dat.push_front("ignore");
    cout << boolalpha << "back check: " << ((dat.back()) == "test1") << endl;

    return 0;
}
