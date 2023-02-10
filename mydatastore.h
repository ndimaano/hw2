#include "datastore.h"
#include "clothing.h"
#include "book.h"
#include "movie.h"
#include "util.h"
#include <deque>
#include <map>
#include <set>

class MyDataStore : public DataStore {
	public:
		MyDataStore();
		virtual ~MyDataStore();
		void addProduct(Product* p);
		void addUser(User* u);
		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void dump(std::ostream& ofile);
		void viewCart(std::string userNameds);
		void buyCart(std::string usersNamed);
		void addToCart(std::string userNamed, int search_hit_number, std::vector<Product*>& producted );
		bool checkUser(std::string userNamez);
	private:
		std::map<std::string, std::set<Product*>> keyPairs;
		std::set<Product*> productList;
		std::set<User*> userList;
		std::map<std::string, User*> keyUsers;
		std::map<User*, std::deque<Product*>> Users;
};