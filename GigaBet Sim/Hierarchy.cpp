#include "Hierarchy.h"
#include <iostream>
#include "Numeric_Functions.h"
#include "GigaBet.h"

using namespace std;

////////////////LOCATION/////////////////////

Location::Location(const string path_name) :path(path_name){}

Location::~Location(){}

Node* Location::Get_Subcategory(const unsigned int id)
{return NULL;}

unsigned int Location::Get_size() {return 0;}

void Location::Remove_Subcategory(const unsigned int index)
{return;}

string Location::Get_Location_Type() 
{return "";}

void Location::Add_Node(Node & N) {
	return;
}

void Location::Add_Location(const string node_name,const string p)
{
}

string Location::Show_Subcategories() { return ""; }

string Location::Show_Hidden_Subcategories(){ return ""; }

void Location::Set_path(const string new_path) 
{
	path = new_path;
}

string Location::Get_path()
{
	return path;
}
//////////////////////////////////////////////////


///////////////////////////////////////////
////////////\n\nODE/////////////////////////
Node::Node(const int  id_num, const string n, const string s_node, const string path_name) :Location(path_name),node_id(id_num), node(s_node), name(n),Hidden(false)
{}



string Node::Get_name() 
{
	return name;
}
int Node::Get_node_id() 
{
	return node_id;
}

void Node::Set_Hidden_Nodes() { return; }

void Node::Change_Hidden_State(bool f)
{
	Hidden = f;
}

bool Node::Get_Hidden_State() 
{
	return Hidden;
}

string Node::Get_node() 
{
	return node;
}


void Node::Set_node(unsigned int new_id) 
{
	node_id = new_id;
	if (this->Get_Location_Type() == "Category") {
		node.erase(0, node.find('.') );
		node.insert(0, Convert_Number_To_String((double)new_id));

	}
	else {
		
		node.erase(node.find_last_of('.')+1);
		node=node+ Convert_Number_To_String((double)new_id);
	}
	

}

void Node::Set_name(const string new_name)
{	
	int i = path.length() - 1;
	while (path[i] != '/') { path.erase(i);i--; }
	name = new_name;
	path = path + name;
	Set_path(path);
}
Node::~Node(){}
////////////////////////////////////////////////
////////////SELECTION/////////////////////////
Selection::Selection(const int  id_num, const  string n, const  string s_node, const string path_name, const  string p) :Node(id_num,n,s_node,path_name)
{
	P.price_s= p;
	P.price_d = Convert_StringFraction_To_Decimal(p);
	
}

bool Selection::display_price_s = true;

string Selection::Get_price_s() 
{
	return P.price_s;

}

void Selection::Set_price(double new_price) {
	P.price_d = new_price;
}

string Selection::Get_Location_Type()
{
	return "Selection";
}

double Selection::Get_price_d() 
{
	return P.price_d;
}

string Selection::Show_price()
{
	if (display_price_s) {
		return P.price_s;
	}
	else {
		return Convert_Number_To_String(P.price_d);
	}
}

bool Selection::Get_Display() {
	return display_price_s;
}

void Selection::Switch_Display() 
{
	if (display_price_s) {
		display_price_s = false;
	}
	else {
		display_price_s = true;
	}
}

Selection::~Selection()
{}

/////////////////////////////////////////////////////////////////////////
////////////MARKET///////////////////////////////
Market::Market(const int  id_num, const  string n, const  string s_node, const string path_name) :Node(id_num, n, s_node,path_name)
{}


Node* Market::Get_Subcategory(const unsigned int ID)
{
	return &selections[ID - 1];
}

void Market::Set_Hidden_Nodes() {
	if (selections.size()==0) {
		this->Change_Hidden_State(true);
	}
}

string Market::Get_Location_Type()
{
	return "Market";
}

string Market::Show_Hidden_Subcategories()
{
	string str;

	for (unsigned int i = 0;i < selections.size();i++) {
		if (!selections[i].Get_Hidden_State()) {
			str = str +"|"+ Convert_Number_To_String(selections[i].Get_node_id()) + "." + selections[i].Get_name() + " - " + selections[i].Show_price() + "\n\n";
		}
		else {
			str = str + "[Hidden]" + Convert_Number_To_String(selections[i].Get_node_id()) + "." + selections[i].Get_name() + " - " + selections[i].Show_price() + "\n\n";
		}

	}
	return str;
}

