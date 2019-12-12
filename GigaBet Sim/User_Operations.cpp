#include <string>
#include <iostream>
#include "Punter.h"
#include "GigaBet.h"
#include "Numeric_Functions.h"
#include <fstream>
#include "Files_Management.h"

using namespace std;







string Visit_Account(Punter &P) {

	string actions;
	string choice;
	bool flag = true;

	
		
	do {
		cout << "\n--------------------------------Acount----------------------------------" << endl;
		cout << "\n\nPunter:" << P.Get_name() << "\n\nAvailable balance : " << P.Get_Wallet().balance << "\n\nAvailable coupons :" << P.Get_Wallet().Get_Freebets() << endl;

		cout << "\n\n\n\nChoices : \n\nR(Rename), change player name \n\nP(Password), to change password \n\nB(Bets), to view the betting history \n\nD(Deposit), for account filling and balance increase or type 'b' or 'back' to go back"<<endl;
		cin >> choice;
		if (choice != "R" && choice != "Rename" && choice != "P" && choice != "Password" && choice != "B" && choice != "Bets" && choice != "D" && choice != "Deposit"&&choice!="b"&&choice!="back") {
			cout << "Unknown command" << endl;
		}
		else if (choice == "b" || choice == "back") {
			return actions;
		}
		if (choice == "Rename" || choice == "R") {
			cout << "\n-------------------------Rename-------------------------" << endl;
			string new_name;
			flag = true;
			do {
				cout << "Give new name or type 'b' or 'back' to go back" << endl;
				cin >> new_name;
				if (new_name == "b" || new_name == "back") {
					flag = false;
				}
				else if (GigaBet::Find_Username(new_name) == NULL && new_name != "guest") {
					P.Set_Username(new_name);
					cout << "Name was changed" << endl;
					actions = actions + ",changed his username to " + P.Get_name();
					flag = false;
					
				}
				else {
					cout << "Forbidden name" << endl;
				}
			} while (flag);
		}
		else if (choice == "P" || choice == "Password") {
			cout << "\n-------------------------Change Password-------------------------" << endl;
			string password;
			string new_password;
			flag = false;
			do {
				cout << "Give two times the password or type 'b' or 'back' to go back" << endl;
				do {
					cout << "Give password:";
					cin >> password;
					if (P.Get_password() != password) { cout << "Wrong password!" << endl; }
					if (password == "back" || password == "b") { flag = true; }
				} while (P.Get_password() != password && !flag);
				if (!flag) {
					do {
						cout << "Give password:";
						cin >> password;
						if (P.Get_password() != password) { cout << "Wrong password!" << endl; }
						if (password == "back" || password == "b") { flag = true; }
					} while (P.Get_password() != password && !flag);
				}
			} while (P.Get_password() != password && !flag);
			if (!flag) {
				cout << "Give new password:";
				cin >> new_password;
				P.Set_Password(new_password);
				cout << "\n Password was changed" << endl;
				actions = actions + ",changed his password";
			}
		}
		else if (choice == "B" || choice == "Bets") {
			cout << "\n-------------------------Bets-------------------------" << endl;
			cout << "\n"<<endl;
			P.Show_Bet_History();
		}
		else if (choice == "D" || choice == "Deposit") {
			cout << "\n-------------------------Deposit-------------------------" << endl;
			flag = true;
			do {
				string new_balance;
				cout << "Add more balance or  type 'b' or 'back' to go back" << endl;
				cout << "Add more balance:";
				cin >> new_balance;
				if (Is_Number(new_balance)) {
					P.Change_balance(Convert_String_To_Number(new_balance));
					cout << "Balance was changed\n\n" << endl;
					actions = actions + ",changed his balance to " + Convert_Number_To_String(P.Get_Wallet().balance);
				}
				else if (new_balance == "back" || new_balance == "b") {
					flag = false;
				}
				else {
					cout << "Wrong input" << endl;
				}
			} while (flag);
		}
	} while (true);
}


unsigned int True_ID(Location* L,unsigned int id_num) {

	for (unsigned int i = 1;i <= L->Get_size();i++) {
		if (L->Get_Subcategory(i)->Get_Hidden_State()) {
			id_num++;
		}
	}
	return id_num;

}

