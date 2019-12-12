#pragma once

#include <iostream>
#include <string>

using namespace std;



class User
{
protected:
	unsigned int user_id;
	string username;
	string fullname;
	string password;
	unsigned int type;
public:
	string Get_name();
	string Get_fullname();
	string Get_password();
	unsigned int Get_user_id();
	unsigned int Get_type();
	virtual string Get_Operations();
	virtual unsigned int Select_Operation(const string);
	User(unsigned const int, unsigned const int, const string, const string, const string);
	virtual~User();
};

