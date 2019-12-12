#pragma once
#include "User.h"

class Trader :
	public User
{
public:
	unsigned int Select_Operation(const string);
	string Get_Operations();
	Trader(int, string , string, string);
	~Trader();
};