void Go_Back() {
	GigaBet::Go_To_Previous_Location();
}

bool Got_To_Next_Category_User(string ID) {

	unsigned int id_num;
	Location* L;
	L = GigaBet::Get_Current_location();

	id_num = (unsigned int)Convert_String_To_Number(ID);
	if (id_num <= 0) { return false; }
	id_num = True_ID(L, id_num);
	if (id_num <= GigaBet::Get_Current_location()->Get_size()){
		GigaBet::Set_Current_location(id_num);
		return true;
	}
	else {
		cout << "Wrong ID" << endl;
		return false;
	}
	
}

bool Got_To_Next_Category_Director(string ID) {
	unsigned int id_num;

	id_num = (unsigned int)Convert_String_To_Number(ID);
	if (id_num <= GigaBet::Get_Current_location()->Get_size() && id_num>0) {
		GigaBet::Set_Current_location(id_num);
		return true;
	}
	else {
		cout << "Wrong ID" << endl;
		return false;
	}
}


void Go_To_Home() {
	GigaBet::Set_Current_location(0);
}



void Change_Price_Display() {
	Selection::Switch_Display();
}





void Show_Last_Bets() 
{
	GigaBet::Show_20_Last_Bets();
}



void Give_Coupon_To_User() {
	string username;
	Punter *P;
	bool flag = true;
	string coupon;

	do{
		do {
			cout << "First give the username and then the coupon or type 'cancel' or 'c' to go back" << endl;
			cout << "Give username:";
			cin >> username;
			P= GigaBet::Find_Punter(username);
			if (P==NULL && username != "c" && username != "cancel") {
				cout << "Username not found or unknown input" << endl;
			}
			else if (username == "c" || username == "cancel") {
				return;
			}
		} while (P == NULL);
		do {
			cout << "Give coupon in decimal or integer with '.' or type 'c' or 'cancel' to go back"<<endl;
			cin >> coupon;
			if (!Is_Number(coupon) && coupon != "c" && coupon != "cancel") {
				cout << "Unknown input" << endl;
			}
			else if (coupon == "c" || coupon == "cancel") {
				flag = false;
			}
			else if(Is_Number(coupon)){
				P->Add_freebet(Convert_String_To_Number(coupon));
				cout << "Freebet was given to " << username << endl;
				flag = false;
			}
		} while (flag);
	} while (true);
}

string Place_New_Bet(Punter &P) {

	string actions;
	Location* l;
	string input1,input2;
	char ch;
	bool flag = false;
	double stake;
	unsigned int num;

	l = GigaBet::Get_Current_location();

	do {
		cout << "Your balance is: " << P.Get_Wallet().balance << "\n\n";
		cout << "Select the selection you want to place the bet or type 'cancel' to exit" << endl;
		cin >> input1;	
		if (Is_Integer(input1)) {
			num = (unsigned int)Convert_String_To_Number(input1);
			num = True_ID(l, num);
			if ((num <= l->Get_size())) {
				do {
					cout << "Your freebets are: " << endl;
					P.Get_Wallet().Show_Freebets();
					cout << "Place new stake or select freebet or type 'cancel' to exit: " << endl;
					cin >> input2;
					if (Is_Number(input2)) {
						stake = Convert_String_To_Number(input2);
						if (stake > P.Get_Wallet().balance) {
							cout << "Give lower stake you dont have enough" << endl;
							flag = true;
						}
						else if (P.Get_Wallet().balance == 0) {
							cout << "Go to your (Account) and fill your wallet" << endl;
							flag = true;
						}
						else {
							P.Change_balance(-stake);
							Bet B(GigaBet::Get_Bets().size() + 1, P.Get_user_id(), l->Get_Subcategory(num)->Get_node(), stake, '-');
							P.Add_New_Bet(B);
							GigaBet::Add_Bet(B);
							cout << "Stake was placed" << endl;
							actions = actions + ",placed a bet with stake " + Convert_Number_To_String(stake) + " at location " + l->Get_Subcategory(num)->Get_path();
							flag = false;
						}
					}
					else if (input2.size() == 1 && input2[0] >= 97 && P.Get_Wallet().freebets.size()>0) {
						ch = input2[0];
						for (unsigned int i = 0;i < P.Get_Wallet().freebets.size();i++) {
							if (ch == (97 + i)) {
								Bet B(GigaBet::Get_Bets().size() + 1, P.Get_user_id(), l->Get_Subcategory(num)->Get_node(), P.Get_Wallet().freebets[i], '-');
								P.Add_New_Bet(B);
								GigaBet::Add_Bet(B);
								cout << "Freebet was used" << endl;
								actions = actions + ",placed a bet with a coupon of " + Convert_Number_To_String(P.Get_freebet(i)) + " at location " + l->Get_Subcategory(num)->Get_path();
								P.Use_freebet(i);
								flag = false;
								break;
							}
						}
					}
					else if (input2 == "cancel") {
						flag = false;
					}
					else {
						cout << "Wrong input" << endl;
						flag = true;
					}
				} while (flag);
			}
		}
		else if (input1 == "cancel") {
			return actions;
		}
		else {
			cout << "Wrong Input" << endl;
		}
	} while (true);
	
	
}

