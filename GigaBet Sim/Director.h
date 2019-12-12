#pragma once
#include "User.h"
class Director :
	public User
{
public:
	string Get_Operations();
	unsigned int Select_Operation(const string);
	Director(int, string , string , string);
	~Director();
};

