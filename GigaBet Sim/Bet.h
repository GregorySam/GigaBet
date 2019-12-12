#pragma once
#include <string>
#include <vector>

using namespace std;
class Bet
{
private:
	unsigned int bet_id;
	unsigned int user_id;
	string node_id;
	double stake;
	char Result;
public:
	void Set_bet_id(const unsigned int);
	void Set_user_id(const unsigned int);
	void Set_node(const string);
	void Set_stake(const double);
	void Set_Result(const char);

	unsigned int Get_bet_id();
	unsigned int Get_user_id();
	string Get_node();
	double Get_stake();
	char Get_Result();

	Bet(const unsigned int, const unsigned int, const string, const double, const char);
	~Bet();
};

