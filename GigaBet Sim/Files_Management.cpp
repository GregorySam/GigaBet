#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GigaBet.h"
#include "Numeric_Functions.h"
#include "User.h"
#include "Punter.h"
#include "Trader.h"
#include "Director.h"


using namespace std;


vector <string> Split(const string str) 
{
	istringstream iss(str);
	vector <string> tokens;
	string token;
	
	while (getline(iss,token,'|')) {
		tokens.push_back(token);
	}
	if (tokens.size() == 8) {
	}
	else {
		tokens.push_back("");
	}
	return tokens;
	

}

void Add_Node(string node_ID, const string node_name) 
{
	char split_char = '.';
	Location* L;
	Node* N;
	bool is_hidden = false;
	L = GigaBet::Get_Current_location();

	if (node_ID != ""&& node_ID.at(0) == '[') {
		node_ID.erase(0, 8);
		is_hidden = true;

	}
	node_ID = node_ID.substr(0, node_ID.size() - 2);
	

	istringstream split(node_ID);

	for (string each;getline(split, each, split_char);) {
		L = L->Get_Subcategory((unsigned int)Convert_String_To_Number(each));
	}
	if (L->Get_Location_Type() == "Market") {
		string price;
		string selection_name;
		istringstream stream_node_name(node_name);

		getline(stream_node_name, selection_name, '#');
		getline(stream_node_name, price, '#');

		L->Add_Location(selection_name,price);
		if (is_hidden) {
			N = L->Get_Subcategory(L->Get_size());
			N->Change_Hidden_State(true);
		}

	}
	else {
		L->Add_Location(node_name,"");
		if (is_hidden) {
			N = L->Get_Subcategory(L->Get_size());
			N->Change_Hidden_State(true);
		}
		
		
	}

}

void Show_Users_File() {
	ifstream users_file;
	string content;

	users_file.open("users.csv");
	cout << endl;
	while (getline(users_file, content))
	{
		cout << content << endl;
	}
	cout << endl;
	users_file.close();
}

unsigned int Read_Users_File() {

	ifstream users_file;
	string line;
	vector<string> usersinfo;

	users_file.open("users.csv");

	if (users_file.is_open()) {
		getline(users_file, line);
		while (getline(users_file, line)) {
			usersinfo=Split(line);
			if (usersinfo[4] == "1") {
				Punter P((int)Convert_String_To_Number(usersinfo[0]), usersinfo[2], usersinfo[3], usersinfo[1], usersinfo[5],Convert_String_To_Number(usersinfo[6]), usersinfo[7]);
				GigaBet::Add_Punter(P);
			}
			else if (usersinfo[4] == "2") {
				Trader T((int)Convert_String_To_Number(usersinfo[0]), usersinfo[2], usersinfo[3], usersinfo[1]);
				GigaBet::Add_Trader(T);
			}
			else if (usersinfo[4] == "3") {
				Director D((int)Convert_String_To_Number(usersinfo[0]), usersinfo[2], usersinfo[3], usersinfo[1]);
				GigaBet::Add_Director(D);
			}
		}
		users_file.close();
		return 1;
	}
	else {
		cout << "Error with file" << endl;
		return 0;
	}


}

unsigned int Read_Profit(){
	ifstream actions_file;
	double profit;

	actions_file.open("Profits");
	if (actions_file.is_open()) {
		actions_file>>profit;
		GigaBet::Change_Profit(profit);
		return 1;
	}
	else {
		cout << "Error with file" << endl;
		return 0;
	}


}

unsigned int Read_History_File() {
	ifstream actions_file;
	string line;

	actions_file.open("audit.log");

	if (actions_file.is_open()) {
		while (getline(actions_file, line)) {
			GigaBet::Add_New_Action(line);
		}
		actions_file.close();
		return 1;
	}
	else {
		cout << "Error with file" << endl;
		return 0;
	}
	
}

