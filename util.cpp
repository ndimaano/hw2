#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords) //COMPLETED 
{
	set<string> pstw; // creates a set object to hold the string set that will be returned
	istringstream iss(rawWords); //creates a string stream of the stream to handle handling of spaces
    string temp;

	while (iss >> temp) { // iterates through the string until there is nothing more to stream
		string before;
		string after;
		bool punctuated = false;
		for(size_t j=0; j< temp.size(); j++) { // this for loop checks if each word has a punctuation in it
			if(ispunct(temp[j]) > 0) { // if there is punctuation it will create two strings out of the substring
				before = temp.substr(0,j);
				after = temp.substr(j+1, rawWords.size()-j);
				punctuated = true;
			}
		}
		if(punctuated == true) { // this if statement will add the seperated substrings from a punctuated string to the set if, and will only add them if they are more than 2 characters
			if(before.size() >= 2) {
				pstw.insert(convToLower(before));
			}
			if(after.size() >= 2) {
				pstw.insert(convToLower(after));
			}
		}
		if((temp.size() > 2) && (punctuated == false)) { //this if statement will add the string from the string stream to the set if it is more than 2 characters
			pstw.insert(convToLower(temp));
		}
	}

	return pstw;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
