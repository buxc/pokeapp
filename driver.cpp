#include "node.h"

int main()
{	/*start everything off by creating and loading pokemon
	linked list*/
	LinkedList* list = new LinkedList();
	list->loadList();
	/*get input file name*/
	std::string inFile, outFile;
	std::cout << "Enter input file name(contains your pokemon):";
	std::cin >> inFile;
	std::cout << std::endl;
	/*get output file name*/
	std::cout << "Which file to save to later on?:";
	std::cin >> outFile;
	std::cout << std::endl;
	Btree* tree = new Btree();
	/*load pokemon from input file*/
	tree->loadPokemon(inFile);
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
	}
	Pokemon* s, *q, *r, *t;
	s = tree->search("Ajax");
	q = tree->search("Eileen");
	r = tree->search("Bitch");
	t = tree->search("Percy");
	Pokemon v = *q;
	Pokemon b = *t;
	Pokemon u = *r;
	Pokemon p = *s;
	std::cout << p << u << q << v << std::endl;
       	tree->save(outFile);
	return 0;
}
