#include "datastore.h"

class Clothing : public Product {
	public:
		Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);
		virtual ~Clothing() {};
		std::set<std::string> keywords() const;
		std::string displayString() const;
		bool isMatch(std::vector<std::string>& searchTerms) const;
		void dump(std::ostream& os) const;
	protected:
		std::string size_;
		std::string brand_;
};