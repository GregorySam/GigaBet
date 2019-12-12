#include "Numeric_Functions.h"
#include <string>
#include <iostream>
using namespace std;





double Convert_StringFraction_To_Decimal(const string fraction) {

	string numerator;
	string denominator;

	istringstream stream_node_name(fraction);

	std::getline(stream_node_name, numerator, '/');
	
	std::getline(stream_node_name, denominator, '/');

	return Convert_String_To_Number(numerator) / Convert_String_To_Number(denominator)+1;



}

double Convert_String_To_Number(const string s)
{
	double Result;

	stringstream convert(s);
	if (!(convert >> Result)) { Result = 0; }
	return Result;
}

string Convert_Number_To_String(const double number) {
	string Result;

	stringstream convert;
	convert << number;
	return Result = convert.str();
}



bool Is_Number(const string s)
{
	unsigned int count=0;
	string::const_iterator it = s.begin();
	while (it != s.end() && (isdigit(*it) || *it == '.') && count <= 1) {
		if (*it == '.') {
			count++;
		}
		it++;
	}
	return !s.empty() && it == s.end();
}

bool Is_Integer(const string s) {

	signed int count = 0;
	string::const_iterator it = s.begin();
	while (it != s.end() && (isdigit(*it))) {
		it++;
	}
	return !s.empty() && it == s.end();

}

bool Is_Fraction(string fraction) {
	
	string numerator;
	string denominator;
	size_t slash;

	slash = fraction.find('/');
	numerator = fraction.substr(0, slash);
	denominator= fraction.substr(slash+1,string::npos);

	return Is_Integer(numerator) && Is_Integer(denominator);
	
}