void Users_Management() {

	string input;
	Punter*P;
	bool flag=true;
	ifstream users_file;

	do {
		cout << "Type 'V' or 'View' to show users list,'S' or 'Search' to find a user,'L' or 'Lock' to switch block status of a user or type 'cancel' to go back" << endl;
		cin >> input;
		if (input == "V" || input == "View") {
			Show_Users_File();
		}
		else if (input == "S" || input == "Search") {
			cout << "Type the username or a substring of username to search or type 'cancel' to go back" << endl;
			cin >> input;
			if (input == "cancel") {
			}
			else {
				vector <User*> U;
				U = GigaBet::Get_Users_With_String(input);
				GigaBet::Show_Users(U);
			}
			
		}
		else if (input == "L" || input == "Lock") {
			do {
				cout << "Type the username of the user you want to lock or 'cancel' to go back" << endl;
				cin >> input;
				if (input != "cancel" && (P= GigaBet::Find_Punter(input))!=NULL) {
					if (P->Get_Status().at(0) == 'A') {
						cout << "Insert block comment or 'cancel' to go back" << endl;
						cin >> input;
						if (input == "cancel") {
							flag = false;
						}
						else{
							P->Set_Status("L," + input);
							cout << "Lock state of user changed" << endl;
						}
					}
					else if (P->Get_Status().at(0) == 'L') {
						cout << "Insert comment if you want or 'cancel' to go back" << endl;
						cin >> input;
						if (input == "cancel") {
							flag = false;
						}
						else {
							if (input == "") {
								P->Set_Status("A");
								cout << "Lock state of user changed" << endl;
							}
							else {
								P->Set_Status("A," + input);
								cout << "Lock state of user changed" << endl;
							}
						}
					}
				}
				else if (input == "cancel") {
					flag = false;
				}
				else {
					cout << "Username not found" << endl;
				}
			} while (flag);
		}
		else if (input == "cancel") {
			return;
		}
	} while (true);

}



void Show_25_last_actions() {

	 int i = GigaBet::Get_Actions_History_Size() - 1;

	while (i >=((int)GigaBet::Get_Actions_History_Size() - 26) && (i >= 0)) {
		cout << GigaBet::Get_Action(i) << endl;
		i--;
	}
}

void Rename_Node() {

	Location *l;
	string input_1;
	string input_2;
	int num;
	bool flag = true;

	l = GigaBet::Get_Current_location();
	do {
		l->Show_Subcategories();
		cout << "Give the id of the node that you want to  change the name or type 'cancel' ,'c','abort','a',to cancel" << endl;
		cin >> input_1;
		
		if (Is_Integer(input_1) && (num = (unsigned int)Convert_String_To_Number(input_1)<= l->Get_size())) {
			do {
				cout << "Insert new node name:" << endl;
				cin >> input_2;
				if (input_1 == "cancel" || input_1 == "c" || input_1 == "abort" || input_1 == "a") {
					flag = false;
				}
				else {
					l->Get_Subcategory(num)->Set_name(input_2);
					flag = false;
				}
			} while (flag);

		}
		else if (input_1 == "cancel" || input_1 == "c" || input_1 == "abort" || input_1 == "a") {
			return;
		}
		else {
			cout << "Wrong input" << endl;
		}
	} while (true);
}

