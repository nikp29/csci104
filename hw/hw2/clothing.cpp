#include "clothing.h"

#include "product.h"
#include "util.h"
#include <iomanip>
#include <sstream>

using namespace std;

Clothing::Clothing(
        const std::string category, const std::string name, double price, int qty, std::string brand, std::string size)
        : Product(category, name, price, qty) {
    size_ = size;
    brand_ = brand;
}

Clothing::~Clothing() {}

std::set<std::string> Clothing::keywords() const {
    // get keywords from name and brand strings
    std::set<std::string> keywords;
    std::set<std::string> name_words = parseStringToWords(name_);
    std::set<std::string> brand_words = parseStringToWords(brand_);
    keywords = setUnion(brand_words, name_words);
    return keywords;
}

// is this supposed to return something else?
bool Clothing::isMatch(std::vector<std::string>& searchTerms) const { return false; }

std::string Clothing::displayString() const {
    // display according to requirements
    return (name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " "
            + std::to_string(qty_) + " left.");
}

void Clothing::dump(std::ostream& os) const {
    // dump according to requirements
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

std::string Clothing::getBrand() const { return brand_; }
std::string Clothing::getSize() const { return size_; }