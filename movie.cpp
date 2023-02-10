#include <sstream>
#include <iomanip>
#include <set>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const string genre, const string rating) :
	Product(category, name, price, qty), genre_(genre), rating_(rating)
{

}


set<string> Movie::keywords() const{
    set<string> nameWords;
    set<string> keystuff;
    nameWords = parseStringToWords(name_);
    keystuff = nameWords;
		keystuff.insert(genre_);
    return keystuff;
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_   << endl;
}

string Movie::displayString() const{
	ostringstream besideYou;
	string bandaids;
	besideYou << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left." << endl;
	bandaids = besideYou.str();
	return bandaids;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}