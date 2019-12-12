#include "Guest.h"
#include "User_Operations.h"
#include "Numeric_Functions.h"
#include "GigaBet.h"



Guest::Guest():User(0,0,"","","guest")
{
}
unsigned int Guest::Select_Operation(const string Operation) {
	if (GigaBet::Get_Current_location()->Get_Location_Type() != "Market" && Is_Integer(Operation)){
		if (Got_To_Next_Category_User(Operation) && GigaBet::Get_Current_location()->Get_Location_Type() != "Market") {
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
	else if (Operation == "X" || Operation == "Exit"){
		return 0;
	}
	else if (Operation == "Back" && GigaBet::Get_Current_location()->Get_Location_Type() != "Hierarchy") {
		Go_Back();
		return 1;
	}
	else {
		return 2;
	}

}
string Guest::Get_Operations() {
	if (GigaBet::Get_Current_location()->Get_Location_Type() == "Market") {
		return "Select:\n\n(Back) ,to go back\n\nH(Home), to return to the home screen\n\nT(Toggle), to switch view rates\n\nX(Exit), to exit the system\n\n";
	}
	else if (GigaBet::Get_Current_location()->Get_Location_Type() == "Hierarchy") {
		return "Select: \n\nthe ID of the node that you want to visit\n\nH(Home), to return to the home screen\n\nT(Toggle), to switch view rates\n\nX(Exit), to exit the system\n\n";

	}
	else {
		return "Select: \n\nthe ID of the node that you want to visit\n\n(Back) ,to go back\n\nH(Home), to return to the home screen\n\nT(Toggle), to switch view rates\n\nX(Exit), to exit the system\n\n";
	}
	
}
Guest::~Guest()
{
}
