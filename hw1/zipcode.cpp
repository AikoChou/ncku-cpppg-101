#include <iostream>
#include "zipcode.h"
using namespace std;

ZipCode::ZipCode(int num)
{
	stringstream ss;
	ss << num;
	string str = ss.str();
	
	int i;
	int len = str.length();
	for(i = 0; i < len; i++)
		switch (str[i])
		{
			case '0':	barCode = barCode + "11000";
						break;
			case '1':	barCode = barCode + "00011";
						break;
			case '2':	barCode = barCode + "00101";
						break;
			case '3':	barCode = barCode + "00110";
						break;
			case '4':	barCode = barCode + "01001";
						break;
			case '5':	barCode = barCode + "01010";
						break;
			case '6':	barCode = barCode + "01100";
						break;
			case '7':	barCode = barCode + "10001";
						break;
			case '8':	barCode = barCode + "10010";
						break;
			case '9':	barCode = barCode + "10100";
						break;
		}
}

ZipCode::ZipCode(string code)
{
	barCode = code;
}

string ZipCode::getCodeNum()
{
	return barCode;
}

void ZipCode::displayInt()
{
	int i, j, k = 0, len, part, one = 0; 
	int temp[5];
	len = getCodeNum().length();
	if((len%5) == 0) part = len/5;
	else
	{
		cout << "Five digits a group!" << endl; 
		terminate();
	}
	
	for(j = 0; j < part; j++) 
	{
		for(i = 0; i < 5; i++) 
		{
			switch(getCodeNum()[k]) 
			{
				case '1':	temp[i] = 1;
							one++;
							break;
				case '0':	temp[i] = 0;
							break;
				default:	cout << "Shoud be 0 or 1!" << endl;
							terminate();
			} 
		k++;
		}
		
		if(one == 2)
		{	
			one = 0;
			cout << (temp[0]*7 + temp[1]*4 + temp[2]*2 + temp[3]) % 11;
		}
		else
		{	
			cout << "Shoud be two 1's!" << endl;
			terminate();
		}
	}
}

void ZipCode::displayString()
{
	cout << getCodeNum();
}

