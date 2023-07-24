#ifndef GRAPH_H
#define GRAPH_H

#define MAXSIZE 26
#define MAX 5

#include <stdbool.h>	
#include <stdio.h>
#define EMPTYSTRING " "

typedef char STRING[15];
//MAIN ARRAY
typedef struct
{
	STRING *edge;	
	int count; 
	int max;
} List;

typedef struct
{
	List arrayList;
	STRING vertex;
} ArrayList;

typedef ArrayList Dictionary;

void initDict(Dictionary *dict); 
bool addVertex(Dictionary *dict, STRING vertex);
int hash(STRING vertex);
void displayDictionary(Dictionary *dict);
void visualizeDictionary(Dictionary *dict);
bool addEdge(Dictionary *dict, STRING vertex, STRING edge);
bool deleteEdge(Dictionary *dict, STRING vertex, STRING edge)


#endif