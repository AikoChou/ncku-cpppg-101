#include "zipcode.h"
using namespace std;

int main()
{
	int i, num;
	string str;
	cout << "*~~ZipCode Transformer~~*" << endl;
	
	while(1)
	{
		cout << "Choose (0.Exit 1.Input integer 2.Input string)? ";
		cin >> i;
		if(i == 0 ) break;
		cout << "Your zip code = ";
		if(i == 1)
		{
			cin >> num; 
			ZipCode zipCode1(num);
			cout << "-----output-----" << endl;
			cout << "As an integer: ";
			zipCode1.displayInt();
			cout << endl;
			cout << "As a  string: ";
			zipCode1.displayString();
			cout << endl;
			cout << "---end of output---" << endl;
		}else if(i == 2)
		{
			cin.ignore(1000, '\n');
			getline(cin, str);
			ZipCode zipCode2(str);
			cout << "-----output-----" << endl;
			cout << "As an integer: ";
			zipCode2.displayInt();
			cout << endl;
			cout << "As a  String: ";
			zipCode2.displayString();
			cout << endl;
			cout << "---end of output---" << endl;
		}
	
	}
	
	return 0;
}
