#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <set>
#include <string>

/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template<typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2) {
    std::set<T> si;
    for (typename std::set<T>::iterator it = s2.begin(); it != s2.end(); ++it) {
        if (s1.find(*it) != s1.end()) {
            si.insert(*it);
        }
    }
    return si;
}
template<typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2) {
    std::set<T> su;
    // first copy everything into su from s1
    for (typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it) {
        su.insert(*it);  // find takes log(n) so the function's runtime will be nlog(n)
    }
    // then copy everything not currently in su from s2
    for (typename std::set<T>::iterator it = s2.begin(); it != s2.end(); ++it) {
        if (su.find(*it) == su.end()) {  // find takes log(n) so the function's runtime will be nlog(n)
            su.insert(*it);
        }
    }
    return su;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string& ltrim(std::string& s);

// Removes any trailing whitespace
std::string& rtrim(std::string& s);

// Removes leading and trailing whitespace
std::string& trim(std::string& s);
#endif