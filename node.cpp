#include "node.h"
#include <sstream>
#include <istream>
#include <fstream>
#include <iostream>

//implicit const
Node::Node()
{
	name = "";
	next = NULL;
}

//explicit const
Node::Node(std::string n, int* v):next(NULL), name(n)
{
	int* value = (int*)malloc(sizeof(int)*6);
	for(int i = 0; i < 6; i++)
	{
		value[i] = v[i];
	}	
}

//copy const
Node::Node(const Node& other)
{
	int* value = (int*)malloc(sizeof(int)*6);
	name = other.name;
	for(int i = 0; i < 6; i++)
	{
		value[i] = other.value[i];
	}
	next = NULL;
}

//assignment op
Node& Node::operator=(const Node& other)
{
	//alias test
	if(this != &other)
	{
		name = other.name;
		for(int i = 0; i < 6; i++)
		{
			value[i] = other.value[i];
		}
		next = NULL;
	}
	return *this;
}

//destructor
Node::~Node()
{
	/*is this all?*/
	delete next;
}

/*friend fxns*/

/*Linked List class stuff*/

/*implicit const*/
LinkedList::LinkedList():head(NULL){}

/*destructor*/
LinkedList::~LinkedList()
{
	/*if list is empty*/
	if(head == NULL)
	{
		return;
	}
	Node* current = head;
	Node* temp;
	/*we know there will be 386 nodes...*/
	for(int i = 0; i < 386; i++)
	{
		temp = current->next;
		delete current;
		current = temp; 
	}
}