void New_Node() {

	Location *l;
	string input_1;
	string input_2;
	bool flag = true;
	
	l = GigaBet::Get_Current_location();
	do {
		l->Show_Subcategories();
		cout << "Give the name of the node you want to add or type 'cancel' ,'c','abort','a',to cancel" << endl;
		cin >> input_1;
		if (input_1 == "cancel" || input_1 == "c" || input_1 == "abort" || input_1 == "a") {
			return;
		}
		else {
			if (l->Get_Location_Type() == "Market") {
				do {
					cout << "Give the odd of the selection in fraction or type 'cancel' ,'c','abort','a',to cancel" << endl;
					cin >> input_2;
					if (Is_Fraction(input_2)) {
						l->Add_Location(input_1, input_2);
						flag = false;
					}
					else if (input_2 == "cancel" || input_2 == "c" || input_2 == "abort" || input_2 == "a") {
						flag = false;
					}
					else {
						cout << "Wrong input" << endl;
					}
				} while (flag);
			}
			else {
				l->Add_Location(input_1);
			}
		}
	} while (true);

}


void Remove_Node() {

	Location *l;
	string input;
	unsigned int new_id;
	bool flag=true;

	l = GigaBet::Get_Current_location();

	do {
		cout<<"\n\n"<<l->Show_Hidden_Subcategories();
		cout << "Select the id of the node you want to remove or type 'cancel' ,'c','abort','a',to cancel" << endl;
		cin >> input;
		if (Is_Integer(input)) {
			new_id = (int)Convert_String_To_Number(input);
			if (new_id <= l->Get_size()) {
				do {
					cout << "Are you sure you want to delete the node?Answer 'Y' for yes 'N' for no" << endl;
					cin >> input;
					if (input == "Y") {
						l->Remove_Subcategory(new_id);
						flag = false;
					}
					else if (input == "N") {
						flag = false;
					}
					else {
						cout << "Wrong input" << endl;
					}
				} while (flag);
				flag = true;
			}
			else {
				cout << "Wrong Input" << endl;
			}
		}
		else if (input == "cancel" || input == "c" || input == "abort" || input == "a") {
			return;
		}
		else {
			cout << "Wrong input" << endl;
		}
	} while (true);
	
}



void Copy_Node() 
{
	string input;
	unsigned int id;
	Location* l;

	l = GigaBet::Get_Current_location();
	do {
		l->Show_Subcategories();
		cout << "Select the id of the node you want to copy or type 'cancel' ,'c','abort','a',to cancel" << endl;
		cin >> input;
		if (Is_Integer(input)){
			id = (int)Convert_String_To_Number(input);
			if (id <= l->Get_size()) {
				if (l->Get_Location_Type() == "Hierarchy") {
					Category *C;
					Hierarchy* H;
					H = dynamic_cast<Hierarchy*>(l);
					C = dynamic_cast<Category*>(l->Get_Subcategory(id));
					Category Copied(*C);
					Copied.Set_node(l->Get_size() + 1);
					Copied.Set_name("-Copied" + C->Get_name());
					Copied.Change_Hidden_State(true);
					H->Add_Category(Copied);
				}
				else if (l->Get_Location_Type() == "Category") {
					SubCategory *S;
					Category* C;
					C = dynamic_cast<Category*>(l);
					S = dynamic_cast<SubCategory*>(l->Get_Subcategory(id));
					SubCategory Copied(*S);
					Copied.Set_node(l->Get_size() + 1);
					Copied.Change_Hidden_State(true);
					C->Add_SubCategory(Copied);
				}
				else if (l->Get_Location_Type() == "SubCategory") {
					Event* E;
					SubCategory* S;
					S = dynamic_cast<SubCategory*>(l);
					E = dynamic_cast<Event*>(l->Get_Subcategory(id));
					Event Copied(*E);
					Copied.Set_node(l->Get_size() + 1);
					Copied.Change_Hidden_State(true);
					S->Add_Event(Copied);
				}
				else if (l->Get_Location_Type() == "Event") {
					Market* M;
					Event* E;
					E = dynamic_cast<Event*>(l);
					M = dynamic_cast<Market*>(l->Get_Subcategory(id));
					Market Copied(*M);
					Copied.Set_node(l->Get_size() + 1);
					Copied.Change_Hidden_State(true);
					E->Add_Market(Copied);
				}
				else if (l->Get_Location_Type() == "Market") {
					Selection* S;
					Market* M;
					M = dynamic_cast<Market*>(l);
					S = dynamic_cast<Selection*>(l->Get_Subcategory(id));
					Selection Copied(*S);
					Copied.Set_node(l->Get_size() + 1);
					Copied.Change_Hidden_State(true);
					M->Add_Selection(Copied);
				}
				else {
					cout << "You cant copy here" << endl;
				}
			}
			else {
				cout << "Wrong Input" << endl;
			}
		}
		else if (input == "cancel" || input == "c" || input == "abort" || input == "a") {
			return;
		}
		else {
			cout << "Wrong input" << endl;
		}
	} while (true);
	

}

