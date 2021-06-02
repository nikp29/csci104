#include "Hashtable.h"
#include "avlbst.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string processWord(string s) {
    string new_string = "";  // strip bad text, make lowercase
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            new_string = new_string + ((char)tolower(s[i]));
        }
    }
    return new_string;
}

int main(int argc, char** argv) {
    srand((unsigned)time(0));

    if (argc < 6) {
        cout << "please specify a input file, output file, probing mode, debug mode, and num_repetitions";
        return 0;
    }

    clock_t start;
    double duration;

    ifstream ifile(argv[1]);
    ofstream ofile(argv[2]);
    int probing = atoi(argv[3]);
    bool debug = atoi(argv[4]);
    int r = atoi(argv[5]);
    int num_words = 0;
    vector<string> words;
    string word;
    while (ifile >> word
           && (argc > 6 ? (num_words < atoi(argv[6]))
                        : true)) {  // this is for debug purposes only. you can provide an optional 7th argument that
                                    // takes only n words from the input file
        words.push_back(processWord(word));
        num_words++;
    }
    start = clock();
    if (probing == 3) {  // make an avl
        for (int n = 0; n < r; n++) {
            AVLTree<string, int> data;
            for (int i = 0; i < words.size(); i++) {
                if (data.find(words[i]) == data.end()) {  // if word not in avl, insert
                    data.insert(pair<string, int>(words[i], 1));
                } else {  // if word in avl, update
                    data.find(words[i])->second = data.find(words[i])->second + 1;
                }
            }
        }
        duration = (clock() - start) / (double)CLOCKS_PER_SEC;
        // now print to output
        AVLTree<string, int> data;
        for (int i = 0; i < words.size(); i++) {
            if (data.find(words[i]) == data.end()) {  // if word not in avl, insert
                data.insert(pair<string, int>(words[i], 1));
            } else {  // if word in avl, update
                data.find(words[i])->second = data.find(words[i])->second + 1;
            }
        }
        for (AVLTree<string, int>::iterator it = data.begin(); it != data.end(); ++it) {
            ofile << it->first << " " << it->second << endl;
        }
    } else {
        for (int n = 0; n < r; n++) {
            Hashtable data(debug, probing);
            for (int i = 0; i < words.size(); i++) {
                data.add(words[i]);
            }
        }
        duration = (clock() - start) / (double)CLOCKS_PER_SEC;
        // now print to output
        Hashtable data(debug, probing);
        for (int i = 0; i < words.size(); i++) {
            data.add(words[i]);
        }
        data.reportAll(ofile);
    }

    cout << duration / r << endl;
    // this is for data recording purposes only, and will be commented
    // ofstream results;
    // results.open("timingResults.csv", ios_base::app);
    // results << atoi(argv[6]) << "," << r << ","
    //         << (probing == 0 ? "linear"
    //                          : (probing == 1   ? "quadratic"
    //                             : probing == 2 ? "double_hashing"
    //                                            : "AVL"))
    //         << "," << boolalpha << debug << "," << duration / r << endl;
}