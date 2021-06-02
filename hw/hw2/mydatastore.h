#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "product.h"
#include "user.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class MyDataStore : public DataStore {
public:
    MyDataStore();

    virtual ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    void add_product_to_cart(std::string username, Product* product, std::string& error);

    void buy_cart(std::string username, std::string& error);

    std::vector<Product*> view_user_cart(std::string username, std::string& error);

private:
    std::map<std::string, std::vector<Product*>*>
            carts_;  // key is username, and has a vector of all the products in that user's cart
    std::map<std::string, std::set<Product*>*>
            keywordMappings_;  // for each keyword we ever get it is the key to a set of products with that keyword
    std::map<std::string, User*> users_;  // this stores all the users
    std::vector<Product*>
            products_;  // this is just use to store all our products for the end dump and to deallocate the products
};

#endif
