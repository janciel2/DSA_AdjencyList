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


void push(StackList *stack, int *top, int val)
{
    (*top)++;
    stack[*top] = val;
}

int pop(StackList *stack, int *top)
{
    int val = stack[*top];
    (*top)--;
    return val;
}

void DFS(Dictionary *dict)
{
    // Create a stack to keep track of the vertices to be explored
    StackList stack[MAXSIZE];
    int top = -1; // Initialize the stack top to -1 (empty stack)

    // Initialize an array to keep track of visited vertices
    bool visited[MAXSIZE];
    for (int i = 0; i < MAXSIZE; i++)
    {
        visited[i] = false;
    }

    // Find the starting vertex (startVal) to begin DFS
    STRING startVal;
    strcpy(startVal, EMPTYSTRING);

    for (int i = 0; i < MAXSIZE - 1; i++)
    {
        if (strcmp(dict[i].vertex, EMPTYSTRING) != 0)
        {
            if (strcmp(dict[i + 1].vertex, EMPTYSTRING) != 0)
            {
                int smallVal = compareValues(dict[i].vertex, dict[i + 1].vertex);
                if (smallVal == 0)
                {
                    if (strcmp(startVal, EMPTYSTRING) != 0)
                    {
                        int smallVal = compareValues(dict[i].vertex, startVal);
                        if (smallVal == 0)
                        {
                            strcpy(startVal, dict[i].vertex);
                        }
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        strcpy(startVal, dict[i].vertex);
                    }
                }
                else
                {
                    if (strcmp(startVal, EMPTYSTRING) != 0)
                    {
                        int smallVal = compareValues(dict[i + 1].vertex, startVal);
                        if (smallVal == 0)
                        {
                            strcpy(startVal, dict[i + 1].vertex);
                        }
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        strcpy(startVal, dict[i + 1].vertex);
                    }
                }
            }
            else
            {
                strcpy(startVal, dict[i].vertex);
            }
        }
    }

    // Find the index of the starting vertex
    int startValIndex = -1;
    for (int i = 0; i < MAXSIZE; i++)
    {
        if (strcmp(dict[i].vertex, startVal) == 0)
        {
            startValIndex = i;
            break;
        }
    }

    // If the starting vertex is not found, return (error)
    if (startValIndex == -1)
    {
        printf("Starting vertex not found: %s\n", startVal);
        return;
    }

    // Push the index of the starting vertex onto the stack
    push(stack, &top, startValIndex);

    // Mark the starting vertex as visited
    visited[startValIndex] = true;

    printf("DFS traversal starting from vertex %s: ", startVal);

    // Start DFS traversal
    while (top >= 0)
    {
        // Pop a vertex from the stack
        int currentVertexIndex = pop(stack, &top);

        // Process the current vertex (e.g., print its value)
        printf("%s ", dict[currentVertexIndex].vertex);

        // Explore all adjacent vertices of the current vertex
        for (int i = 0; i < MAX; i++)
        {
            if (strcmp(dict[currentVertexIndex].arrayList.edge[i], EMPTYSTRING) != 0)
            {
                // Find the index of the adjacent vertex in the dictionary
                int adjacentVertexIndex = -1;
                for (int j = 0; j < MAXSIZE; j++)
                {
                    if (strcmp(dict[j].vertex, dict[currentVertexIndex].arrayList.edge[i]) == 0)
                    {
                        adjacentVertexIndex = j;
                        break;
                    }
                }

                // If the adjacent vertex is not visited, push it onto the stack
                if (!visited[adjacentVertexIndex])
                {
                    push(stack, &top, adjacentVertexIndex);
                    visited[adjacentVertexIndex] = true;
                }
            }
        }
    }

    printf("\n");
}

int compareValues(STRING x, STRING y)
{
    int i = 0;
    
    while (x[i] != '\0' && y[i] != '\0')
    {
        if (x[i] < y[i])
        {
            return -1;
        }
        else if (x[i] > y[i])
        {
            return 1;
        }
        i++;
    }
    
    if (x[i] == '\0' && y[i] != '\0')
    {
        return -1;
    }
    else if (x[i] != '\0' && y[i] == '\0')
    {
        return 1;
    }
    
    return 0; // Both strings are equal
}

