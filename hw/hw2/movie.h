#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

class Movie : public Product {
public:
    Movie(const std::string category,
          const std::string name,
          double price,
          int qty,
          std::string rating,
          std::string genre);
    virtual ~Movie();

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
    // members and functions specific to movie
    std::string genre_;
    std::string rating_;
    std::string getRating() const;
    std::string getGenre() const;
};
#endif