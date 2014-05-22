#include "node.h"

int main()
{	/*start everything off by creating and loading pokemon
	linked list*/
	LinkedList* list = new LinkedList();
	list->loadList();	
	Btree* tree = new Btree();
	/*get input file name*/
	std::string inFile, outFile;
	std::cout << "Have an input file:(y or n):";
	char input;
	std::cin >> input;
	/*if user has input file, proceed normally*/
	if(input == 'y')
	{
		std::cout << "Enter input file name(contains your pokemon):";
		std::cin >> inFile;
		/*load pokemon from input file. If input file doesn't exist, fxn
		will return false and the program will end*/
		if(!tree->loadPokemon(inFile))
		{
			return 0;
		}
	}
	/*if user doesn't have input file*/
	else
	{
		/*I guess don't do anything?*/
	}
	std::cout << std::endl;
	/*get output file name*/
	std::cout << "Which file to save to later on?:";
	std::cin >> outFile;
	std::cout << std::endl;
	/*now start master loop*/
	bool keep_going = true;
	while(keep_going)
	{	/*get name of pokemon to add ev's to*/
		std::cout << "Enter name of your pokemon:";
		std::string name;
		std::cin >> name;
		std::cout << std::endl;
		Pokemon* pokemon = tree->search(name);
		/*if user's pokemon doesn't exist*/
		if(pokemon == NULL)
		{
			std::cout << "Pokemon not loaded. Create new pokemon of same name?(enter either 'y' or 'n':";			
			char create;
			std::cin >> create;
			/*if user wants to create new pokemon*/
			if(create == 'y')
			{	/*create it*/
				Pokemon* p = new Pokemon();
				/*assign name previously entered*/
				p->name = name;
				/*store pokemon in binary tree*/
				tree->store(p);
			}
		}
		/*if user's pokemon does exist*/
		else
		{
			char choice;
			bool contin = true;
			while(contin)
			{
				std::cout << "Which pokemon did you defeat?:";
				std::string defeated;
				std::cin >> defeated;
				/*if search fxn fails, execute if statement*/
				if(!list->search(defeated, pokemon))
				{
					std::cout << "Pokemon does not exist. Please make sure you spell the name correctly." << std::endl;
				}
				std::cout << "Again?(enter either 'y' or 'n':";
				std::cin >> choice;
				if(choice != 'y')
				{
					contin = false;
				}			
			}
		}
		/*prompt to do again for another pokemon?*/
		std::cout << "Repeat for a separate pokemon?:";
		char choice;
		std::cin >> choice;
		if(choice != 'y')
		{
			keep_going = false;
		}	
       	}
	/*ask to save*/
	std::cout << "Save changes?:";
	std::cin >> input;
	if(input == 'y')
	{
		tree->save(outFile);
		std::cout << "Changes saved. Thanks for using this!" << std::endl;
		return 0;	
	}
	else
	{
		std::cout << "Changes not saved. Thanks for using this!" << std::endl;
		return 0;
	}
}
