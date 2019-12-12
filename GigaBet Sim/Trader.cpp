#include "Trader.h"
#include "User_Operations.h"
#include "Numeric_Functions.h"
#include "GigaBet.h"


Trader::Trader(int id, string name, string pass, string user_name):User(2,id,name,pass,user_name)
{
}
unsigned int Trader::Select_Operation(const string Operation) {
	if (Is_Integer(Operation)) {
		if (GigaBet::Get_Current_location()->Get_Location_Type() != "Market" && Got_To_Next_Category_User(Operation)) {
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
	else if (Operation == "B"||Operation == "Bets") {
		Show_Last_Bets();
		return 1;
	}
	else if (Operation == "F" || Operation == "Freebets") {
		Give_Coupon_To_User();
		return 1;
	}
	else if (Operation == "V" || Operation == "Void" && GigaBet::Get_Current_location()->Get_Location_Type()=="Market") {
		Void(*this);
		return 1;
	}
	else if (Operation == "S" || Operation == "Settle" && GigaBet::Get_Current_location()->Get_Location_Type() == "Market") {
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
string Trader::Get_Operations() {
	if (GigaBet::Get_Current_location()->Get_Location_Type() == "Market") {
		return "Select:\n\nB(Back) ,to go back\n\nH(Home), to return to the home screen\n\nT(Toggle), to switch view rates\n\nX(Exit), to exit the system\n\nB(Bets), to display the last 20 bets\n\nF(Freebets), to give a coupon to a user\n\nV(Void) to cancel a selection\n\nS(Settle)for market settlement\n\n";
	}
	else if (GigaBet::Get_Current_location()->Get_Location_Type() == "Hierarchy") {
		return "Select: \n\nthe ID of the node that you want to visit\n\nH(Home), to return to the home screen\n\nT(Toggle), to switch view rates\n\nX(Exit), to exit the system\n\nB(Bets), to display the last 20 bets\n\nF(Freebets), to give a coupon to a user\n\n";
	}
	else {
		return "Select: \n\nthe ID of the node that you want to visit\n\n(Back) ,to go back\n\nH(Home), to return to the home screen\n\nT(Toggle), to switch view rates\n\nX(Exit), to exit the system\n\nB(Bets), to display the last 20 bets\n\nF(Freebets), to give a coupon to a user\n\n";
	}
}

Trader::~Trader()
{
}
