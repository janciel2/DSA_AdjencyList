#ifndef GRAPH_H
#define GRAPH_H

#define MAXSIZE 26
#define MAX 5

#include <stdbool.h>	
#include <stdio.h>
#define EMPTYSTRING " "

typedef char STRING[15];
typedef int StackList;
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
bool deleteEdge(Dictionary *dict, STRING vertex, STRING edge);
bool deleteVertex(Dictionary *dict, STRING vertex);
void DFS(Dictionary *dict);
int compareValues(STRING x, STRING y);
void push(StackList *stack, int *top, int val);
int pop(StackList *stack, int *top);
void enqueue(int *queue, int *front, int *rear, int val);
int dequeue(int *queue, int *front, int *rear);
void BFS(Dictionary *dict);


#endif
