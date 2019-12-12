#include "GigaBet.h"
#include "Bet.h"
#include <sstream>
#include "Numeric_Functions.h"
#include "Trader.h"

GigaBet::GigaBet(){}


GigaBet::~GigaBet(){}


double GigaBet::profit = 0;



vector <Location*> GigaBet::Previous_Locations;

vector <Punter> GigaBet::punters_list;

vector <Trader> GigaBet::traders_list;

vector <Director> GigaBet::directors_list;

vector <User> GigaBet::users_list;

vector <Bet> GigaBet::Bets;

Hierarchy  GigaBet::betting_hierarchy;

vector <string> GigaBet::Actions_History;

Location* GigaBet::Current_location = &GigaBet::betting_hierarchy;


double GigaBet::Get_Profit() {
	return profit;
}

void GigaBet::Add_Bet(Bet& B) {
	Bets.push_back(B);
}









void GigaBet::Set_Hidden_Nodes() {

	Location* L;
	L = &GigaBet::Get_Hierarchy();
	for (unsigned int i = 1;i <= L->Get_size();i++) {
		L->Get_Subcategory(i)->Set_Hidden_Nodes();
	}
	
}

bool GigaBet::Set_Bet_Result(const char c, const string ID, unsigned int id_num) {

	string id_part = ID.substr(0, 8);
	Punter *P;
	string id_part_2;
	Selection *S;

	if (Get_Current_location()->Get_Location_Type() == "Market") {
		S = dynamic_cast<Selection*>(Get_Current_location()->Get_Subcategory(id_num));
	}
	else {
		return false;
	}
	if (c == 'V') {
		for (unsigned int i = 0;i < Bets.size();i++) {
			if (Bets[i].Get_node() == ID && Bets[i].Get_Result()=='-') {
				Bets[i].Set_Result(c);
				P = Get_Punter(Bets[i].Get_user_id());
				P->Change_balance(Bets[i].Get_stake());
			}
		}
		S->Change_Hidden_State(true);
		return true;
	}
	else if (c == 'W') {
		for (unsigned int i = 0;i < Bets.size();i++) {
			id_part_2 = Bets[i].Get_node().substr(0, 8);
			if (Bets[i].Get_node() == ID && Bets[i].Get_Result() == '-') {
				Bets[i].Set_Result(c);
				P = Get_Punter(Bets[i].Get_user_id());
				P->Change_balance(Bets[i].Get_stake()*S->Get_price_d()*0.95);
				Change_Profit(-Bets[i].Get_stake());
				Change_Profit(Bets[i].Get_stake()*S->Get_price_d()*0.05);
			}
			else if (id_part_2 == id_part  && Bets[i].Get_Result() == '-') {
				Bets[i].Set_Result('L');
				P = Get_Punter(Bets[i].Get_user_id());
				Change_Profit(Bets[i].Get_stake());
			}
		}
		return true;

	}
	else if (c == 'L') {
		for (unsigned int i = 0;i < Bets.size();i++) {
			id_part_2 = Bets[i].Get_node().substr(0, 8);
			if (Bets[i].Get_node() == ID && Bets[i].Get_Result() == '-') {
				Bets[i].Set_Result(c);
				P = Get_Punter(Bets[i].Get_user_id());
				P->Change_balance(-Bets[i].Get_stake());
				Change_Profit(Bets[i].Get_stake());
			}
			else if (id_part_2 == id_part  && Bets[i].Get_Result() == '-') {
				Bets[i].Set_Result('W');
				for (unsigned int j = 1;j <= Get_Current_location()->Get_size();j++) {
					if (j != id_num) {
						S = dynamic_cast<Selection*>(Get_Current_location()->Get_Subcategory(j));
						if (Bets[i].Get_node() == S->Get_node()) {
							P = Get_Punter(Bets[i].Get_user_id());
							P->Change_balance(Bets[i].Get_stake()*S->Get_price_d()*0.95);
							Change_Profit(-Bets[i].Get_stake());
							Change_Profit(Bets[i].Get_stake()*S->Get_price_d()*0.05);
						}
					}
				}
			}
		}
		return true;
	}
	else {
		return false;
	}

}




Punter* GigaBet::Find_Punter(const string user_name)
{
	for (unsigned int i = 0;i < punters_list.size();i++) {
		if (user_name == punters_list[i].Get_name()) {
			return &punters_list[i];
		}
	}
	return NULL;
}

vector <User>& GigaBet::Get_Users_List() {
	return users_list;
}

Hierarchy& GigaBet::Get_Hierarchy() {
	return betting_hierarchy;

}

