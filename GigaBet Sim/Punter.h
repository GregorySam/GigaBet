#pragma once
#include"User.h"
#include <vector>
#include "Bet.h"

class Punter:public User
{
private:
	string status;
	vector <Bet> Bet_History;
	struct Wallet {
		string Get_Freebets();
		void Show_Freebets();
		double balance;
		vector <double> freebets;
		
	};
	Wallet W;
public:
	void Add_freebet(const double);
	void Use_freebet(const int);
	void Change_balance(const double);
	string Get_Status();
	void Set_Status(const string);
	void Show_Bet_History();
	void Add_New_Bet(Bet&);
	Wallet Get_Wallet();
	double Get_freebet(const unsigned int);
	void Set_Password(const string );
	void Set_Username(const string );
	unsigned int Select_Operation(const string);
	Punter(int,const string,const string ,const string, const string, const double , const string);
	string Get_Operations();
	~Punter();
};

