#include "node.h"
#include <sstream>
#include <istream>
#include <fstream>
#include <iostream>
/**
	Function definitions of all functions, not just of Node.

	@author Vasili Papastrat
	@version 1.0 5/23/2014
*/




/**
	Implicit constructor for Node. Sets name
	data member to empty string "" and next data
	member to NULL
*/
Node::Node()
{
	name = "";
	next = NULL;
}

/**
	Explicit constructor for Node. Allocates
	int* value onto heap and sets EVs.

	@param string for pokemon's name
	@param pointer to int array of evs to be copied
	@return pointer to object

*/
Node::Node(std::string n, int* v):next(NULL), name(n)
{
	value = (int*)malloc(sizeof(int)*6);
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

/**
	Destructor for LinkedList
*/
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

/**
	Checks if list of reference pokemon is empty
	@return "true" if empty, "false" if not
*/
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
/**
	Keeps the user's pokemon from exceeding 510 total EVs.
	
	@return a boolean "true" if pokemon has less than 510,
	"false" if have reached limit

*/
bool Pokemon::check()
{
	int total = 0;
	/*Sum all the EVs*/
	for(int i = 0; i < 6; i++)
	{
		total += atts[i];
	}
	/*If the total is greater than or equal to 510*/
	if(total >= 510)
	{
		return false;
	}
	else
	{
		return true;
	}
}
/**
	Searches LinkedList of ref. pokemon for match user provided,
	based on name. If finds a match will add ref's EVs to user's
	EVs.
	
	@param string of ref pokemon's name.
	@param Pokemon* pointing to user's pokemon which we want
	to add EVs to.
	@param number of times we want to add ref's EVs to user's.
	@return whether we found a match to ref pokemon or not.
*/
bool LinkedList::search(std::string poke, Pokemon* p, int times)
{
	/*Node pointer to keep track of where we are in list*/
	Node* current;
	bool end = true;
	/*start at head of list*/
	current = head;
	/*if list isn't empty...*/
	if(!empty())
	{
		/*cycle through list until find match*/
		while(current != NULL && current->name != poke && end)
		{	/*if at end of list*/
			if(current->next == NULL)
			{
				end = false;
				current = NULL;
			}
			//advance one node down list
			if(end)
			{
				current = current->next;
			}
		}
		/*If we found the pokemon*/
		if(current != NULL)
		{
			for(int h = 0; h < times; h++)
			{
				/*Add ev's to user's pokemon*/
				for(int i = 0; i < 6; i++)
				{
					if(p->check())
					{
						p->atts[i] += current->value[i];
						if(p->atts[i] >= 255)
						{
							p->atts[i] = 255;
						}
					}
				}
				
			}	
			std::cout << "EVs added." << std::endl;
			std::cout << "/***************/"<< std::endl;
			std::cout << *p;
			std::cout << "/***************/" << std::endl;
			return true;
		}
		
	}
	return false;
}

/*pokemon class shit*/
Pokemon::Pokemon():name(""), left(NULL), right(NULL)
{
	atts = (int*)malloc(sizeof(int) * 6);
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

/**
	Does the actual writing to outfile.
	
	@param Pokemon* to pokemon currently writing to file.
	@param outputfile stream.
	
*/
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


/**
	Performs PREORDER search on btree storing all user's pokemon.
	Provides fxn saveHelper2 with each pokemon object needing to be
	written to the outfile.
	
	@param Pokemon* current position in btree.
	@param outputfile stream
*/
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


/**
	Initializes everything for the save helper functions to do the
	actual saving.
	
	@param string name of output file
*/
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

/**
	Loads all pokemon from specified file. Will end up creating a number
	of pokemon objects which will be stored in a binary tree sorted by name.

	@param name of inputfile.
	@return whether opened inputfile successfully or not
*/
bool Btree::loadPokemon(std::string file)
{
	const char* fileC = new char[file.length() + 1];
	fileC = file.c_str();
	//open file stream
	std::ifstream ifs;
	ifs.open(fileC, std::ifstream::in);
	/*check if file opened*/
	if(!ifs.is_open())
	{
		std::cout << "Error: Something wrong with input file. ABORT" << std::endl;
		return false;
	}
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
	return true;
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
	out << "Speed:" << p.atts[5] << std::endl;
	return out;
} 

/*overload >> operator for pokemon*/
std::istream& operator>> (std::istream& in, Pokemon& p)
{
	std::cout << "Please enter name of new Pokemon:";
	in >> p.name;
	std::cout << "Already acquired EVs for: Health:";
	in >> p.atts[0];
	std::cout <<  "Attack:";
	in >> p.atts[1];
	std::cout << "Defense:";
	in >> p.atts[2];
	std::cout << "Special Attack:";
	in >> p.atts[3];
	std::cout << "Special Defense:";
	in >> p.atts[4];
	std::cout << "Speed:";
	in >> p.atts[5];
	std::cout << std::endl;
	return in;
}

/**
	Stores user's pokemon from inputfile or create during session in
	binary tree sorted by name.
	
	@param Pokemon* current pokemon to be stored.
*/
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

/**
	Searches btree of user's pokemon for a specific one user specified.
	Returned pointer to pokemon will be used to add EVs.

	@param name of user's desired pokemon.
	@return pointer to desired pokemon or NULL if not found.
	
*/
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

/**
	Adds one Node to LinkedList, always at the end.

	@param pointer to Node to be stored.
*/
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

/**
	Loads LinkedList of reference pokemon(Nodes) that is accessed
	everytime the user wants to add EVs to pokemon.
*/
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
	//
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
