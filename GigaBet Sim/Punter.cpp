
#include "User_Operations.h"
#include "Numeric_Functions.h"
#include "GigaBet.h"
#include <stdio.h>

vector <double> Get_freebets_from_string(const string freebets_str) {

	istringstream iss(freebets_str);
	string freebet;
	vector <double> freebets_d;


	while (getline(iss, freebet, ',')) {
		freebets_d.push_back(Convert_String_To_Number(freebet));
	}
	return freebets_d;
}

Punter::Punter(const  int id, const string name, const string pass, const string user_name,const string status_str,const double new_balance,const string freebets_str) :User(1, id, name, pass, user_name)
{

	status = status_str;
	W.balance = new_balance;
	W.freebets = Get_freebets_from_string(freebets_str);
}

void Punter::Set_Status(const string new_status)
{
	status = new_status;
}

string Punter::Get_Status()
{
	return status;
}

void Punter::Add_New_Bet(Bet& B) 
{
	Bet_History.push_back(B);
}


void Punter::Show_Bet_History() {

	cout << "Showing bet history" << endl;
	cout << "bet_id|user_id|node_id|stake|result" << endl;
	for (int i = 0;i < Bet_History.size();i++) {
		cout << Bet_History[i].Get_bet_id() << "|" << this->Get_user_id() <<"|"<<Bet_History[i].Get_node() << "|" << Bet_History[i].Get_stake() << "|" << Bet_History[i].Get_Result() << endl;
	}
	if (Bet_History.size() == 0) {
		cout << "Nothing to show" << endl;
	}
}

string Punter::Get_Operations() {
	if (GigaBet::Get_Current_location()->Get_Location_Type() == "Market") {
		return "Select: \n\n(Back) ,to go back\n\nH(Home), to return to the home screen\n\nT(Toggle), to switch view rates\n\nX(Exit), to exit the system\n\nA(Account), for managing user account information\n\nP(Place) to place new bet\n\n";
	}
	else if (GigaBet::Get_Current_location()->Get_Location_Type() == "Hierarchy") {
		return "Select: \n\nthe ID of the node that you want to visit\n\nH(Home), to return to the home screen\n\nT(Toggle), to switch view rates\n\nX(Exit), to exit the system\n\nA(Account), for managing user account information\n\n";

	}
	else {
		return "Select: \n\nthe ID of the node that you want to visit\n\n(Back) to go to previous category\n\nH(Home), to return to the home screen\n\nT(Toggle), to switch view rates\n\nX(Exit), to exit the system\n\nA(Account), for managing user account information\n\n";

	}
}
unsigned int Punter::Select_Operation(const string Operation) {

	string action;

	if (Is_Integer(Operation)) {
		if (GigaBet::Get_Current_location()->Get_Location_Type() != "Market" && Got_To_Next_Category_User(Operation) ) {
			action = "--The user with name " + this->username + " visited location " + GigaBet::Get_Current_location()->Get_path();
			GigaBet::Add_New_Action(action);
			return 1;
		}
		else {
			return 2;
		}
		
	}
	else if (Operation == "H" || Operation == "Home") {
		Go_To_Home();
		action = "--The user with name " + this->username + " went to homepage";
		GigaBet::Add_New_Action(action);
		return 1;
	}
	else if (Operation == "T" || Operation == "Toggle") {
		Change_Price_Display();
		action = "--The user with name " + this->username + " changed price display";
		GigaBet::Add_New_Action(action);
		return 1;
	}
	else if (Operation == "X" || Operation == "Exit") {
		action = "--The user with name " + this->username + " exited the system";
		GigaBet::Add_New_Action(action);
		return 0;
	}
	else if (Operation == "A" || Operation == "Account") {
		action="--The user with name "+ this->username +" visited his account"+ Visit_Account(*this);
		GigaBet::Add_New_Action(action);
		return 1;
	}
	else if (Operation == "P" || Operation == "Place" && GigaBet::Get_Current_location()->Get_Location_Type() == "Market") {
		action= "--The user with name " + this->username+ Place_New_Bet(*this);
		GigaBet::Add_New_Action(action);
		return 1;
	}
	else if (Operation == "Back" && GigaBet::Get_Current_location()->Get_Location_Type() != "Hierarchy") {
		Go_Back();
		action = "--The user with name " + this->username + " visited location " + GigaBet::Get_Current_location()->Get_path();
		GigaBet::Add_New_Action(action);
		return 1;
	}
	else {
		return 2;
	}
}

double Punter::Get_freebet(const unsigned int id) {
	return W.freebets[id];
}

void Punter::Set_Password(const string new_password) {
	password = new_password;
}
void Punter::Set_Username(const string new_username) {
	username = new_username;
}
Punter::Wallet Punter::Get_Wallet() {
	return W;
}
void Punter::Change_balance(const double new_balance) {
	W.balance =W.balance+new_balance;
}

string Punter::Wallet::Get_Freebets() 
{
	string freebets_str;

	for (int i = 0;i < freebets.size();i++) {
		if (i == freebets.size() - 1) {
			freebets_str = freebets_str + Convert_Number_To_String(freebets[i]);
		}
		else {
			freebets_str = freebets_str + Convert_Number_To_String(freebets[i]) + ",";
			
		}
	}
	return freebets_str;
}

void Punter::Wallet::Show_Freebets() {
	char c;

	for (unsigned int i = 0;i < freebets.size();i++) {
		c = putchar(97+i);
		cout << "." << freebets[i] <<endl<<endl;
	}
	cout <<"\n\n";
}

void Punter::Use_freebet(const int coupon_index) {
	W.freebets.erase(W.freebets.begin() + coupon_index);
}

void Punter::Add_freebet(const double coupon){
	W.freebets.push_back(coupon);
}

Punter::~Punter()
{
}
