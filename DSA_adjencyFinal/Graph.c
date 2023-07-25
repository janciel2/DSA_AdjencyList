#include "Graph.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

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

    while (i < 26)
    {
        if (strcmp(dict[hashValEdge].vertex, edge) == 0)
        {
            shouldAdd = true;
            break;
        }
        hashValEdge = (hashValEdge + 1) % MAXSIZE;
        i++;
    }

    i = 0;
    int hashValVertex = hash(vertex);
    while (i < 26)
    {
        if (strcmp(dict[hashValVertex].vertex, vertex) == 0)
        {
            vertexPresent = true;
            break;
        }
        hashValVertex = (hashValVertex + 1) % MAXSIZE;
        i++;
    }

    if (shouldAdd && vertexPresent && (dict[hashValVertex].arrayList.count < 5 && dict[hashValEdge].arrayList.count < 5))
    {
        int count = dict[hashValVertex].arrayList.count;
        for (i = 0; i < MAX; i++)
        {
            if (strcmp(dict[hashValVertex].arrayList.edge[i], edge) == 0 || strcmp(dict[hashValVertex].arrayList.edge[i], "DELETED") == 0)
            {
                // Edge is already added or marked as "DELETED," so we won't add it again.
                return false;
            }
            if (strcmp(dict[hashValVertex].arrayList.edge[i], EMPTYSTRING) == 0)
            {
                strcpy(dict[hashValVertex].arrayList.edge[i], edge);
                dict[hashValVertex].arrayList.count++;
                break;
            }
        }

        int v;
        for (v = 0; v < MAX; v++)
        {
            if (strcmp(dict[hashValEdge].arrayList.edge[v], vertex) == 0 || strcmp(dict[hashValEdge].arrayList.edge[v], "DELETED") == 0)
            {
                // Edge is already added or marked as "DELETED," so we won't add it again.
                return false;
            }
            if (strcmp(dict[hashValEdge].arrayList.edge[v], EMPTYSTRING) == 0)
            {
                strcpy(dict[hashValEdge].arrayList.edge[v], vertex);
                dict[hashValEdge].arrayList.count++;
                return true;
            }
        }
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
	printf("\n\n%5s | %20s |%20s\n", "INDEX", "VERTEX", "EDGES");
	printf("---------------------------\n");
	
	int i;
	
	for(i = 0; i < 26; i++)
		{
			if(strcmp(dict[i].vertex, EMPTYSTRING) != 0 && strcmp(dict[i].vertex, "DELETED") != 0)
				{
					printf("%5d | ", i);
					printf("%20s", dict[i].vertex);
						
						int y = 0;
						while(y < MAX)
							{
								if(strcmp(dict[i].arrayList.edge[y], EMPTYSTRING)!= 0)
									{	
										printf("%15s, ",dict[i].arrayList.edge[y]);
									}
								y++;
							}
						
						if(strcmp(dict[i].arrayList.edge[y], EMPTYSTRING)!= 0)
							{
								printf("%15s ",dict[i].arrayList.edge[y]);			
							}
					printf("\n");		
				}		
					
		}
}

bool deleteEdge(Dictionary *dict, STRING vertex, STRING edge)
{
    int i, hashValEdge = hash(edge);
    bool shouldDelete = false, vertexPresent = false;

    // Check if the edge is part of the vertex
    for (i = 0; i < 26; i++)
    {
        if (strcmp(dict[hashValEdge].vertex, edge) == 0)
        {
            shouldDelete = true;
            break;
        }
        hashValEdge = (hashValEdge + 1) % MAXSIZE;
    }

    // Check if the vertex is present in the dictionary
    int hashValVertex = hash(vertex);
    for (i = 0; i < 26; i++)
    {
        if (strcmp(dict[hashValVertex].vertex, vertex) == 0)
        {
            vertexPresent = true;
            break;
        }
        hashValVertex = (hashValVertex + 1) % MAXSIZE;
    }

    if (shouldDelete && vertexPresent) // If both are true
    {
        // Delete the edge on the vertex
        for (i = 0; i < MAX; i++)
        {
            if (strcmp(dict[hashValVertex].arrayList.edge[i], edge) == 0)
            {
                // Found the edge, mark it as "DELETED"
                strcpy(dict[hashValVertex].arrayList.edge[i], "DELETED");
                dict[hashValVertex].arrayList.count--;
                break;
            }
        }

        // Delete the connection on the Vertex[edge]
        for (i = 0; i < MAX; i++)
        {
            if (strcmp(dict[hashValEdge].arrayList.edge[i], vertex) == 0)
            {
                // Found the connection, mark it as "DELETED"
                strcpy(dict[hashValEdge].arrayList.edge[i], "DELETED");
                dict[hashValEdge].arrayList.count--;
                break;
            }
        }
        return true;
    }

    return false;
}

bool deleteVertex(Dictionary *dict, STRING vertex)
{
   	int hashVal = hash(vertex), i = 0;	
   	bool shouldDelete = false;
	STRING edgeList[MAX];
	int edgeCount = 0;	
	if(strcmp(dict[hashVal].vertex, vertex) == 0)
		{
			shouldDelete = true;
		}
		
	if(shouldDelete)
		{
			int i,v = 0;
			
			for(i = 0; i < MAX; i++)
				{
					if(strcmp(dict[hashVal].arrayList.edge[i], EMPTYSTRING) != 0)
						{
							strcpy(edgeList[v], dict[hashVal].arrayList.edge[i]);
							printf("\n\n\n\n%s", edgeList[v]);
							v++;
							edgeCount++;
						}
				}
			
		int y = 0;
		while(y < edgeCount)
		{
			int hashValEdge = hash(edgeList[y]);
			
			 for (i = 0; i < MAX; i++) //this part deletes everything inside the edges array;
        		{
           			 if (strcmp(dict[hashValEdge].arrayList.edge[i], vertex) == 0)
            		{
                		strcpy(dict[hashValEdge].arrayList.edge[i], "DELETED");
                		dict[hashValEdge].arrayList.count--;
                		break;
            		}
        		}
			y++;
		}
		
		strcpy(dict[hashVal].vertex, "DELETED");
		
		return true;
		}
		
		
		
		
	
	return false;
}
