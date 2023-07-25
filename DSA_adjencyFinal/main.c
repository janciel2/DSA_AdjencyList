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
	added = addVertex(dict, "Malaysia");
	added = addVertex(dict, "Korea");
	added = addVertex(dict, "Japan");
	
	
	visualizeDictionary(dict);
	displayDictionary(dict);
	
	added = addEdge(dict, "Philippines", "Thailand");
	added = addEdge(dict, "Philippines", "Mexico");
	added = addEdge(dict, "Mexico", "Malaysia");
	added = addEdge(dict, "Malaysia", "Korea");
	added = addEdge(dict, "Malaysia", "Japan");
	added = addEdge(dict, "Japan", "Malaysia");
	added = addEdge(dict, "Japan", "Korea");
	added = addEdge(dict, "Korea", "Thailand");
	added = addEdge(dict, "Korea", "Malaysia");
	added = addEdge(dict, "Thailand", "Korea");
	added = addEdge(dict, "Thailand", "Philippines");
	displayDictionary(dict);
	
//	deleteEdge(dict, "Philippines", "Thailand");
//	displayDictionary(dict);
//	
//	deleteVertex(dict, "Philippines");
	
	displayDictionary(dict);
	
	printf("\n\nDFS:\n\n");
	DFS(dict);
	
	printf("\n\nBFS:\n\n");
	BFS(dict);
	return 0;
}