string Market::Show_Subcategories() 
{
	string str;
	unsigned int count=0;

	for (unsigned int i = 0;i < selections.size();i++) {
		if (!selections[i].Get_Hidden_State()) {
			count++;
			str = str + Convert_Number_To_String((double)count) + "." + selections[i].Get_name() + " - " + selections[i].Show_price() + "\n\n";
		}
		
	}
	return str;
}

string Market::Show_All_Nodes()
{
	string nodes;


	for (unsigned int i = 0;i < selections.size();i++) {
		if (selections[i].Get_Hidden_State()) {
			nodes = nodes +"[Hidden]"+ selections[i].Get_node() + " " + selections[i].Get_name() + "#" + selections[i].Get_price_s() + "\n";
		}
		else {
			nodes = nodes + selections[i].Get_node() + " " + selections[i].Get_name() + "#" + selections[i].Get_price_s() + "\n";
		}
		

	}
	return nodes;
}

void Market::Add_Location(const string node_name, const string p)
{
	Add_Selection(node_name, p);
}

void Market::Remove_Subcategory(const unsigned int id) 
{
	selections.erase(selections.begin()+id-1);
	for (unsigned int i = id - 1;i < selections.size();i++) {
		selections[i].Set_node(i+1);
	}
}

void Market::Add_Selection(Selection& S) {
	selections.push_back(S);
}

void Market::Add_Selection(const string name,const string price) 
{	
	string new_node;
	new_node=node + "."+Convert_Number_To_String(selections.size()+1);
	Selection new_selection(selections.size() + 1,name,new_node,path+"/"+name,price);
	selections.push_back(new_selection);
}
Market::~Market()
{}
unsigned int Market::Get_size() {
	return selections.size();
}

///////////////////////////////////////////////////////////////////
////////////EVENT///////////////////////////////////
Event::Event(const int  id_num, const  string n, const  string s_node, const string path_name) :Node(id_num, n, s_node, path_name)
{}

void Event::Add_Market(const string name)
{
	string new_node;
	new_node = node + "." + Convert_Number_To_String(markets.size() + 1);
	Market new_market(markets.size() + 1, name, new_node, path + "/" + name);
	Add_Market(new_market);
}

void Event::Add_Location(const string node_name, const string p)
{
	Add_Market(node_name);
}

void Event::Set_Hidden_Nodes() {
	unsigned int count=0;

	for (unsigned int i = 0;i < markets.size();i++) {
		markets[i].Set_Hidden_Nodes();
		if (markets[i].Get_Hidden_State()) {
			count++;
		}
	}
	if (count == markets.size()) {
		this->Change_Hidden_State(true);
	}


}

string Event::Show_Hidden_Subcategories()
{
	string str;

	for (unsigned int i = 0;i < markets.size();i++) {
		if (!markets[i].Get_Hidden_State()) {
			str = str + "|" + Convert_Number_To_String(markets[i].Get_node_id()) + "." + markets[i].Get_name() +"\n\n";
		}
		else {
			str = str + "[Hidden]" + Convert_Number_To_String(markets[i].Get_node_id()) + "." + markets[i].Get_name() +"\n\n";
		}

	}
	return str;
}

void Event::Remove_Subcategory(const unsigned int id)
{
	markets.erase(markets.begin() + id - 1);
	for (unsigned int i = id - 1;i < markets.size();i++) {
		markets[i].Set_node(i + 1);
	}
}

string Event::Show_All_Nodes()
{
	string nodes;


	for (unsigned int i = 0;i < markets.size();i++) {
		if (markets[i].Get_Hidden_State()) {
			nodes = nodes + "[Hidden]" + markets[i].Get_node() + " " + markets[i].Get_name() + "\n" + markets[i].Show_All_Nodes();
		}
		else {
			nodes = nodes + markets[i].Get_node() + " " + markets[i].Get_name() + "\n" + markets[i].Show_All_Nodes();
		}

	}
	return nodes;
}

void Event::Add_Market(Market& M) {

	markets.push_back(M);
}
	

string Event::Show_Subcategories()
{
	string str;
	unsigned int count=0;
	
	for (unsigned int i = 0;i < markets.size();i++) {
		if (!markets[i].Get_Hidden_State()) {
			count++;
			str = str + Convert_Number_To_String((double)count) + "." + markets[i].Get_name() + "\n\n";
		}
		
	}
	return str;
}

string Event::Get_Location_Type()
{
	return "Event";
}
Node* Event::Get_Subcategory(const unsigned int ID) 
{
	return &markets[ID - 1];
}