unsigned int Read_Bets_File() {

	ifstream bets_file;
	string line;
	vector <string> bets_info;

	bets_file.open("bets.csv");

	if (bets_file.is_open()) {
		getline(bets_file, line);
		while (getline(bets_file, line)) {
			bets_info = Split(line);
			Bet B((unsigned int)Convert_String_To_Number(bets_info[0]), (unsigned int)Convert_String_To_Number(bets_info[1]),bets_info[2],Convert_String_To_Number(bets_info[3]),bets_info[4].at(0));
			GigaBet::Add_Bet(B);
			GigaBet::Get_Punter((unsigned int)Convert_String_To_Number(bets_info[1]))->Add_New_Bet(B);
		}
		bets_file.close();
		return 1;

	}
	else {
		cout << "Error with file"<< endl;
		return 0;
	}
}



unsigned int Read_Hierarchy_File() 
{
	ifstream hierarchy_file;
	string line;
	string node_id;
	string node_name;
	size_t  found;



	hierarchy_file.open("hierarchy.dat");

	if (hierarchy_file.is_open()) {
		while (getline(hierarchy_file, line)) {

			found = line.find(" ");
			node_id = line.substr(0, found);
			node_name = line.substr(found + 1, string::npos);

			Add_Node(node_id, node_name);
		}
		hierarchy_file.close();
		return 1;
	}
	else {
		cout << "Error with file" << endl;
		return 0;
	}
}

void Write_Users_File() {

	ofstream users_file;

	users_file.open("users.csv");

	
	if (users_file.is_open()) {
		users_file << "userid|username|fullname|password|type|status|balance|freebets" << endl;
		for (unsigned int i = 1;i <= GigaBet::Get_Users_List().size();i++) {
			User *U;
			U = GigaBet::Get_User(i);
			if (U->Get_type() == 1) {
				Punter* P;
				P = GigaBet::Get_Punter(i);
				users_file << P->Get_user_id() << "|" << P->Get_name() << "|" << P->Get_fullname() << "|" << P->Get_password() << "|" << P->Get_type() << "|" << P->Get_Status() << "|" << P->Get_Wallet().balance << "|" << P->Get_Wallet().Get_Freebets() << endl;

			}
			else {
				users_file << U->Get_user_id() << "|" << U->Get_name() << "|" << U->Get_fullname() << "|" << U->Get_password() << "|" << U->Get_type() << "|" << "|" << "|" << endl;
			}
		}
		users_file.close();
	}
	else {
		cout << "Error with file" << endl;
	}


}

void Write_Bets_File() {

	ofstream bets_file;

	bets_file.open("bets.csv");

	if (bets_file.is_open()) {
		bets_file << "bet_id|user_id|node_id|stake|result" << endl;
		for (unsigned int i = 1;i <= GigaBet::Get_Bets().size();i++) {
			Bet* B;
			B = &GigaBet::Get_Bet(i);
			bets_file << B->Get_bet_id() << "|" << B->Get_user_id() << "|" << B->Get_node() << "|" << B->Get_stake() << "|" << B->Get_Result() << endl;
		}
		bets_file.close();

	}
	else {
		cout << "Error with file" << endl;
	}

}

void Write_Actions_File()
{
	ofstream actions_file;

	actions_file.open("audit.log");
	if (actions_file.is_open()) {
		for (unsigned int i = 0;i < GigaBet::Get_Actions_History_Size();i++) {
			actions_file << GigaBet::Get_Action(i) << endl;

		}
		actions_file.close();
	}
	else {
		cout << "Error with file" << endl;
	}
}


void Write_Hierarchy_File() {

	ofstream hierarchy_file;
	GigaBet::Set_Hidden_Nodes();
	hierarchy_file.open("hierarchy.dat");
	
	if(hierarchy_file.is_open()) {
		hierarchy_file <<GigaBet::Get_Hierarchy().Show_All_Nodes();
		hierarchy_file.close();
	}
	else {
		cout << "Error with file"<< endl;
	}

}

void Write_Profit() {
	ofstream actions_file;
	double profit;

	actions_file.open("Profits");
	if (actions_file.is_open()) {
		actions_file << GigaBet::Get_Profit();
	}
	else {
		cout << "Error with file" << endl;
	}
}