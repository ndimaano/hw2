#include <sstream>
#include <iomanip>
#include <set>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const string isbn, const string author) :
	Product(category, name, price, qty), isbn_(isbn), author_(author)
{

}

set<string> Book::keywords() const{
    set<string> nameWords;
    set<string> authorWords;
    set<string> keystuff;
    nameWords = parseStringToWords(name_);
    authorWords = parseStringToWords(author_);
    keystuff = setUnion(nameWords, authorWords);
		keystuff.insert(isbn_);
    return keystuff;
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_   << endl;
}

string Book::displayString() const{
	ostringstream besideYou;
	string bandaids;
	besideYou << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left." << endl;
	bandaids = besideYou.str();
	return bandaids;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}