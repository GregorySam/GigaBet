#include "User.h"



User::User(unsigned const int a=0, unsigned const int b=0, const string real_name=0, const string pass=0 , const string user_name=0 ):fullname(real_name),type(a),user_id(b)
{	
	username = user_name;
	password = pass;
}
string User::Get_Operations() { return ""; }
unsigned int User::Select_Operation(const string Operation) { return false; }
string User::Get_name() {
	return username;
}
string User::Get_fullname() {
	return fullname;
}
string User::Get_password() {
	return password;
}
unsigned int User::Get_user_id() {
	return user_id;
}
unsigned int User::Get_type() {
	return type;
}
User::~User()
{
}
