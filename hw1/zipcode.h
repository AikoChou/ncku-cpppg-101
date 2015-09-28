#include <iostream>
#include <string>
#include <sstream>
#include <exception>

using namespace std;

class ZipCode
{
public:
	ZipCode(int);
	ZipCode(string);
	string getCodeNum();
	void displayInt();
	void displayString();
private:
	string barCode;
};
