#pragma once
#include "Punter.h"
#include "Trader.h"
#include "Director.h"
#include "Hierarchy.h"
#include <vector>

class GigaBet
{
private:
	
	static vector <Location*> Previous_Locations;
	static double profit;
	static Location* Current_location;
	static vector <Punter> punters_list;
	static vector <Trader> traders_list;
	static vector <Director> directors_list;
	static vector <User> users_list;
	static vector <Bet> Bets;
	static Hierarchy betting_hierarchy;
	static vector <string> Actions_History;
public:
	static double Get_Profit();
	static void Set_Hidden_Nodes();
	static void Go_To_Previous_Location();
	static Trader* Find_Trader(const string);
	static Director* Find_Director(const string);
	static void Add_Trader(Trader&);
	static void Add_Director(Director&);
	static vector <Bet>& Get_Bets();
	static Bet& Get_Bet(const unsigned int);
	static Hierarchy& Get_Hierarchy();
	static void Add_Bet(Bet&);
	static void Show_Users(vector <User*>&);
	static void Show_20_Last_Bets();
	static bool Set_Bet_Result(const char,const string,unsigned int );
	static Punter* Get_Punter(const unsigned int);
	static void Add_Punter(Punter&);
	static void Add_User(User&);
	static void Change_Profit(const double);
	static unsigned int Get_Actions_History_Size();
	static string Get_Action(const unsigned int);
	static void Add_New_Action(const string);
	static Location* Get_Current_location();
	static void Set_Current_location(const int);
	static User* Get_User(const int);
	static vector <User>& Get_Users_List();
	GigaBet();
	~GigaBet();
	static Punter* Find_Punter(const string);
	static User* Find_Username(const string);
	static vector <User*> Get_Users_With_String(const string);

};


