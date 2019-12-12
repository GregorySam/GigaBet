#pragma once
#include <string>
#include <vector>

using namespace std;

class Node;
////////////////LOCATION/////////////////////////////////
class Location 
{
protected:
	string path;
public:
	virtual void Add_Node(Node&);
	virtual string Show_Hidden_Subcategories();
	virtual void Remove_Subcategory(const unsigned int);
	virtual string Get_Location_Type();
	virtual unsigned int Get_size();
	virtual void Add_Location(const string, const string= "");
	virtual string Show_Subcategories();
	virtual Node* Get_Subcategory(const unsigned int);
	void Set_path(const string);
	virtual string Get_path();
	~Location();
	Location(const string);
};
///////////////////////////////////////////////////////
//////////////////////////////////\n\nODE////////////////////////////////////////////////
class Node:public Location													
{																					
protected:
	bool Hidden;
	int node_id;
	string node;
	string name;
public:
	virtual void Set_Hidden_Nodes();
	bool Get_Hidden_State();
	void Change_Hidden_State(bool);
	void Set_node(const unsigned int);
	void Set_name(const string);
	virtual string Get_name();
	virtual int Get_node_id();
	virtual string Get_node();
	Node(const int,const string,const string,const string);
	virtual ~Node();
};
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////SELECTION//////////////////////////////////////////
class Selection :public Node
{
private:
	static bool display_price_s;
	struct Price {
		double price_d;
		string price_s;
	};
	Price P;
public:
	
	static bool Get_Display();
	string Get_Location_Type();
	static void Switch_Display();
	string Show_price();
	void Set_price(double);
	string Get_price_s();
	double Get_price_d();
	Selection(const int, const string, const string, const string,const string);
	~Selection();

};
/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////MARKET////////////////////////////////////////////////
class Market :public Node
{
private:
	vector <Selection> selections;
public:
	void Set_Hidden_Nodes();
	string Show_All_Nodes();
	void Add_Selection(Selection&);
	void Remove_Subcategory(const unsigned int);
	void Add_Location(const string,const string= "");
	Node* Get_Subcategory(const unsigned int);
	string Get_Location_Type();
	string Show_Hidden_Subcategories();
	string Show_Subcategories();
	void Add_Selection(const string,const string);
	unsigned int Get_size();
	Market(const int, const string, const string, const string);
	~Market();
	
};
/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////EVENT//////////////////////////////////////////////////
class Event:public Node
{
private:
	vector <Market> markets;
public:
	void Set_Hidden_Nodes();
	string Show_All_Nodes();
	void Add_Market(Market&);
	void Remove_Subcategory(const unsigned int);
	void Add_Location(const string, const string = "");
	string Get_Location_Type();
	string Show_Hidden_Subcategories();
	string Show_Subcategories();
	void Add_Market(const string);
	unsigned int Get_size();
	Node* Get_Subcategory(const unsigned int);
	Event(const int, const string, const string, const string);
	~Event();

};
////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////SUBCATEGORY/////////////////////////////////////////////////
class SubCategory :public Node 
{
private:
	vector <Event> events;
public:
	void Set_Hidden_Nodes();
	string Show_All_Nodes();
	void Remove_Subcategory(const unsigned int);
	void Add_Location(const string, const string = "");
	string Get_Location_Type();
	string Show_Hidden_Subcategories();
	void Add_Event(Event&);
	string Show_Subcategories();
	void Add_Event(const string);
	unsigned int Get_size();
	Node* Get_Subcategory(const unsigned int);
	SubCategory(const int, const string, const string, const string);
	~SubCategory();
};
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////CATEGORY//////////////////////////////////////////////////////
class Category :public Node
{
private:
	vector <SubCategory> subcategories;
public:
	void Set_Hidden_Nodes();
	void Add_SubCategory(SubCategory&S);
	string Show_All_Nodes();
	void Remove_Subcategory(const unsigned int);
	void Add_Location(const string, const string = "");
	string Get_Location_Type();
	string Show_Hidden_Subcategories();
	string Show_Subcategories();
	void Add_Subcategory(const string);
	unsigned int Get_size();
	Node* Get_Subcategory(const unsigned int);
	Category(int,const string,const  string, const string);
	~Category();
};
/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////HIERARCHY////////////////////////////////////////////
class Hierarchy:public Location
{
private:
	vector <Category> categories;
public:
	string Show_All_Nodes();
	void Remove_Subcategory(const unsigned int);
	void Add_Location(const string, const string = "");
	string Show_Hidden_Subcategories();
	void Add_Category(Category&);
	string Show_Subcategories();
	string Get_Location_Type();
	string Get_path();
	void Add_Category(const string);
	unsigned int Get_size();
	Node* Get_Subcategory(const unsigned int);
	Hierarchy();
	~Hierarchy();
};
////////////////////////////////////////////////////////////////////////////////////////
