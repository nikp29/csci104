#include "util.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>

using namespace std;

bool isPunctuation(char c);  // delete b4 submit

// int main() {
//     std::set<std::string> s1 = parseStringToWords("s hi hi123 whats up uzi");
//     std::set<std::string> s2 = parseStringToWords("s uzi joe");
//     std::set<std::string> su = setIntersection(s1, s2);
//     for (std::set<std::string>::iterator itr = su.begin(); itr != su.end(); itr++) {
//         cout << *itr << " ";
//     }
//     cout << endl;
//     return 0;
// }
std::string convToLower(std::string src) {
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords) {
    std::set<std::string> words;
    std::string current_word;
    bool have_word = false;  // variable to track if we are currently parsing over a legit word
    // steps through string
    for (std::string::iterator it = rawWords.begin(); it != rawWords.end(); ++it) {
        std::string::iterator next = it;
        ++next;
        if (have_word == false && (isalpha(*it) || isdigit(*it))) {  // if we see the first letter in a word
            current_word = current_word + *it;
            // start adding characters to our current word var, and set have worder tracker to true
            have_word = true;
        } else if (have_word == true) {
            // if we currently have word and see a punctuation, that means the word is done
            if ((!isalpha(*it) && !isdigit(*it))) {
                // if word is 2 or longer char, save it
                if (current_word.size() > 1) {
                    words.insert(convToLower(current_word));
                }
                // reset have word and current word
                current_word = "";
                have_word = false;
            } else if (next == rawWords.end()) {
                // if this is the last char in string, save word if it is long enough
                current_word = current_word + *it;
                if (current_word.size() > 1) {
                    words.insert(convToLower(current_word));
                }
            } else {
                // else we're not done with the word, keep adding characters to it
                current_word = current_word + *it;
            }
        }
    }
    // return words
    return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string& ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string& rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string& trim(std::string& s) { return ltrim(rtrim(s)); }
