#include "GigaBet.h"
#include "User_Operations.h"
#include <iostream>
#include "Guest.h"

using namespace std;




Punter* Sign_Up_Page() {

	string new_fullname;
	string new_username;
	string new_password;
	
	Punter* P;

	cout << "Fullname:";
	getline(cin, new_fullname);
	cout << "Username:";
	getline(cin, new_username);
	if (GigaBet::Find_Username(new_username)==NULL) {
		cout << "Password:";
		cin >> new_password;
		if (new_password == "cancel") {
			cout << "You cant give cancel as password" << endl;
			return NULL;
		}
		else {
			P = new Punter(GigaBet::Get_Users_List().size()+1, new_fullname, new_password, new_username,"A",0,"");
			GigaBet::Add_Punter(*P);
			return P;
		}
	}
	else {
		cout << "Username already taken" << endl;
		return NULL;
	}
	

}

User* Login_Page() {


	string username;
	string password;
	unsigned int userid;
	User* U;
	Punter* P;

	cout << "Welcome to GigaBet!" << endl;
	cout << "Please give username and password to login.If you dont have account press anter or type guest:guest to login as guest\n" << endl;
	do {
		cout << "Username:";
		getline(cin, username);
		if (username == "" || username == "guest:guest") {
			return U = new Guest();
		}
		else if ((U= GigaBet::Find_Username(username))!=NULL) {
			if (U->Get_type() == 1) {
				P = GigaBet::Get_Punter(U->Get_user_id());
				if (P->Get_Status().at(0) == 'L') {
					cout << "You are locked" << endl;
					return NULL;
				}
			}
			cout << "Password:";
			getline(cin, password);
			if (password == U->Get_password()) {
				return U;
			}
			else {
				cout << "Wrong Password" << endl;
			}
		}
		else {
			cout << "Wrong Username" << endl;
		}
	} while (true);
}



	

void Show_Categories() 
{
	
	cout << GigaBet::Get_Current_location()->Show_Subcategories()<< endl;
	
}

void Show_Operations(User* user)
{
	cout<<user->Get_Operations();

}



void Show_Type_Odds()
{

	if (Selection::Get_Display())
		cout << "Odds type: fractional"<< endl;
	else {
		cout << "Odds type: decimal"<<endl;
	}

}


void Show_Location()
{
	cout << GigaBet::Get_Current_location()->Get_path() << endl;
}

unsigned int Select_User_Operation(const string input,User* U) 
{
	return U->Select_Operation(input);

}

void Show_Current_Status(User* user)
{
	
	
	cout << endl;
	cout << endl;
	Show_Location();
	cout << endl;
	cout << endl;
	Show_Type_Odds();
	cout << endl;
	cout << endl;
	Show_Operations(user);
	cout << endl;
	cout << endl;
	if (user->Get_type() == 3) {
		cout<<GigaBet::Get_Current_location()->Show_Hidden_Subcategories();
		cout << endl;
	}
	else {
		Show_Categories();
	}

}