void Change_Visibility_Of_Node() {
	
	Location *l;
	string input;
	unsigned int id;


	l = GigaBet::Get_Current_location();
	do {
		l->Show_Subcategories();
		cout << "Give the id of the node you want to change the visibility or type 'cancel' ,'c','abort','a',to cancel" << endl;
		cin >> input;
		if (Is_Integer(input)) {
			id = (int)Convert_String_To_Number(input);
			if (id <= l->Get_size()) {
				l->Get_Subcategory(id)->Change_Hidden_State(!(l->Get_Subcategory(id)->Get_Hidden_State()));
			}
			else {
				cout << "Wrong Input" << endl;
			}
		}
		else if (input == "cancel" || input == "c" || input == "abort" || input == "a") {
			return;
		}
		else {
			cout << "Wrong Input" << endl;
		}
	} while (true);

}



void Void(User& U) 
{
	Location *l;
	string input1;
	unsigned int num;


	l = GigaBet::Get_Current_location();
	do {
		if (U.Get_type() == 2) {
			cout << l->Show_Subcategories();
		}
		else {
			cout << l->Show_Hidden_Subcategories();
		}
		cout << "Give the id of the node you want to void or type 'cancel' ,'c','abort','a',to cancel " << endl;
		cin >> input1;
		if (Is_Integer(input1)){
			num = (unsigned int)Convert_String_To_Number(input1);
			if (U.Get_type() == 2) {
				num = True_ID(l, num);
			}
			if (num<= l->Get_size()) {
				GigaBet::Set_Bet_Result('V', l->Get_Subcategory(num)->Get_node(),num);
			}
			else {
				cout << "Wrong Input" << endl;
			}
		}
		else if (input1 == "cancel" || input1 == "c" || input1 == "abort" || input1 == "a") {
			return;
		}
		else {
			cout << "Wrong Input" << endl;
		}
	} while (true);
}

void Settle(User& U) {

	
	Location *l;
	string input1;
	string input2;
	unsigned int num;
	bool flag = true;

	
	l = GigaBet::Get_Current_location();
	do {
		if (U.Get_type() == 2) {
			cout << l->Show_Subcategories();
		}
		else {
			cout << l->Show_Hidden_Subcategories();
		}
		cout << "Give the id of the node you want to settle type 'cancel' ,'c','abort','a',to cancel " << endl;
		cin >> input1;
		if (Is_Integer(input1)) {
			num = (unsigned int)Convert_String_To_Number(input1);
			if (U.Get_type() == 2) {
				num = True_ID(l, num);
			}
			if (num <= l->Get_size()) {
				do {
					cout << "Select  'W' for winning or 'L' for losing or type 'cancel' ,'c','abort','a',to cancel" << endl;
					cin >> input2;
					if (input2 == "W") {
						GigaBet::Set_Bet_Result('W', l->Get_Subcategory(num)->Get_node(), num);
						return;
					}
					else if (input2 == "L") {
						GigaBet::Set_Bet_Result('L', l->Get_Subcategory(num)->Get_node(), num);
						return;
					}
					else if (input2 == "cancel" || input2 == "c" || input2 == "abort" || input2 == "a") {
						flag = false;
					}
					else {
						cout << "Wrong Input" << endl;
					}
				} while (flag);
			}
			

		}
		else if (input1 == "cancel" || input1 == "c" || input1 == "abort" || input1 == "a") {
			return;
		}
		else {
			cout << "Wrong Input" << endl;
		}
	} while (true);


}

