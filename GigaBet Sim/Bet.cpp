#include "Bet.h"



Bet::Bet(const unsigned int id, const unsigned int id_of_user, const string node_s, const double bet, const char R):bet_id(id),user_id(id_of_user),node_id(node_s),stake(bet),Result(R)
{}


Bet::~Bet()
{
}

void Bet::Set_bet_id(const unsigned int new_bet_id) {
	bet_id=new_bet_id;
}

void Bet::Set_user_id(const unsigned int) {

}
void Bet::Set_node(const string new_node_id) {
	node_id = new_node_id;
}
void Bet::Set_stake(const double new_stake) {
	stake = new_stake;
}
void Bet::Set_Result(const char new_Result) {
	Result = new_Result;
}
unsigned int Bet::Get_bet_id() {
	return bet_id;
}
unsigned int Bet::Get_user_id() {
	return user_id;
}
string Bet::Get_node() {
	return node_id;
}

double Bet::Get_stake() {
	return stake;
}
char Bet::Get_Result() {
	return Result;
}