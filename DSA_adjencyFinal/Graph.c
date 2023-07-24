#include "Graph.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void initDict(Dictionary *dict)
{
	int i,v;
	for(i = 0; i < 26; i++)
		{
			strcpy(dict[i].vertex, EMPTYSTRING);
			dict[i].arrayList.max = MAX;
			dict[i].arrayList.count = 0;
			
			dict[i].arrayList.edge = malloc(sizeof(STRING) * MAX);
				for(v = 0; v < MAX; v++)
					{
						strcpy(dict[i].arrayList.edge[v], EMPTYSTRING);
					}
 			printf("%d : SUCCESSFULLY INITIALIZED\n",i);
 			printf("\n");
		}
}

bool addVertex(Dictionary *dict, STRING vertex)
{
	int hashVal = hash(vertex), i = 0;
	
	while(strcmp(dict[hashVal].vertex, EMPTYSTRING) != 0 && i < 26) //to traverse if there is already a similar vertex
		{
			hashVal = (hashVal + 1) % MAXSIZE; 
			i++;
		}
		
	if(strcmp(dict[hashVal].vertex, EMPTYSTRING) == 0)
		{
			strcpy(dict[hashVal].vertex,vertex);
			printf("\nVERTEX SUCCESSFULLY ADDED");
			return true;
		}

	
	return false;
}

int hash(STRING vertex)
{
	return vertex[0] % 26;
}

bool addEdge(Dictionary *dict, STRING vertex, STRING edge)
{
	int i = 0, hashValEdge = hash(edge);
	bool shouldAdd = false, vertexPresent = false;
	
	
	while(i < 26)
		{
			if(strcmp(dict[hashValEdge].vertex, edge) == 0)
				{
					shouldAdd = true;
					break;
				}
			hashValEdge = (hashValEdge + 1) % MAXSIZE;
			i++;
		}
		
	i = 0;
	int hashValVertex = hash(vertex);
	while(i < 26)
		{
			if(strcmp(dict[hashValVertex].vertex, vertex) == 0)
				{
					vertexPresent = true;
					break;
				}
			hashValVertex = (hashValVertex + 1) % MAXSIZE;
			i++;
		}
	
	
	if(shouldAdd && vertexPresent && (dict[hashValVertex].arrayList.count < 5 && dict[hashValEdge].arrayList.count < 5))
		{
			int count = dict[hashValVertex].arrayList.count;
			strcpy(dict[hashValVertex].arrayList.edge[count],edge);	
			dict[hashValVertex].arrayList.count++;
			
			strcpy(dict[hashValEdge].arrayList.edge[dict[hashValEdge].arrayList.count], dict[hashValVertex].vertex);
			dict[hashValEdge].arrayList.count++;
			return true;
		}
	else if(dict[hashValVertex].arrayList.count >= 5 || dict[hashValEdge].arrayList.count >= 5)
		{
			printf("THE EDGES COUNT REACHED THE MAXIMUM LIMIT");
		}
	
	return false;
}

void visualizeDictionary(Dictionary *dict)
{
	printf("%5s | %20s\n", "INDEX", "VERTEX");
	printf("---------------------------\n");
	
	int i;
	
	for(i = 0; i < 26; i++)
		{
			printf("%5d | ", i);
				if(strcmp(dict[i].vertex, EMPTYSTRING) == 0)
					{
						printf("%20s", "EMPTY");
					}
				else
					{
						printf("%20s", dict[i].vertex);
					}
			printf("\n");
		}
}

void displayDictionary(Dictionary *dict)
{
	printf("%5s | %20s |%20s\n", "INDEX", "VERTEX", "EDGES");
	printf("---------------------------\n");
	
	int i;
	
	for(i = 0; i < 26; i++)
		{
			if(strcmp(dict[i].vertex, EMPTYSTRING) != 0)
				{
					printf("%5d | ", i);
					printf("%20s", dict[i].vertex);
						
						int x = dict[i].arrayList.count, y;
						for(y = 0; y < x - 1; y++)
							{
								printf("%15s, ",dict[i].arrayList.edge[y]);
							}
						printf("%15s ",dict[i].arrayList.edge[y]);		
					printf("\n");		
				}		
					
		}
}

bool deleteEdge(Dictionary *dict, STRING vertex, STRING edge) //delete the edge on the particular vertex and on the Vertex[edge] delete the connection also
{
	int i = 0, hashValEdge = hash(edge);
	bool shouldDelete = false, vertexPresent = false;
	
	
	while(i < 26)
		{
			if(strcmp(dict[hashValEdge].vertex, edge) == 0) //check if the edge is part of the vertex
				{
					shouldDelete = true;
					break;
				}
			hashValEdge = (hashValEdge + 1) % MAXSIZE;
			i++;
		}  
		
		
	i = 0;
	int hashValVertex = hash(vertex);
	while(i < 26)
		{
			if(strcmp(dict[hashValVertex].vertex, vertex) == 0)//check if the vertex is present in the dictionary
				{
					vertexPresent = true;
					break;
				}
			hashValVertex = (hashValVertex + 1) % MAXSIZE;
			i++;
		}
	
	
	if(shouldDelete && vertexPresent) //if both are true
		{
			
			//delete first the edge on the vertes    
			int count = dict[hashValVertex].arrayList.count;
			strcpy(dict[hashValVertex].arrayList.edge[count],edge);	
			dict[hashValVertex].arrayList.count++;
			
			strcpy(dict[hashValEdge].arrayList.edge[dict[hashValEdge].arrayList.count], dict[hashValVertex].vertex);
			dict[hashValEdge].arrayList.count++;
			return true;
		}
	else if(dict[hashValVertex].arrayList.count >= 5 || dict[hashValEdge].arrayList.count >= 5)
		{  
			printf("THE EDGES COUNT REACHED THE MAXIMUM LIMIT");
		}
	
	return false;
}