#include "User_Navigation.h"
#include "Files_Management.h"
#include <string.h>






int main(int argc, char* argv[]) {

	string input;
	bool flag = true;
	unsigned int option;

	User *U;

	if (!Read_Hierarchy_File()) { return 0; }
	if (!Read_Users_File()) { return 0; }
	if (!Read_History_File()) { return 0; }
	if (!Read_Bets_File()) { return 0; }
	if (!Read_Profit()) { return 0; }
	


	if (argc == 1) {
		U = Login_Page();
		if (U == NULL) { return 0; }
		
	}
	else if (argc == 2 && !strcmp(argv[1], "-R")) {
		U = Sign_Up_Page();
		if (U == NULL) { return 0; }
	}
	else {
		return 0;
	}
	do {
		Show_Current_Status(U);
		cin >> input;
		option = Select_User_Operation(input, U);
		if (option== 2) {
			cout << "Operation failed" << endl;
		}
		else if (option == 0) {
			if (U->Get_type() == 0) {
				delete U;
			}
			flag = false;
		}
	} while (flag);
	if (U->Get_type() != 3) {
		Write_Bets_File();
		Write_Hierarchy_File();
		Write_Actions_File();
		Write_Users_File();
		Write_Profit();
	}
	

}