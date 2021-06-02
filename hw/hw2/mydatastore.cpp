#include "mydatastore.h"

#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <map>
#include <set>
#include <string>
#include <vector>

MyDataStore::MyDataStore() {}
MyDataStore::~MyDataStore() {
    // deallocate products, users, keyword product mapping vectors and carts product vectors
    for (std::vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        delete *it;
    }
    for (std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        delete it->second;
    }
    for (std::map<std::string, std::vector<Product*>*>::iterator it = carts_.begin(); it != carts_.end(); ++it) {
        delete it->second;
    }
    for (std::map<std::string, std::set<Product*>*>::iterator it = keywordMappings_.begin();
         it != keywordMappings_.end();
         ++it) {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p) {
    // adds product to the products_ vector
    products_.push_back(p);
    std::set<std::string> keywords = p->keywords();
    // creates a set of keywords, iterates through it and checks if that keyword is a key in keyword mappings, if not it
    // adds key, then adds product to that keyword's vector
    for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
        if (keywordMappings_.find(*it) == keywordMappings_.end()) {
            keywordMappings_[*it] = new std::set<Product*>;
        }
        keywordMappings_[*it]->insert(p);
    }
}
void MyDataStore::addUser(User* u) {
    // adds user to the users map (key = username, value = user object), this is for quick access when trying to check
    // if a user can buy a product
    users_[u->getName()] = u;
    // creates a cart for the user
    carts_[u->getName()] = new std::vector<Product*>;
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> hits_set;
    if (type == 1) {
        // unions each keyword's associated products until hits_set contians all products
        for (std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it) {
            if (keywordMappings_.find(*it) != keywordMappings_.end()) {  // if keyword has products associated with it
                hits_set = setUnion(hits_set, *keywordMappings_[*it]);
            }
        }
    } else {
        // gets the first term's keywords, and sets hits set equal to that
        std::vector<std::string>::iterator it = terms.begin();
        if (keywordMappings_.find(*it) != keywordMappings_.end()) {
            hits_set = *keywordMappings_[*it];
        }
        // iterates over keywords, only keeping products that are in hits_Set AND associated with the current product
        for (std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it) {
            if (keywordMappings_.find(*it) != keywordMappings_.end()) {  // if keyword has products associated with it
                hits_set = setIntersection(hits_set, *keywordMappings_[*it]);
            } else {
                hits_set.clear();  // if we ever have a unassociated term, and we have the AND command we should return
                                   // nothing
            }
        }
    }
    // now that we have the set, turn it into a vector
    std::vector<Product*> hits;
    for (std::set<Product*>::iterator it = hits_set.begin(); it != hits_set.end(); ++it) {
        hits.push_back(*it);
    }
    return hits;
}

void MyDataStore::dump(std::ostream& ofile) {
    // dumps in the order and format specified in requirements
    ofile << "<products>"
          << "\n";
    // iterate through products vector and dump each product
    for (std::vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</products>"
          << "\n"
          << "<users>"
          << "\n";
    // iterate through user map and dump each user
    for (std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        (it->second)->dump(ofile);
    }
    ofile << "</users>"
          << "\n";
}

void MyDataStore::add_product_to_cart(std::string username, Product* product, std::string& error) {
    // check if the cart exists (essentially checking if username is valid)
    if (carts_.find(username) != carts_.end()) {
        // add product to cart
        // since carts are FIFO, add to the back, and when buying take out of the front
        carts_[username]->push_back(product);
    } else {
        // save error if username is bad
        error = "Invalid request";
    }
}

void MyDataStore::buy_cart(std::string username, std::string& error) {
    // if username is valid iterate through users cart
    if (carts_.find(username) != carts_.end()) {
        for (std::vector<Product*>::iterator it = carts_[username]->begin(); it != carts_[username]->end(); ++it) {
            if (users_[username]->getBalance() >= (*it)->getPrice() && (*it)->getQty() > 0) {
                // if we can afford item, buy it, deduct money from users account and qty from product
                users_[username]->deductAmount((*it)->getPrice());
                (*it)->subtractQty(1);
                // erase item from list, because erasei(it) will reset it to equal the next object in list, --it, so
                // that we dont skip items
                carts_[username]->erase(it);
                --it;
            }
        }
    } else {
        // report invalid username
        error = "Invalid username";
    }
}

std::vector<Product*> MyDataStore::view_user_cart(std::string username, std::string& error) {
    std::vector<Product*> cart;
    // get cart, if username invalid report error
    if (carts_.find(username) != carts_.end()) {
        cart = *carts_[username];
    } else {
        error = "Invalid username";
    }

    return cart;
}