void GigaBet::Show_Users(vector <User*>& U) 
{

	Punter *P;
	cout << "Showing users\n\n" << endl;
	cout << "|user_id|username|fullname|password|type|status|balance|freebets|" << endl;
	if (U.size() == 0) {
		cout << "Nothing to show" << endl;
		return;
	}
	for (unsigned int i = 0;i < U.size();i++) {
		if (U[i]->Get_type() != 1) {
			cout << "|" << U[i]->Get_user_id() << "|" << U[i]->Get_name() << "|" << U[i]->Get_fullname() << "|" << U[i]->Get_password() << "|" << U[i]->Get_type() << "|" << "    |" << "    |" << "   " << endl;
		}
		else {
			P = GigaBet::Get_Punter(U[i]->Get_user_id());
			cout << "|" << P->Get_user_id() << "|" << P->Get_name() << "|" << P->Get_fullname() << "|" << P->Get_password() << "|" << P->Get_type() << "|" << P->Get_Status() << "|" << P->Get_Wallet().balance << "|"<< P->Get_Wallet().Get_Freebets()<< endl;
		}
		
	}

}

void GigaBet::Show_20_Last_Bets() {
	
	vector <Bet> *B;
	B = &Get_Bets();
	int size = B->size();

	cout << "Showing 20 last bets" << endl;
	cout << "|bet_id|user_id|node_id|stake|result|" << endl;

	int i = B->size() - 1;
	while((i >= (size - 21)&& (i>=0))) {
		cout << "|" << B->at(i).Get_bet_id() << "|" << B->at(i).Get_node() << "|" << B->at(i).Get_stake() << "|" << B->at(i).Get_Result()<<"|"<< endl;
		i--;
	}
	if (B->size() == 0) {
		cout << "Nothing to show" << endl;
	}
}
			
vector <Bet>& GigaBet::Get_Bets() {
	return Bets;
}


Bet& GigaBet::Get_Bet(const unsigned int id) {
	return Bets[id - 1];
}

Punter* GigaBet::Get_Punter(const unsigned int id) {
	for (unsigned int i = 0;i < punters_list.size();i++) {
		if (punters_list[i].Get_user_id() == id) {
			return &punters_list[i];
		}
	}
	return NULL;
}

void GigaBet::Add_Punter(Punter& P){

	punters_list.push_back(P);
	Add_User(P);
}

void GigaBet::Change_Profit(const double new_profit) {
	profit = profit + new_profit;
}

void GigaBet::Add_User(User& U)
{
	users_list.push_back(U);
}

vector <User*> GigaBet::Get_Users_With_String(const string name_part) 
{
	vector <User*> U;

	for (unsigned int i = 0;i < users_list.size();i++) {
		if (users_list[i].Get_name().find(name_part) != -1) {
			U.push_back(&users_list[i]);
		}
	}
	return U;
}

Trader* GigaBet::Find_Trader(const string user_name)
{
	for (unsigned int i = 0;i < traders_list.size();i++) {
		if (user_name == traders_list[i].Get_name()) {
			return &traders_list[i];
		}
	}
	return NULL;
}

Director* GigaBet::Find_Director(const string user_name)
{
	for (unsigned int i = 0;i < directors_list.size();i++) {
		if (user_name == directors_list[i].Get_name()) {
			return &directors_list[i];
		}
	}
	return NULL;
}


void GigaBet::Add_Trader(Trader &T) {
	traders_list.push_back(T);
	Add_User(T);
}

void GigaBet::Add_Director(Director& D) {
	directors_list.push_back(D);
	Add_User(D);

}


User* GigaBet::Find_Username(const string username)
{
	unsigned int i = 0;

	if (users_list.size() == 0) {
		return NULL;
	}
	do {
		if (users_list[i].Get_name() == username) {
			if (users_list[i].Get_type() == 1) {
				Punter* P;
				P = GigaBet::Find_Punter(username);
				return P;
			}
			else if (users_list[i].Get_type() == 2) {
				Trader* T;
				T = GigaBet::Find_Trader(username);
				return T;
			}
			else if (users_list[i].Get_type() == 3) {
				Director* D;
				D = GigaBet::Find_Director(username);
				return D;
			}
		}
		i++;
	} while (i < users_list.size());
	return NULL;
}

Location* GigaBet::Get_Current_location() {
	return Current_location;
}

void GigaBet::Go_To_Previous_Location() {

	Current_location=Previous_Locations.back();
	Previous_Locations.pop_back();


}

void GigaBet::Set_Current_location(int id) {

	if (id > 0) {
		Previous_Locations.push_back(Current_location);
		Current_location = Current_location->Get_Subcategory(id);
	}
	else {
		Current_location = &betting_hierarchy;
	}
	
	
}

User* GigaBet::Get_User(int id) {
	return &users_list[id-1];
}


void GigaBet::Add_New_Action(string new_action) {
	Actions_History.push_back(new_action);
}

string GigaBet::Get_Action(unsigned int index) {
	return Actions_History[index];
}

unsigned int GigaBet::Get_Actions_History_Size() {
	return Actions_History.size();
}
