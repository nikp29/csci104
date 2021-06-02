#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <vector>

class Hashtable {
public:
    explicit Hashtable(bool debug = false, unsigned int probing = 0);
    ~Hashtable();
    void add(std::string k);
    int count(std::string k);
    void reportAll(std::ostream&) const;

private:
    void resize();
    int hash(std::string k) const;
    int hash2(std::string k) const;
    void insert(std::string k);
    void insert(std::pair<std::string, int>* p);
    int probe_index(int h1, int i, int h2) const;
    void make_rands();
    int m() const;
    int p() const;
    double load_factor();
    int char_to_int(char c) const;
    int num_occupied;
    int probing_;
    int size_step;
    int debug_;
    int r[5];
    std::vector<std::pair<std::string, int>*> table;
};
#endif
