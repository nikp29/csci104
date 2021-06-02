#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "please specify a train, classify, and output file";
        return 0;
    }

    ifstream tfile(argv[1]);
    stringstream ss;
    string line;
    ifstream cfile(argv[2]);
    ofstream ofile(argv[3]);
    int n_train;  // number of train lines
    getline(tfile, line);
    ss << line;
    ss >> n_train;
    // create map with fruit name,
    // and value is map of descriptors and counts for those descriptors
    map<string, map<string, int>> train;  // a map for the numbers of fruits with each trait
    map<string, int> train_counts;        // a map for the total number of fruits
    map<string, int> trait_counts;        // a map for the total number of traits
    set<string> fruits;                   // a set of all the fruits
    set<string> traits;                   // a set of all the traits
    for (int i = 0; i < n_train; i++) {
        getline(tfile, line);
        stringstream ss2(line);
        string fruit;
        ss2 >> fruit;

        if (train.find(fruit) == train.end()) {
            // fruit not in map yet
            fruits.insert(fruit);
            map<string, int> fruit_map;
            train_counts.insert(pair<string, int>(fruit, 1));
            train.insert(pair<string, map<string, int>>(fruit, fruit_map));
        } else {
            // if fruit already in map add 1 to fruit count
            train_counts[fruit]++;
        }
        // get all the traits for this fruit and record them
        string trait;
        set<string> current_traits;
        while (ss2 >> trait) {                                       // n where n = number of traits
            if (current_traits.find(trait) == current_traits.end())  // to ignore duplicate traits
            {
                current_traits.insert(trait);
                if (traits.find(trait) == traits.end()) {
                    traits.insert(trait);
                }
                if (train[fruit].find(trait) == train[fruit].end()) {  // logn
                    // trait is not in that fruit's map
                    train[fruit].insert(pair<string, int>(trait, 1));
                } else {
                    // if trait already in fruit's map add it
                    train[fruit][trait]++;
                }
                if (trait_counts.find(trait) == trait_counts.end()) {
                    // if trait not already in traits map add it
                    trait_counts.insert(pair<string, int>(trait, 1));
                } else {
                    // if trait already in traits map increment that trait by 1
                    trait_counts[trait]++;
                }
            }
        }
    }
    map<string, double> p_fruit;  // key is fruit, value is probability of that fruit occurring
    for (set<string>::iterator it2 = fruits.begin(); it2 != fruits.end(); ++it2) {
        p_fruit[*it2] = ((double)((double)train_counts[*it2]) / ((double)n_train));
    }
    map<string, double> p_not_fruit;  // key is fruit value is the probability of that fruit not occurring
    for (set<string>::iterator it2 = fruits.begin(); it2 != fruits.end(); ++it2) {
        p_not_fruit[*it2] = ((double)((double)(n_train - train_counts[*it2])) / ((double)n_train));
    }

    map<string, map<string, double>> p_trait_given_fruit;
    for (set<string>::iterator it2 = fruits.begin(); it2 != fruits.end(); ++it2) {
        // for each of the traits, calculate the probability of that trait given the fruit for each fruit
        // iterate through fruits
        map<string, double> p_traits;  // all probabilities of that trait for the current fruits
        p_trait_given_fruit.insert(pair<string, map<string, double>>(*it2, p_traits));
        for (set<string>::iterator it = traits.begin(); it != traits.end();
             ++it)  // these two for loops together will run what is in the loop ~ n times
        {
            p_trait_given_fruit[*it2].insert(pair<string, double>(
                    *it,
                    ((double)((double)train[*it2][*it]) + ((double)1))
                            / (((double)1) + ((double)train_counts[*it2]))));  // lapaccian
        }
    }

    map<string, map<string, double>> p_trait_given_not_fruit;  // probability of that trait for all other fruits
    for (set<string>::iterator it2 = fruits.begin(); it2 != fruits.end(); ++it2) {
        // for each of the traits, calculate the probability of that trait given the fruit for each fruit
        // iterate through fruits
        map<string, double> p_traits;  // all probabilities of that trait for the current fruits
        p_trait_given_not_fruit.insert(pair<string, map<string, double>>(*it2, p_traits));
        for (set<string>::iterator it = traits.begin(); it != traits.end();
             ++it)  // these two for loops together will run what is in the loop ~ n times
        {
            p_trait_given_not_fruit[*it2].insert(pair<string, double>(
                    *it,
                    ((double)((double)(trait_counts[*it] - train[*it2][*it]))
                     + ((double)1))  // trait_counts[*it] - train[*it2][*it] is the number of fruits that arent *it that
                                     // have that trait
                            / (((double)1)
                               + ((double)(n_train - train_counts[*it2])))));  // lapaccian , n_train -
                                                                               // train_counts[*it2] is the number of
                                                                               // fruits that arent *it2
        }
    }

    // now on to classifying
    int n_classify;
    getline(cfile, line);
    stringstream ss2(line);
    ss2 >> n_classify;
    for (int i = 0; i < n_classify; i++) {
        // first calculate the probability of all the traits
        getline(cfile, line);
        // there are 2 parts to p, the numerator which is p = p(e|f)*p(f) and the p_not = p(e|not f)*p(not f) so the
        // denom is p+p_not
        string most_likely;
        double p_most_likely = 0;
        for (set<string>::iterator it2 = fruits.begin(); it2 != fruits.end(); ++it2) {
            map<string, double> p_traits_for_fruit = p_trait_given_fruit[*it2];
            map<string, double> p_not_traits_for_fruit = p_trait_given_not_fruit[*it2];
            double p = p_fruit[*it2];          // p will eventually p_fruit * p trait1 | fruit * p trait2 | fruit ...
                                               // currently is probabiliy p(is *it2)
            double p_not = p_not_fruit[*it2];  // p_not will eventually p_not_fruit * p trait1 | not_fruit * p trait2 |
                                               // not_fruit ..., currently is p(not *it2)
            stringstream ss3(line);
            string trait;
            set<string> current_traits;  // to ignore duplicate traits
            while (ss3 >> trait) {
                if (current_traits.find(trait) == current_traits.end())  // to ignore duplicate traits
                {
                    current_traits.insert(trait);
                    // calculate the probability the fruit is *it2 given traits
                    double p_ = p_traits_for_fruit.find(trait) == p_traits_for_fruit.end()
                                        ? ((double)1) / (((double)1) + ((double)train_counts[*it2]))
                                        : p_traits_for_fruit[trait];
                    // calculate the probability the fruit is not *it2 given traits
                    double p_not_ = p_not_traits_for_fruit.find(trait) == p_not_traits_for_fruit.end()
                                            ? ((double)1) / (((double)1) + ((double)(n_train - train_counts[*it2])))
                                            : p_not_traits_for_fruit[trait];
                    p = p * p_;
                    p_not = p_not * p_not_;
                }
            }
            double p_final = p / (p + p_not);
            if (p_final > p_most_likely) {
                p_most_likely = p_final;
                most_likely = *it2;
            }
        }
        // because you guys didnt want the to be a newline at the end of our output file
        if (i != n_classify - 1) {
            ofile << most_likely << endl;
        } else {
            ofile << most_likely;
        }
    }
    ofile.close();
    return 0;
}