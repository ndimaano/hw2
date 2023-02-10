#include "mydatastore.h"

MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore(){
	std::set<Product*>::iterator it;
	for(std::set<Product*>::iterator it = productList.begin(); it != productList.end(); ++it) {
		delete *it;
	}
	std::set<User*>::iterator itt;
	for(std::set<User*>::iterator itt = userList.begin(); itt != userList.end(); ++itt) {
		delete *itt;
	}
}

void MyDataStore::addProduct(Product* p) {
	std::set<std::string> keyWordSet = p->keywords();
	productList.insert(p);
	std::set<std::string>::iterator it;
	for(std::set<std::string>::iterator it = keyWordSet.begin(); it != keyWordSet.end(); ++it)
	{
			std::map<std::string, std::set<Product*>>::iterator ittt = keyPairs.find(*it);
			if (ittt != keyPairs.end()) // we found the element
			{
				ittt->second.insert(p);
			}
			else {
				std::set<Product*> productions = {p};
				keyPairs.insert(std::make_pair(convToLower(*it), productions));
			}
			
			// std::map<std::string, std::set<Product*>>::iterator itt = keyPairs.find(*it);
			// if (itt != keyPairs.end()) 
			// {
			// 	itt->second.insert(p);
			// }
	}

}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
	std::set<Product*> temp;
	std::vector<Product*> tempted;
	if(type == 0){
		std::map<std::string, std::set<Product*>>::iterator ot = keyPairs.find(convToLower(terms[0]));
			if (ot != keyPairs.end()) 
			{
				temp = ot->second;
			}
		if(terms.size() > 1) {
			for(size_t i=1; i < terms.size(); i++) {
				std::map<std::string, std::set<Product*>>::iterator it = keyPairs.find(convToLower(terms[i]));
				if (it != keyPairs.end()) 
				{
					temp = setIntersection(temp, it->second);
				}
			}
		}
	}
	else if (type == 1) {
		for(size_t i=0; i < terms.size(); i++) {
			std::map<std::string, std::set<Product*>>::iterator it = keyPairs.find(convToLower(terms[i]));
			if (it != keyPairs.end()) 
			{
				temp = setUnion(temp, it->second);
			}
		}
	}
	std::set<Product*>::iterator it;
	for(std::set<Product*>::iterator it = temp.begin();it!=temp.end();it++) {
		tempted.push_back(*it);
	}
	return tempted;
}

void MyDataStore::dump(std::ostream& ofile) {
	if(productList.empty() == false) {
		ofile << "<products>" << "\n";
		std::set<Product*>::iterator itt;
		for(std::set<Product*>::iterator itt = productList.begin(); itt != productList.end(); ++itt)
		{
			(*itt)->dump(ofile);
		}
		ofile << "</products>" << "\n";
	}
	else {
		ofile << "<products>" << "\n";
		ofile << "</products>" << "\n";
	}

	if(userList.empty() == false) {
		ofile << "<users>" << "\n";
		std::set<User*>::iterator it;
		for(std::set<User*>::iterator it = userList.begin(); it != userList.end(); ++it)
		{
			(*it)->dump(ofile);
		}
		ofile << "</users>";
	}
	else {
		ofile << "<users>" << "\n";
		ofile << "</users>" << "\n";
	}
	
}

void MyDataStore::addToCart(std::string userNamed, int search_hit_number, std::vector<Product*>& producted) { //ERROR PROBABLY HERE
	std::map<std::string, User*>::iterator it = keyUsers.find(userNamed);
	if (it != keyUsers.end()) 
	{
		std::map<User*, std::deque<Product*>>::iterator itt = Users.find(it->second);
		if (itt != Users.end()) 
		{
			Product*& temporary = producted[search_hit_number-1];
			itt->second.push_back(temporary);
		}
	}
}

void MyDataStore::addUser(User* u) {
	std::deque<Product*> userbased = {};
	
	Users.insert(std::make_pair(u, userbased));
	userList.insert(u);
	keyUsers.insert(std::make_pair(u->getName(), u));
}

void MyDataStore::viewCart(std::string userNameds) { //PROBLEM IS HERE
	std::map<std::string, User*>::iterator it = keyUsers.find(userNameds);
	if (it != keyUsers.end()) 
	{
		std::map<User*, std::deque<Product*>>::iterator itt = Users.find(it->second);
		if (itt != Users.end()) 
		{
			for(size_t i=0; i < itt->second.size(); i++) {
				std::cout << "Item " << (i + 1) << "\n";
				std::cout << itt->second[i]->displayString();
			}
		}
	}
}

void MyDataStore::buyCart(std::string usersNamed) {
		std::map<std::string, User*>::iterator it = keyUsers.find(usersNamed);

		if (it != keyUsers.end()) 
		{
			// std::map<User*, std::deque<Product*>>::iterator itt = Users.find(it->second);
			// if (itt != Users.end()) 
			// {
			// 	for(size_t i=0; i < itt->second.size(); i++) {
			// 		std::cout << "Item " << (i + 1) << "\n";
			// 		std::cout << itt->second[i]->displayString();
			// 	}
			// }
			std::map<User*, std::deque<Product*>>::iterator iit = Users.find(it->second);
			if (iit != Users.end()) 
			{
				int counter = 0;
				for(size_t i=0; i < iit->second.size(); i++) {
					if((iit->second[i]->getQty() > 0) && (iit->first->getBalance() >= iit->second[i]->getPrice())) {
						iit->first->deductAmount(iit->second[i]->getPrice());
						iit->second[i]->subtractQty(1);
						counter++;
					}
				}
				for(int i =0; i < counter; i++) {
					iit->second.pop_front();
				}
			}
		}
}

bool MyDataStore::checkUser(std::string userNamez) {
	std::map<std::string, User*>::iterator it = keyUsers.find(userNamez);
		if(it != keyUsers.end()){
			return true;
		}
		else {
			return false;
		}
	
	return true;
}





