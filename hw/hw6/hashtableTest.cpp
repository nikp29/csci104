//
// Created by deoca on 4/18/2021.
//

#include "Hashtable.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * add specified combos to a hashtable
 * @param Letters the letters to make permutations from
 * @param s Add an empty string
 * @param depth The maximum number of letters to add to the hashtable (starts to take a really long time for depth>5)
 * @param ht Hashtable to add to
 */
void addCombos(vector<char>& letters, string& s, int depth, Hashtable& ht) {
    if (!depth) {
        return;
    }

    for (char c : letters) {
        string newS(s);
        newS += c;
        ht.add(newS);
        addCombos(letters, newS, depth - 1, ht);
    }
}

// ./<executable name> <optional filename>
int main(int argc, char** argv) {
    vector<char> letters;
    for (char i = 'a'; i <= 'z'; i++) {
        letters.push_back(i);
    }

    int probeType = (argc >= 3) ? atoi(argv[2]) : 0;
    if (probeType < 0 || probeType > 2) {
        probeType = 0;
    }

    Hashtable ht(true, probeType);
    string s = "";
    addCombos(letters, s, 2, ht);

    ofstream oFile((argc >= 2) ? argv[1] : "output.txt");
    oFile << "probe type: " << probeType << endl;
    ht.reportAll(oFile);
    oFile.close();

    // cout << endl;
    // ht.debugReport();
    return 0;
}