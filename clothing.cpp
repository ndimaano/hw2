#include <sstream>
#include <iomanip>
#include <set>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const string size, const string brand) :
	Product(category, name, price, qty), size_(size), brand_(brand)
{

}

set<string> Clothing::keywords() const{
    set<string> nameWords;
    set<string> brandWords;
    set<string> keystuff;
    nameWords = parseStringToWords(name_);
    brandWords = parseStringToWords(brand_);
    keystuff = setUnion(nameWords, brandWords);
    return keystuff;
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_  << endl;
}

string Clothing::displayString() const{
	ostringstream besideYou;
	string bandaids;
	besideYou << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left." << endl;
	bandaids = besideYou.str();
	return bandaids;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}
