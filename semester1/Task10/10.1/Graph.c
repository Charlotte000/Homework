#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
	int value;
} Node;

typedef struct Graph
{
	int size;
	int** adjacency;
	Node** nodes;
} Graph;

Graph* createGraph(int n)
{
	Graph* graph = malloc(sizeof(Graph));
	if (graph == NULL)
	{
		return NULL;
	}
	graph->size = n;
	graph->nodes = calloc(n, sizeof(Node));
	graph->adjacency = calloc(n, sizeof(int*));
	if (graph->adjacency == NULL)
	{
		free(graph);
		return NULL;
	}
	for (int i = 0; i < n; i++)
	{
		graph->adjacency[i] = calloc(n, sizeof(int));
		if (graph->adjacency[i] == NULL)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				free(graph->adjacency[j]);
			}
			free(graph->adjacency);
			free(graph);
			return NULL;
		}
		graph->nodes[i] = calloc(1, sizeof(Node));
		graph->nodes[i]->value = 0;
	}
	return graph;
}

void setEdge(Graph* graph, int node1, int node2, int length)
{
	graph->adjacency[node1][node2] = length;
	graph->adjacency[node2][node1] = length;
}

int getEdge(Graph* graph, int node1, int node2)
{
	return graph->adjacency[node1][node2];
}

void setNode(Graph* graph, int node, int value)
{
	graph->nodes[node]->value = value;
}

int getNode(Graph* graph, int node)
{
	return graph->nodes[node]->value;
}

void printEdges(Graph* graph)
{
	for (int y = 0; y < graph->size; y++)
	{
		for (int x = 0; x < graph->size; x++)
		{
			printf("%d ", graph->adjacency[y][x]);
		}
		printf("\n");
	}
}

void printNodes(Graph* graph)
{
	for (int i = 0; i < graph->size; i++)
	{
		printf("%d ", getNode(graph, i));
	}
	printf("\n");
}

void deleteGraph(Graph** graph)
{
	for (int i = 0; i < (*graph)->size; i++)
	{
		free((*graph)->adjacency[i]);
		free((*graph)->nodes[i]);
	}
	free((*graph)->adjacency);
	free((*graph)->nodes);
	*graph = NULL;
}