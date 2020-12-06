#pragma once

typedef struct Graph Graph;

Graph* createGraph(int n);

void setEdge(Graph* graph, int node1, int node2, int length);

int getEdge(Graph* graph, int node1, int node2);

void setNode(Graph* graph, int node, int value);

int getNode(Graph* graph, int node);

void printEdges(Graph* graph);

void printNodes(Graph* graph);

void deleteGraph(Graph** graph);