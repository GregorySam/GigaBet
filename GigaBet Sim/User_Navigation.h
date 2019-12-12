#pragma once
#include "GigaBet.h"
#include <iostream>

using namespace std;



Punter* Sign_Up_Page();

	

User* Login_Page();




void Show_Categories();

void Show_Operations(User* user);




void Show_Type_Odds();


void Show_Location();


unsigned int Select_User_Operation(const string, User*);

void Show_Current_Status(User* user);