Event::~Event() {
}
unsigned int Event::Get_size() {
	return markets.size();
}
///////////////////////////////////////////////////////////////////////
//////////SUBCATEGORY//////////////////////////////////
SubCategory::SubCategory(const int  id_num, const  string n, const  string s_node, const string path_name) :Node(id_num, n, s_node, path_name)
{}

string SubCategory::Show_Hidden_Subcategories()
{
	string str;
	for (unsigned int i = 0;i < events.size();i++) {
		if (!events[i].Get_Hidden_State()) {
			str = str + "|" + Convert_Number_To_String(events[i].Get_node_id()) + "." + events[i].Get_name() + "\n\n";
		}
		else {
			str = str + "[Hidden]" + Convert_Number_To_String(events[i].Get_node_id()) + "." + events[i].Get_name() + "\n\n";
		}

	}
	return str;
}

string SubCategory::Show_Subcategories()
{
	string str;
	unsigned int count=0;

	for (unsigned int i = 0;i < events.size();i++) {
		if (!events[i].Get_Hidden_State()) {
			count++;
			str = str + Convert_Number_To_String((double)count) + "." + events[i].Get_name() + "\n\n";
		}
		
	}
	return str;
}

void SubCategory::Set_Hidden_Nodes() {
	unsigned int count = 0;

	for (unsigned int i = 0;i < events.size();i++) {
		events[i].Set_Hidden_Nodes();
		if (events[i].Get_Hidden_State()) {
			count++;
		}
	}
	if (count == events.size()) {
		this->Change_Hidden_State(true);
	}
}

string SubCategory::Show_All_Nodes()
{
	string nodes;


	for (unsigned int i = 0;i < events.size();i++) {
		if (events[i].Get_Hidden_State()) {
			nodes = nodes + "[Hidden]" + events[i].Get_node() + " " + events[i].Get_name() + "\n" + events[i].Show_All_Nodes();
		}
		else {
			nodes = nodes + events[i].Get_node() + " " + events[i].Get_name() + "\n" + events[i].Show_All_Nodes();
		}

	}
	return nodes;
}

void SubCategory::Add_Location(const string node_name, const string p)
{
	Add_Event(node_name);
}

string SubCategory::Get_Location_Type()
{
	return "Subcategory";
}

void SubCategory::Add_Event(Event& E) {
	events.push_back(E);
}

void SubCategory::Remove_Subcategory(const unsigned int id)
{
	events.erase(events.begin() + id - 1);
	for (unsigned int i = id - 1;i < events.size();i++) {
		events[i].Set_node(i + 1);
	}
}

void SubCategory::Add_Event(const string name)
{
	string new_node;
	new_node = node + "." + Convert_Number_To_String(events.size() + 1);
	Event new_event(events.size() + 1, name, new_node, path + "/" + name);
	events.push_back(new_event);
}
Node* SubCategory::Get_Subcategory(const unsigned int ID)
{
	return &events[ID-1];
}

unsigned int SubCategory::Get_size()
{
	return events.size();
}
SubCategory::~SubCategory(){}
//////////////////////////////////////////////////////////////////////
///////////CATEGORY////////////////////////////


Category::Category(const int  id_num, const  string n, const  string s_node, const string path_name) :Node(id_num, n, s_node, path_name)
{}

void Category::Add_Subcategory(const string name) 
{
	string new_node;
	new_node = node+ Convert_Number_To_String(subcategories.size() + 1);
	SubCategory new_subcategory(subcategories.size() + 1, name, new_node, path + "/" + name);
	subcategories.push_back(new_subcategory);
}

void Category::Set_Hidden_Nodes() {
	unsigned int count = 0;

	for (unsigned int i = 0;i < subcategories.size();i++) {
		subcategories[i].Set_Hidden_Nodes();
		if (subcategories[i].Get_Hidden_State()) {
			count++;
		}
	}
	if (count == subcategories.size()) {
		this->Change_Hidden_State(true);
	}
}

string Category::Get_Location_Type()
{
	return "Category";
}


void Category::Add_Location(const string node_name, const string p)
{
	Add_Subcategory(node_name);
}

void Category::Remove_Subcategory(const unsigned int id)
{
	subcategories.erase(subcategories.begin() + id - 1);
	for (unsigned int i = id - 1;i < subcategories.size();i++) {
		subcategories[i].Set_node(i + 1);
	}
}

