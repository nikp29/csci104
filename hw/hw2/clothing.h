#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

class Clothing : public Product {
public:
    Clothing(
            const std::string category,
            const std::string name,
            double price,
            int qty,
            std::string brand,
            std::string size);
    virtual ~Clothing();

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
    // private members and functions specifically for clothing
    std::string size_;
    std::string brand_;
    std::string getBrand() const;
    std::string getSize() const;
};
#endif