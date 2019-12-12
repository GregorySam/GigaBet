#include "Director.h"
#include "User_Operations.h"
#include "Numeric_Functions.h"
#include "GigaBet.h"
#include "Files_Management.h"

Director::Director(int id, string name, string pass, string user_name):User(3, id, name, pass, user_name)
{
}
unsigned int Director::Select_Operation(string Operation) {
	if (Is_Integer(Operation)) {
		if (GigaBet::Get_Current_location()->Get_Location_Type() != "Market" && Got_To_Next_Category_Director(Operation)) {
			return 1;
		}
		else {
			return 2;
		}
	}
	else if (Operation == "H" || Operation == "Home") {
		Go_To_Home();
		return 1;
	}
	else if (Operation == "T" || Operation == "Toggle") {
		Change_Price_Display();
		return 1;
	}
	else if (Operation == "X" || Operation == "Exit") {
		return 0;
	}
	else if (Operation == "B" || Operation == "Bets") {
		Show_Last_Bets();
		return 1;
	}
	else if (Operation == "F" || Operation == "Freebets") {
		Give_Coupon_To_User();
		return 1;
	}
	else if (Operation == "S" || Operation == "Save") {
		Write_Bets_File();
		Write_Hierarchy_File();
		Write_Actions_File();
		Write_Users_File();
		Write_Profit();
		cout << "\n\nSystem was saved\n" << endl;

		return 1;
	}
	else if (Operation == "L" || Operation == "Logs") {
		Show_25_last_actions();
		return 1;
	}
	else if (Operation == "U" || Operation == "Users") {
		Users_Management();
		return 1;
	}
	else if (Operation == "Visibility") {
		Change_Visibility_Of_Node();
		return 1;
	}
	else if (Operation == "R" || Operation == "Rename") {
		Rename_Node();
		return 1;
	}
	else if (Operation == "N" || Operation == "New") {
		New_Node();
		return 1;
	}
	else if (Operation == "C" || Operation == "Copy") {
		Copy_Node();
		return 1;
	}
	else if (Operation == "D" || Operation == "Delete") {
		Remove_Node();
		return 1;
	}
	else if (Operation == "V" || Operation == "Void" && GigaBet::Get_Current_location()->Get_Location_Type() == "Market") {
		Void(*this);
		return 1;
	}
	else if (Operation == "Settle" && GigaBet::Get_Current_location()->Get_Location_Type() == "Market") {
		Settle(*this);
		return 1;
	}
	else if (Operation == "Back" && GigaBet::Get_Current_location()->Get_Location_Type() != "Hierarchy") {
		Go_Back();
		return 1;
	}
	else {
		return 2;
	}
	
}
string Director::Get_Operations() {
	if (GigaBet::Get_Current_location()->Get_Location_Type() == "Market") {
		return  "Select: \n\n(Back) ,to go back\n\nH(Home), to return to the home screen\n\nT(Toggle), to switch view rates\n\nX(Exit), to exit the system\n\nB(Bets), to display the last 20 bets\n\nF(Freebets), to give a coupon to a user\n\nL(Logs), to display the last 25 actions in the system\n\nU(Users), for user management\n\n(Visibility), to switch node visibility\n\nR(Rename),to rename a node\n\nN(New), to create a new node\n\nC(Copy), to copy a node(as non - visible)\n\nD(Delete), for node deletion\n\nS(Save),to save current system state\n\nV(Void) to cancel a selection\n\n(Settle)for market settlement\n\n";
	}
	else if (GigaBet::Get_Current_location()->Get_Location_Type() == "Hierarchy") {
		return  "Select: \n\nthe ID of the node that you want to visit\n\nH(Home), to return to the home screen\n\nT(Toggle), to switch view rates\n\nX(Exit), to exit the system\n\nB(Bets), to display the last 20 bets\n\nF(Freebets), to give a coupon to a user\n\nL(Logs), to display the last 25 actions in the system\n\nU(Users), for user management\n\n(Visibility), to switch node visibility\n\nR(Rename),to rename a node\n\nN(New), to create a new node\n\nC(Copy), to copy a node(as non - visible)\n\nD(Delete), for node deletion\n\nS(Save),to save current system state\n\n";
	}
	else {
		return  "Select: \n\nthe ID of the node that you want to visit\n\n(Back) to go to previous category\n\nH(Home), to return to the home screen\n\nT(Toggle), to switch view rates\n\nX(Exit), to exit the system\n\nB(Bets), to display the last 20 bets\n\nF(Freebets), to give a coupon to a user\n\nL(Logs), to display the last 25 actions in the system\n\nU(Users), for user management\n\n(Visibility), to switch node visibility\n\nR(Rename),to rename a node\n\nN(New), to create a new node\n\nC(Copy), to copy a node(as non - visible)\n\nD(Delete), for node deletion\n\nS(Save),to save current system state\n\n";
	}
}


Director::~Director()
{
}
