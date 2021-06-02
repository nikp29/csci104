#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

class Book : public Product {
public:
    Book(const std::string category,
         const std::string name,
         double price,
         int qty,
         std::string author,
         std::string isbn);
    virtual ~Book();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    virtual std::set<std::string> keywords() const;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    virtual bool isMatch(std::vector<std::string>& searchTerms) const;

    /**
     * Returns a string to display the product info for hits of the search
     */
    virtual std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
    virtual void dump(std::ostream& os) const;

private:
    // pricate data members and functions specific to book
    std::string isbn_;
    std::string author_;
    std::string getAuthor() const;
    std::string getIsbn() const;
};
#endif