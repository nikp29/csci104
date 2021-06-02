#include "movie.h"

#include "product.h"
#include "util.h"
#include <iomanip>
#include <sstream>

using namespace std;

Movie::Movie(
        const std::string category,
        const std::string name,
        double price,
        int qty,
        std::string rating,
        std::string genre)
        : Product(category, name, price, qty) {
    genre_ = genre;
    rating_ = rating;
}

Movie::~Movie() {}

std::set<std::string> Movie::keywords() const {
    // get keywords from name and genre strings
    std::set<std::string> keywords;
    std::set<std::string> name_words = parseStringToWords(name_);
    std::set<std::string> genre_words = parseStringToWords(genre_);
    keywords = setUnion(genre_words, name_words);
    return keywords;
}

// is this supposed to return something else?
bool Movie::isMatch(std::vector<std::string>& searchTerms) const { return false; }

std::string Movie::displayString() const {
    // display movie according to requirements
    return (name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " "
            + std::to_string(qty_) + " left.");
}

void Movie::dump(std::ostream& os) const {
    // dump movie according to requirements
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

std::string Movie::getRating() const { return rating_; }
std::string Movie::getGenre() const { return genre_; }