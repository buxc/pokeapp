#include "node.h"

/**
	Driver for the program. Contains all UI elements.

	@author Vasili Papastrat
	@version 1.0 5/23/2014

*/

int main()
{	std::cout <<"/************************************************************/ \n" << std::endl;
	std::cout <<"Hello! This command line tool keeps track of your pokemon's EVs for you." << std::endl << "Developed by Vasili Papastrat(vpapastrat@hotmail.com)in early 2014."<<std::endl<<"IMPORTANT: For every yes/no question, respond with either 'y' or 'n'!" << std::endl;
	std::cout <<" \n /************************************************************/" << std::endl;


	/*start everything off by creating and loading pokemon
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
	/*get output file name*/
	std::cout << "Which file to save to later on?:";
	std::cin >> outFile;
	/*now start master loop*/
	bool keep_going = true;
	while(keep_going)
	{	/*get name of pokemon to add ev's to*/
		std::cout << "Enter name of your pokemon:";
		std::string name;
		std::cin >> name;
		Pokemon* pokemon = tree->search(name);
		/*if user's pokemon doesn't exist*/
		if(pokemon == NULL)
		{
			std::cout << "Pokemon not loaded. Create new pokemon?:";		
			char create;
			std::cin >> create;
			/*if user wants to create new pokemon*/
			if(create == 'y')
			{	/*create it*/
				Pokemon* p = new Pokemon();
				/*assign name previously entered*/
				p->name = name;
				/*get attributes*/
				std::cin >> *p;
				/*store pokemon in binary tree*/
				tree->store(p);
			}
		}
		/*if user's pokemon does exist*/
		else
		{
			int times;
			char choice;
			bool contin = true;
			while(contin)
			{
				std::cout << "Which pokemon did you defeat?:";
				std::string defeated;
				std::cin >> defeated;
				std::cout << "How many times?:";
				std::cin >> times;
				/*if search fxn fails, execute if statement*/
				if(!list->search(defeated, pokemon, times))
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
