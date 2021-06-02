#include "db_parser.h"
#include "mydatastore.h"
#include "product.h"
#include "product_parser.h"
#include "util.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) { return (p1->getName() < p2->getName()); }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;

    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if (parser.parse(argv[1], ds)) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while (!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin, line);
        stringstream ss(line);
        string cmd;
        if ((ss >> cmd)) {
            if (cmd == "AND") {
                string term;
                vector<string> terms;
                while (ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            } else if (cmd == "OR") {
                string term;
                vector<string> terms;
                while (ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            } else if (cmd == "QUIT") {
                string filename;
                if (ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            } else if (cmd == "ADD") {
                // make sure we can get a username and result (the index for which hit we're adding, and that result is
                // valid)
                string username;
                int result;
                if (ss >> username && ss >> result && result > 0 && (unsigned int)result <= hits.size()) {
                    // create error string
                    string error = "";
                    Product* hit = hits[result - 1];
                    // try to add product
                    ds.add_product_to_cart(username, hit, error);
                    // log any error
                    if (error != "") {
                        cout << error << endl;
                    }
                } else {
                    // log error
                    std::cout << "Invalid request" << std::endl;
                }
            } else if (cmd == "VIEWCART") {
                string username;
                // get username to view cart and log errors if fails
                if (ss >> username) {
                    string error = "";
                    vector<Product*> cart_products = ds.view_user_cart(username, error);
                    if (error != "") {
                        cout << error << endl;
                    } else {
                        displayProducts(cart_products);
                    }
                } else {
                    cout << "Invalid username" << endl;
                }
            } else if (cmd == "BUYCART") {
                // get username
                string username;
                if (ss >> username) {
                    string error = "";
                    // run buy_cart, if there is a problem buy_cart will cout invalid username
                    ds.buy_cart(username, error);
                    if (error != "") {
                        cout << error << endl;
                    }
                } else {
                    cout << "Invalid username" << endl;
                }
            }

            else {
                cout << "Unknown command" << endl;
            }
        }
    }
    return 0;
}

void displayProducts(vector<Product*>& hits) {
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
        cout << "No results found!" << endl;
        return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for (vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
