#pragma once
#include "User.h"


class Guest:public User
{
public:
	unsigned int Select_Operation(const string);
	string Get_Operations();
	Guest();
	~Guest();
};

