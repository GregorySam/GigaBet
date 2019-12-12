#include "GigaBet.h"
#include <iostream>

using namespace std;




void Login_Page() {
	cout << "Username:" << endl;
	cout << "Password:" << endl;
}

void Sign_Up_Page() {
	cout << "Welcome to GigaBet!" <<endl;
	cout << "Please give username and password to login.If you dont have account press anter or type guest:guest to login as guest" << endl;
	cout << "Username:" << endl;
	cout << "Password:" << endl;
}

void Show_Categories() 
{
	if (GigaBet::Get_Current_location() == NULL) {
		for (int i = 1;i <= GigaBet::Get_hierarchy().Get_size();i++)
			cout << GigaBet::Get_hierarchy().Get_Category(i).Get_node_id() + "." + GigaBet::Get_hierarchy().Get_Category(i).Get_name() << endl;
	}
	else {
			cout << GigaBet::Get_Current_location()->Show_Subcategories()<< endl;

	}
	
}

void Show_Operations(User* user)
{
	user->Get_Operations();

}



void Show_Type_Odds(Node* Current_location)
{
	Selection *Sel;

	if (Current_location->Get_Category_Type()=="Selection") {
		Sel= dynamic_cast<Selection*>(Current_location);
		cout << "Odds type:" << Sel->Show_price() <<endl;
	}
	else {
		cout << "Odds type:" << endl;
	}

}

void Show_Location()
{
	if (GigaBet::Get_Current_location() == NULL) {
		cout << GigaBet::Get_hierarchy().Get_path() << endl;
	}
	else {
		cout << GigaBet::Get_Current_location()->Get_path() << endl;
	}



}
void Show_Current_Status() {

}