void enqueue(int *queue, int *front, int *rear, int val)
{
    (*rear)++;
    queue[*rear] = val;
}

int dequeue(int *queue, int *front, int *rear)
{
    int val = queue[*front];
    (*front)++;
    return val;
}

void BFS(Dictionary *dict)
{
    // Create a queue to keep track of the vertices to be explored
    int queue[MAXSIZE];
    int front = 0; // Front of the queue (initially 0)
    int rear = -1; // Rear of the queue (initially -1)

    // Initialize an array to keep track of visited vertices
    bool visited[MAXSIZE];
    for (int i = 0; i < MAXSIZE; i++)
    {
        visited[i] = false;
    }

    // Find the starting vertex (startVal) to begin BFS
    STRING startVal;
    strcpy(startVal, EMPTYSTRING);

    for (int i = 0; i < MAXSIZE - 1; i++)
    {
        if (strcmp(dict[i].vertex, EMPTYSTRING) != 0)
        {
            if (strcmp(dict[i + 1].vertex, EMPTYSTRING) != 0)
            {
                int smallVal = compareValues(dict[i].vertex, dict[i + 1].vertex);
                if (smallVal == 0)
                {
                    if (strcmp(startVal, EMPTYSTRING) != 0)
                    {
                        int smallVal = compareValues(dict[i].vertex, startVal);
                        if (smallVal == 0)
                        {
                            strcpy(startVal, dict[i].vertex);
                        }
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        strcpy(startVal, dict[i].vertex);
                    }
                }
                else
                {
                    if (strcmp(startVal, EMPTYSTRING) != 0)
                    {
                        int smallVal = compareValues(dict[i + 1].vertex, startVal);
                        if (smallVal == 0)
                        {
                            strcpy(startVal, dict[i + 1].vertex);
                        }
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        strcpy(startVal, dict[i + 1].vertex);
                    }
                }
            }
            else
            {
                strcpy(startVal, dict[i].vertex);
            }
        }
    }

    // Find the index of the starting vertex
    int startValIndex = -1;
    for (int i = 0; i < MAXSIZE; i++)
    {
        if (strcmp(dict[i].vertex, startVal) == 0)
        {
            startValIndex = i;
            break;
        }
    }

    // If the starting vertex is not found, return (error)
    if (startValIndex == -1)
    {
        printf("Starting vertex not found: %s\n", startVal);
        return;
    }

    // Enqueue the index of the starting vertex into the queue
    enqueue(queue, &front, &rear, startValIndex);

    // Mark the starting vertex as visited
    visited[startValIndex] = true;

    printf("BFS traversal starting from vertex %s: ", startVal);

    // Start BFS traversal
    while (front <= rear)
    {
        // Dequeue a vertex from the queue
        int currentVertexIndex = dequeue(queue, &front, &rear);

        // Process the current vertex (e.g., print its value)
        printf("%s ", dict[currentVertexIndex].vertex);

        // Explore all adjacent vertices of the current vertex
        for (int i = 0; i < MAX; i++)
        {
            if (strcmp(dict[currentVertexIndex].arrayList.edge[i], EMPTYSTRING) != 0)
            {
                // Find the index of the adjacent vertex in the dictionary
                int adjacentVertexIndex = -1;
                for (int j = 0; j < MAXSIZE; j++)
                {
                    if (strcmp(dict[j].vertex, dict[currentVertexIndex].arrayList.edge[i]) == 0)
                    {
                        adjacentVertexIndex = j;
                        break;
                    }
                }

                // If the adjacent vertex is not visited, enqueue it into the queue
                if (!visited[adjacentVertexIndex])
                {
                    enqueue(queue, &front, &rear, adjacentVertexIndex);
                    visited[adjacentVertexIndex] = true;
                }
            }
        }
    }

    printf("\n");
}
