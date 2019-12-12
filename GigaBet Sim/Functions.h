#include <string>
#include <cctype>
#include <sstream>
#pragma once

using namespace std;


string Convert_Number_To_String(const double);
double Convert_String_To_Number(const string);
double Convert_StringFraction_To_Decimal(const string);

bool Is_Number(const string);
bool Is_Integer(const string);


bool Is_Fraction(string);