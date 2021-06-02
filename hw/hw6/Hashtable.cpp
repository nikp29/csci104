#include "Hashtable.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// make sure to set  srand((unsigned) time(0)); in main

Hashtable::Hashtable(bool debug, unsigned int probing)
        : debug_(debug), probing_(probing), size_step(0), num_occupied(0) {
    r[0] = 983132572;
    r[1] = 62337998;
    r[2] = 552714139;
    r[3] = 984953261;
    r[4] = 261934300;
    vector<pair<string, int>*> new_table;
    int size = m();
    for (int i = 0; i < size; i++) {
        new_table.push_back(nullptr);
    }
    table = new_table;
    make_rands();
}
Hashtable::~Hashtable() {
    for (int i = 0; i < table.size(); i++) {
        if (table[i]) {
            delete table[i];
            table[i] = nullptr;
        }
    }
}
void Hashtable::make_rands() {
    if (!debug_) {
        r[0] = rand() % m();  // each goes from 0-(m-1)
        r[1] = rand() % m();
        r[2] = rand() % m();
        r[3] = rand() % m();
        r[4] = rand() % m();
    }
}
int Hashtable::m() const {
    const static int m_steps[]
            = {11,       23,       47,       97,        197,       397,       797,       1597,      3203,    6421,
               12853,    25717,    51437,    102877,    205759,    411527,    823117,    1646237,   3292489, 6584983,
               13169977, 26339969, 52679969, 105359969, 210719881, 421439783, 842879579, 1685759167};
    return m_steps[size_step];
}
int Hashtable::p() const {
    const static int p_steps[]
            = {7,        19,       43,       89,        193,       389,       787,       1583,      3191,    6397,
               12841,    25703,    51431,    102871,    205721,    411503,    823051,    1646221,   3292463, 6584957,
               13169963, 26339921, 52679927, 105359939, 210719881, 421439749, 842879563, 1685759113};
    return p_steps[size_step];
}
double Hashtable::load_factor() { return ((double)num_occupied) / ((double)m()); }
int Hashtable::char_to_int(char c) const {
    // takes a lower case character c, and converts it into an int where a = 0
    return ((int)tolower(c)) - ((int)'a');  // also makes char lowercase
}
int Hashtable::hash(string k) const {
    int string_index = k.length() - 1;
    long long words[5];
    for (int i = 4; i >= 0; i--) {  // for each word
        long long w = 0;
        for (int j = 0; j < 6; j++) {

            if (string_index != -1) {
                // calculate the proper number n stuff and add it to the current
                w += ((long long)pow(26, j)) * ((long long)char_to_int(k[string_index]));  // make lower and get int
                string_index--;
            }
        }
        // insert the 6 letter groupings (words) from back of the array to the front
        words[i] = w;
    }
    // multiply the 5 words by the rand numbers
    long long rand_sum = 0;
    for (int i = 0; i < 5; i++) {
        rand_sum += ((long long)r[i]) * words[i];
    }
    // do the modulo operation on the sum of the words*rands
    long long hash_ = rand_sum % ((long long)m());
    int to_return = (int)hash_;
    return to_return;
}
int Hashtable::hash2(string k) const {
    int string_index = k.length() - 1;
    long long words[5];
    for (int i = 4; i >= 0; i--) {  // for each word
        long long w = 0;
        for (int j = 0; j < 6; j++) {

            if (string_index >= 0) {
                // calculate the proper number n stuff and add it to the current
                w += pow(26, j) * char_to_int(k[string_index]);
            }
            string_index--;
        }
        // insert the 6 letter groupings (words) from back of the array to the front
        words[i] = w;
    }
    // sum the words
    long long sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += words[i];
    }
    // do the modulo operation on the sum of the words
    long long hash_ = p() - sum % ((long long)p());
    int to_return = (int)hash_;
    return to_return;
}
int Hashtable::probe_index(int h1, int i, int h2) const {
    if (probing_ == 0)
        return (h1 + i) % m();  // linear probing
    else if (probing_ == 1)
        return (h1 + (i * i)) % m();  // quadratic probing
    else
        return (h1 + i * h2) % m();  // double hashing
}
int Hashtable::count(string k) {
    int hash_ = hash(k);  // get both hashes
    int hash2_ = hash2(k);

    int i = 0;                                  // set probing number to 0
    int index = probe_index(hash_, i, hash2_);  // find starting index
    while (table[index]) {                      // if we encounter a null value just
                                                // stop so we can return 0
        if (table[index]->first == k) {         // if key matches return value
            return table[index]->second;
        }
        i++;  // get next index
        index = probe_index(hash_, i, hash2_);
    }
    return 0;
}
void Hashtable::insert(string k) {
    int hash_ = hash(k);  // get both hashes
    int hash2_ = hash2(k);

    int i = 0;                                          // set probing number to 0
    int index = probe_index(hash_, i, hash2_);          // find starting index
    while (table[index] && table[index]->first != k) {  // iterate through the table till either we find a place to
                                                        // insert or that it has already been inserted
        i++;                                            // get next index
        index = probe_index(hash_, i, hash2_);
    }
    if (table[index]) {  // if not null that means the key already exists, increment by 1
        table[index]->second = table[index]->second + 1;
    } else {  // if it is null then insert
        table[index] = new pair<string, int>(k, 1);
    }
}
void Hashtable::insert(
        std::pair<std::string, int>* p) {  // this is used only for resizing, instead of a key we provide a pair
    string k = p->first;
    int hash_ = hash(k);  // get both hashes
    int hash2_ = hash2(k);

    int i = 0;                                  // set probing number to 0
    int index = probe_index(hash_, i, hash2_);  // find starting index
    while (table[index]) {                      // iterate through the table till either we find a place to
                                                // insert or that it has already been inserted
        i++;                                    // get next index
        index = probe_index(hash_, i, hash2_);
    }
    table[index] = p;
}
void Hashtable::add(string k) {
    if (load_factor() > .5) {
        resize();
    }
    num_occupied++;
    insert(k);
}
void Hashtable::resize() {
    size_step++;

    vector<pair<string, int>*> prev_table = table;
    // create new table
    vector<pair<string, int>*> new_table;
    int size = m();

    for (int i = 0; i < size; i++) {  // fill table
        new_table.push_back(nullptr);
    }
    table = new_table;  // now set hashtable to blank table and fill it with prev table

    for (int i = 0; i < prev_table.size(); i++) {
        if (prev_table[i])
            insert(prev_table[i]);  // if the pointer is allocated move it to the table from the prev table
    }
}
void Hashtable::reportAll(ostream& o) const {
    for (int i = 0; i < m(); i++) {
        if (table[i]) {  // if it is occupied, print
            o << table[i]->first << " " << table[i]->second << endl;
        }
    }
}