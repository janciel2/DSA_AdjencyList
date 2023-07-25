#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
	Dictionary *dict;
	bool added;
	dict = malloc(sizeof(Dictionary) * 26);
	initDict(dict);
	
	
	added = addVertex(dict, "Philippines");
	added = addVertex(dict, "Thailand");
	added = addVertex(dict, "Mexico");
	
	visualizeDictionary(dict);
	displayDictionary(dict);
	
	added = addEdge(dict, "Philippines", "Thailand");
	added = addEdge(dict, "Thailand", "Mexico");
	displayDictionary(dict);
	
//	deleteEdge(dict, "Philippines", "Thailand");
	displayDictionary(dict);
	
	deleteVertex(dict, "Philippines");
	
	displayDictionary(dict);
	return 0;
}