string Category::Show_Hidden_Subcategories()
{
	string str;
	for (unsigned int i = 0;i < subcategories.size();i++) {
		if (!subcategories[i].Get_Hidden_State()) {
			str = str + "|" + Convert_Number_To_String(subcategories[i].Get_node_id()) + "." + subcategories[i].Get_name() + "\n\n";
		}
		else {
			str = str + "[Hidden]" + Convert_Number_To_String(subcategories[i].Get_node_id()) + "." + subcategories[i].Get_name() + "\n\n";
		}

	}
	return str;
}
void Category::Add_SubCategory(SubCategory& S) {
	subcategories.push_back(S);

}

string Category::Show_All_Nodes()
{
	string nodes;


	for (unsigned int i = 0;i < subcategories.size();i++) {
		if (subcategories[i].Get_Hidden_State()) {
			nodes = nodes +"[Hidden]"+subcategories[i].Get_node() + " " + subcategories[i].Get_name() + "\n" + subcategories[i].Show_All_Nodes();
		}
		else {
			nodes = nodes + subcategories[i].Get_node() + " " + subcategories[i].Get_name() + "\n" + subcategories[i].Show_All_Nodes();
		}
		

	}
	return nodes;
}

string Category::Show_Subcategories()
{
	string str;
	unsigned int count=0;

	for (unsigned int i = 0;i < subcategories.size();i++) {
		if (!subcategories[i].Get_Hidden_State()) {
			count++;
			str = str + Convert_Number_To_String((double)count) + "." + subcategories[i].Get_name() + "\n\n";
		}
	}
	return str;
}

unsigned int Category::Get_size()
{
	return subcategories.size();
}

Node* Category::Get_Subcategory(const unsigned int ID)
{
	return &subcategories[ID - 1];
}

Category::~Category(){}

///////////////////////////////////////////////////
///////////////////HIERARCHY////////////////////
Hierarchy::Hierarchy():Location("Location:/GiagaBet/"){}

string Hierarchy::Get_Location_Type() 
{
	return "Hierarchy";
}


string Hierarchy::Show_Hidden_Subcategories()
{
	string str;
	for (unsigned int i = 0;i < categories.size();i++) {
		if (!categories[i].Get_Hidden_State()) {
			str = str + "|" + Convert_Number_To_String(categories[i].Get_node_id()) + "." + categories[i].Get_name() + "\n\n";
		}
		else {
			str = str + "[Hidden]" + Convert_Number_To_String(categories[i].Get_node_id()) + "." + categories[i].Get_name() + "\n\n";
		}

	}
	return str;
}

void Hierarchy::Add_Category(Category& C) {

	categories.push_back(C);
}

string Hierarchy::Show_Subcategories()

{
	string str;
	unsigned int count=0;

	for (unsigned int i = 0;i < categories.size();i++) {
		if (!categories[i].Get_Hidden_State()) {
			count++;
			str = str + Convert_Number_To_String((double)count) + "." + categories[i].Get_name() + "\n\n";
		}
	}
	return str;
}

void Hierarchy::Add_Location(const string node_name, const string p)
{
	Add_Category(node_name);
}

string Hierarchy::Show_All_Nodes()
{
	string nodes;
	

	for (unsigned  int i = 0;i < categories.size();i++) {
		if (categories[i].Get_Hidden_State()) {
			nodes = nodes +"[Hidden]"+categories[i].Get_node() + " " + categories[i].Get_name() + "\n" + categories[i].Show_All_Nodes();
		}
		else {
			nodes = nodes + categories[i].Get_node() + " " + categories[i].Get_name() + "\n" + categories[i].Show_All_Nodes();
		}
		

	}
	return nodes;
}

void Hierarchy::Remove_Subcategory(const unsigned int id)
{
	categories.erase(categories.begin() + id - 1);
	for (unsigned int i = id - 1;i < categories.size();i++) {
		categories[i].Set_node(i + 1);
	}
}

void Hierarchy::Add_Category(string name)
{
	string new_node;
	new_node = Convert_Number_To_String(categories.size() + 1)+".";
	Category new_category(categories.size() + 1, name, new_node, path + name);
	categories.push_back(new_category);
}
Node* Hierarchy::Get_Subcategory(const unsigned int ID)
{
	return &categories[ID - 1];
}
string Hierarchy::Get_path() 
{
	return path;
}
unsigned int Hierarchy::Get_size()
{
	return categories.size();
}

Hierarchy::~Hierarchy()
{}
