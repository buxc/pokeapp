//#ifndef POKEAPP_H
//#define POKEAPP_H

#include <iostream>
#include <string>

/*These nodes will be stored in a linked list and
have 3 datas: name of pokemon(string), type ev given(char),
and ev value(int)*/

/*The attributes Health, Attack, Defense, Special Attack, Special Defense,
and Speed are represented by a int array of size 6, where array[0] is the
ev value given for Health, array[1] = ev value given for Attack, and so on*/
class Node{
    public:
	Node* next;
	std::string name;
	int* value;
	/*methods*/
	/*implicit const*/
	Node();
	/*explicit*/
	Node(std::string n, int* v);
	/*copy const*/
	Node(const Node& other);
	/*assignment op*/
	Node& operator=(const Node& other);
	/*destructor*/
	~Node();
	/*input and output fxns*/
	friend std::ostream& operator<<(std::ostream &out, Node node);
	friend std::istream& operator>>(std::istream &in, Node node);
};

/*pokemon class that will be saved/loaded to/from files*/
class Pokemon{
    public:
	std::string name;
	Pokemon* left;
	Pokemon* right;
	int* atts;
	Pokemon();
	Pokemon(std::string n, int* a);
	void addEV(int* a);
	/*saves pokemon to file, parameter is name of file*/
	friend std::ostream& operator<<(std::ostream &out, Pokemon& p);
	friend std::istream& operator>>(std::istream &in, Pokemon& p);	
};	
/*Linked List class that will contain all the nodes*/
class LinkedList{
    public:
	/*first node, should be bulbasaur*/
	Node* head;
	LinkedList();
	~LinkedList();
	/*checks if list is empty*/
	bool empty() const;
	/*searches for pokemon through name, returns bool to
	say if successful or not*/	
	bool search(std::string poke, Pokemon* p);
	void loadList();
	void add(Node* n);
};

//#endif	

class Btree{
    public:
	Pokemon* head;
	Btree();
	void saveHelper1(Pokemon* p, std::ofstream& ofs);
	void saveHelper2(Pokemon* p, std::ofstream& ofs);
	void save(std::string file);
	Pokemon* search(std::string name);
	void store(Pokemon* p);
	/*Load pokemon from file, parameter is name of file*/
	bool loadPokemon(std::string file);

};
