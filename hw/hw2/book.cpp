#include "book.h"

#include "product.h"
#include "util.h"
#include <iomanip>
#include <sstream>

using namespace std;

Book::Book(
        const std::string category, const std::string name, double price, int qty, std::string author, std::string isbn)
        : Product(category, name, price, qty) {
    isbn_ = isbn;
    author_ = author;
}

Book::~Book() {}

std::set<std::string> Book::keywords() const {
    // get keywords from name and author strings and add isbn as a keyword as well
    std::set<std::string> keywords;
    std::set<std::string> name_words = parseStringToWords(name_);
    std::set<std::string> author_words = parseStringToWords(author_);
    keywords = setUnion(author_words, name_words);
    keywords.insert(isbn_);
    return keywords;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const { return false; }

std::string Book::displayString() const {
    // dsiplay according to requirements
    return (name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + std::to_string(price_) + " "
            + std::to_string(qty_) + " left.");
}

void Book::dump(std::ostream& os) const {
    // dump according to requirements
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

std::string Book::getAuthor() const { return author_; }
std::string Book::getIsbn() const { return isbn_; }