#include "datastore.h"

class Movie : public Product {
	public:
		Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);
		~Movie() {};
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;
		bool isMatch(std::vector<std::string>& searchTerms) const;
	protected:
		std::string genre_;
		std::string rating_;
};