/*checks if empty*/
bool LinkedList::empty() const
{
	if(head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LinkedList::search(std::string poke)
{
	/*will turn to true if find pokemon*/
	bool worked = false;
	/*Node pointer to keep track of where we are in list*/
	Node* current;
	/*start at head of list*/
	current = head;
	/*if list isn't empty...*/
	if(!empty())
	{
		/*cycle through list until find match*/
		while(current->name != poke)
		{
			//advance one node down list
			current = current->next;
		}
		/*current should be nullptr if no match*/
		if(current != NULL)
		{
			/*call fxn to make changes to poke file*/
			
			worked = true;
		}
		
	}
	return worked;
}

/*pokemon class shit*/
Pokemon::Pokemon():name(""), left(NULL), right(NULL)
{
	int* atts = (int*)malloc(sizeof(int) * 6);
	for(int i = 0; i < 6; i++)
	{
		atts[i] = 0;
	}
}

Pokemon::Pokemon(std::string n, int* a)
{
	int* att =(int*) malloc(sizeof(int) * 6);
	atts = att;
	for(int i = 0; i < 6; i++)
	{
		atts[i] = a[i];
	}
	name = n;
	left = NULL;
	right = NULL;
}

void Pokemon::addEV(int* a)
{
	for(int i = 0; i < 6; i++)
	{
		/*simply add the EVs to the pokemon's attributes array*/
		atts[i] = atts[i] + a[i];
	}
}

//does the actual output to file
void Btree::saveHelper2(Pokemon* p, std::ofstream& ofs)
{
	//now do the actual writing to the file
	ofs << p->name << "; ";
	for(int i = 0; i < 6; i++)
	{
		ofs << p->atts[i] << " ";
	}
	ofs << "\n"; 
}


/*PREORDER*/
/*provides saveHelper2 with each pokemon object to write
to the outfile*/
void Btree::saveHelper1(Pokemon* p, std::ofstream& ofs)
{
	if(p == NULL)
	{
		return;
	}
	saveHelper2(p, ofs);
	saveHelper1(p->left, ofs);
	saveHelper1(p->right, ofs);
}


/*initializes everything for the save helper functions to do the
actual work*/
void Btree::save(std::string file)
{
	//open outputfile stream
	std::ofstream ofs;
	const char* fileC = (char*)malloc(sizeof(char) * file.length() + 1);
	fileC = file.c_str();
	ofs.open(fileC, std::ofstream::out);
	saveHelper1(head, ofs);
	/*can't release without error*/
//	free(fileC);
}
/*Btree class shit*/

Btree::Btree():head(NULL){}

/*Don't need explicit const*/

/*loads all pokemon from specified file. Will end up creating a number
of pokemon objects which will be stored in a binary tree sorted by name*/
void Btree::loadPokemon(std::string file)
{
	const char* fileC = new char[file.length() + 1];
	fileC = file.c_str();
	//open file stream
	std::ifstream ifs;
	ifs.open(fileC, std::ifstream::in);
	
	//put inside loop
	//??
	//create string stream to store info.
		//get the line from file containing pokemon name and ev's
	std::string line;
	while(std::getline(ifs, line))
	{
		std::istringstream iss;
	//	put contents of string(line) into stringstream(iss)
		iss.str(line);
		//create two strings to put name and atts in separately
		std::string nameTemp;
		std::string atts3;
		std::istringstream attsTemp;
		//extract info from iss that has info from file
		//get name
		std::getline(iss, nameTemp, ';');
		//get atts
		std::getline(iss, atts3, '\n');	
		attsTemp.str(atts3);
		int* attsTemp2 = (int*)malloc(sizeof(int) * 6);
		//put contents of attsTemp(istringstream) into attsTemp2
		//which is the same type as pokemon object data member
		for(int i = 0; i < 6; i++)
		{
			attsTemp >> attsTemp2[i]; 
		}
		//now create pokemon object
		Pokemon* p = new Pokemon(nameTemp, attsTemp2);
		free(attsTemp2);
		//store pokemon in btree
		store(p);
	}
	ifs.close();	
//	delete[] fileC;
}

/*overload << operator for pokemon*/
std::ostream& operator<< (std::ostream& out, Pokemon& p)
{
	out << "Name:" << p.name << std::endl;
	out << "Health:" << p.atts[0] << std::endl;
	out << "Attack:" << p.atts[1] << std::endl;
	out << "Defense:" << p.atts[2] << std::endl;
	out << "Special Attack:" << p.atts[3] << std::endl;
	out << "Special Defense:" << p.atts[4] << std::endl;
	out << "Speed" << p.atts[5] << std::endl;
	return out;
} 

/*overload >> operator for pokemon*/
std::istream& operator>> (std::istream& in, Pokemon& p)
{
	std::cout << "Please enter name of new Pokemon:";
	in >> p.name;
	std::cout << std::endl << "Already acquired EVs for: Health:";
	in >> p.atts[0];
	std::cout << std::endl << "Attack:";
	in >> p.atts[1];
	std::cout << std::endl << "Defense:";
	in >> p.atts[2];
	std::cout << std::endl << "Special Attack:";
	in >> p.atts[3];
	std::cout << std::endl << "Special Defense:";
	in >> p.atts[4];
	std::cout << std::endl << "Speed";
	in >> p.atts[5];
	std::cout << std::endl;
	return in;
}

void Btree::store(Pokemon* p)
{
	if(head == NULL)
	{
		head = p;
		return;
	}
	Pokemon* current = head;
	while(1)
	{
		/*if name is less alphabetically and left node not occupied then store
		poke node there*/
		if(current->name.compare(p->name) < 0 && current->left == NULL)
		{
			current->left = p;
			return;
		}
		/*move down left of tree*/
		if(current->name.compare(p->name) < 0 && current->left != NULL)
		{
			current = current->left;
		}
		/*if name is greater alphbetically and right node not occupied then
		store poke node there*/
		else if(current->name.compare(p->name) > 0 && current->right == NULL)
		{
			current->right = p;
			return;
		}
		/*move down right branch of tree*/
		else if(current->name.compare(p->name) > 0 && current->right != NULL)
		{
			current = current->right;
		}
		else if(current->name.compare(p->name) == 0)
		{
			std::cout << "Theres a duplicate!" << std::endl;
			return;
		}
		//should never execute...
		else
		{		
			std::cout << "ERROR. Did not store pokemon" << std::endl;
			return;
		}
	}
}

Pokemon* Btree::search(std::string name)
{
	//if names match
	if(head->name.compare(name) == 0)
	{
		return head;
	}
	Pokemon* current = head;
	while(1)
	{
		//if no match in tree
		if(current->name == "")
		{
			return NULL;
		}
		else if(current->name.compare(name) == 0)
		{
			return current;
		}
		else if(current->name.compare(name) < 0 && current->left != NULL)
		{
			current = current->left;
		}
		else if(current->name.compare(name) > 0 && current->right != NULL)
		{
			current = current->right;
		}
		else if(current->name.compare(name) != 0 && current->right == NULL && current->left == NULL)
		{
			return NULL;
		}
	}
}

void LinkedList::add(Node* n)
{
	if(head == NULL)
	{
		head = n;
		return;
	}
	Node* current = head;
	/*search for last link in list*/
	while(current->next != NULL)
	{
		current = current->next;
	}
	/*assign newest node to list*/
	current->next = n;
}

void LinkedList::loadList()
{
	//format
	/*create pokemon, add to list. Many times. Thats it!*/
	
	int* evs = (int*)malloc(sizeof(int) * 6);
	//zero out array
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[3] = 1;
	Node* bulbasaur = new Node("Bulbasaur", evs);
	//add pokemon to linked list
	add(bulbasaur);
	//zero out array again for reuse
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[3] = 1;
	evs[4] = 1;
	Node* ivysaur = new Node("Ivysaur", evs);
	add(ivysaur);
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}	
	evs[3] = 2;
	evs[4] = 1;
	Node* venusaur = new Node("Venusaur", evs);
	add(venusaur);
	//
 	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
       evs[5] = 1;
	Node* charmander = new Node("Charmander", evs);
	add(charmander);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[3] = 1;
	evs[5] = 1;
	Node* charmeleon = new Node("Charmeleon", evs);
	add(charmeleon);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[3] = 3;
	Node* charizard = new Node("Charizard", evs);
	add(charizard);
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[2] = 1;
	Node* squirtle = new Node("Squirtle", evs);
	add(squirtle);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[2] = 1;
	evs[4] = 1;
	Node* wartortle = new Node("Wartortle", evs);
	add(wartortle);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[4] = 3;
	Node* blastoise = new Node("Blastoise", evs);
	add(blastoise);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[0] = 1;
	Node* caterpie = new Node("Caterpie", evs);
	add(caterpie);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[2] = 2;
	Node* metapod = new Node("Metapod", evs);
	add(metapod);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[3] = 2;
	evs[4] = 1;
	Node* butterfree = new Node("Butterfree", evs);
	add(butterfree);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 1;
	Node* weedle = new Node("Weedle", evs);
	add(weedle);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[2] = 2;
	Node* kakuna = new Node("Kakuna", evs);
	add(kakuna);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[1] = 2;
	evs[4] = 1;
	Node* beedrill = new Node("Beedrill", evs);
	add(beedrill);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 1;
	Node* pidgey = new Node("Pidgey", evs);
	add(pidgey);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 2;
	Node* pidgeotto = new Node("Pidgeotto", evs);
	add(pidgeotto);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 3;
	Node* pidgeot = new Node("Pidgeot", evs);
	add(pidgeot);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 1;
	Node* rattata = new Node("Rattata", evs);
	add(rattata);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 2;
	Node* raticate = new Node("Raticate", evs);
	add(raticate);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 1;
	Node* spearow = new Node("Spearow", evs);
	add(spearow);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 2;
	Node* fearow = new Node("Fearow", evs);
	add(fearow);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[1] = 1;
	Node* ekans = new Node("Ekans", evs);
	add(ekans);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[1] = 2;
	Node* arbok = new Node("Arbok", evs);
	add(arbok);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 2;
	Node* pikachu = new Node("Pikachu", evs);
	add(pikachu);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 3;
	Node* raichu = new Node("Raichu", evs);
	add(raichu);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[2] = 1;
	Node* sandshrew = new Node("Sandshrew", evs);
	add(sandshrew);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[2] = 2;
	Node* sandslash = new Node("Sandslash", evs);
	add(sandslash);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[0] = 1;
	Node* nidoran_girl = new Node("Nidoran_girl", evs);
	add(nidoran_girl);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[0] = 2;
	Node* nidorina = new Node("Nidorina", evs);
	add(nidorina);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[0] = 3;
	Node* nidoqueen = new Node("Nidoqueen", evs);
	add(nidoqueen);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[1] = 1;
	Node* nidoran_boy = new Node("Nidoran_boy", evs);
	add(nidoran_boy);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[1] = 2;
	Node* nidorino = new Node("Nidorino", evs);
	add(nidorino);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[1] = 3;
	Node* nidoking = new Node("Nidoking", evs);	
	add(nidoking);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[0] = 2;
	Node* clefairy = new Node("Clefairy", evs);
	add(clefairy);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[0] = 3;
	Node* clefable = new Node("Clefable", evs);
	add(clefable);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 1;
	Node* vulpix = new Node("Vulpix", evs);
	add(vulpix);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}	
	evs[4] = 1;
	evs[5] = 1;
	Node* ninetails = new Node("Ninetails", evs);
	add(ninetails);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[0] = 2;
	Node* jigglypuff = new Node("Jigglypuff", evs);
	add(jigglypuff);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[0] = 3;
	Node* wigglytuff = new Node("Wigglytuff", evs);
	add(wigglytuff);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 1;
	Node* zubat = new Node("Zubat", evs);
	add(zubat);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 2;
	Node* golbat = new Node("Golbat", evs);
	add(golbat);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[3] = 1;
	Node* oddish = new Node("Oddish", evs);
	add(oddish);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[3] = 2;
	Node* gloom = new Node("Gloom", evs);
	add(gloom);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[3] = 3;
	Node* vileplume = new Node("Vileplume", evs);
	add(vileplume);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[1] = 1;
	Node* paras = new Node("Paras", evs);
	add(paras);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[1] = 2;
	evs[2] = 1;
	Node* parasect = new Node("Parasect", evs);
	add(parasect);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[4] = 1;
	Node* venonat = new Node("Venonat", evs);
	add(venonat);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[3] = 1;
	evs[5] = 1;
	Node* venomoth = new Node("Venomoth", evs);
	add(venomoth);
	//
	for(int i = 0; i < 6; i++)
	{
		evs[i] = 0;
	}
	evs[5] = 1;
	Node* diglett = new Node("Diglett", evs);
	add(diglett);
	//
}
