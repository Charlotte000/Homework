#define _CRT_SECURE_NO_WARNINGS

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Graph* readData(char* fileName, int* city_len, int* capital_len)
{
	FILE* file = fopen(fileName, "r");
	int roads_len = 0;
	fscanf(file, "%d %d", city_len, &roads_len);

	Graph* graph = createGraph(*city_len);
	for (int i = 0; i < roads_len; i++)
	{
		int city1 = 0;
		int city2 = 0;
		int len = 0;
		fscanf(file, "%d %d %d", &city1, &city2, &len);
		setEdge(graph, city1, city2, len);
	}

	fscanf(file, "%d", capital_len);
	for (int i = 1; i <= *capital_len; i++)
	{

		int capital = 0;
		fscanf(file, "%d", &capital);
		setNode(graph, capital, i);
	}
	fclose(file);
	return graph;
}

void doTheDivision(Graph* graph, int city_len, int country_len)
{
	bool hasFreeCities = true;
	while (hasFreeCities)
	{
		hasFreeCities = false;
		for (int country = 1; country <= country_len; country++)
		{
			int node = 0;
			int minimal_len = -1;

			for (int city = 0; city < city_len; city++)
			{
				if (getNode(graph, city) == country)
				{
					for (int capture = 0; capture < city_len; capture++)
					{
						if (getNode(graph, capture) == 0)
						{
							int len = getEdge(graph, city, capture);
							if (len)
							{
								if (minimal_len == -1 || len < minimal_len)
								{
									minimal_len = len;
									node = capture;
								}
							}

						}
					}
				}
			}
			if (minimal_len != -1)
			{
				setNode(graph, node, country);
				hasFreeCities = true;
			}
		}
	}
}

void printCountries(Graph* graph, int city_len, int country_len)
{
	for (int country = 1; country <= country_len; country++)
	{
		printf("Country #%d: ", country);
		
		for (int city = 0; city < city_len; city++)
		{
			if (getNode(graph, city) == country)
			{
				printf("%d ", city);
			}
		}
		printf("\n");
	}
}

bool test(void)
{
	bool isPassed = true;

	int city_len = 2;
	int country_len = 2;
	Graph* graph = createGraph(city_len);
	setEdge(graph, 0, 1, 5);
	setNode(graph, 0, 1);
	setNode(graph, 1, 2);
	doTheDivision(graph, city_len, country_len);

	isPassed = isPassed && getNode(graph, 0) == 1 && getNode(graph, 1) == 2;
	deleteGraph(&graph);
	return isPassed;
}

int main()
{
	if (!test())
	{
		printf("Test Failed!\n");
		return;
	}
	int city_len = 0;
	int capital_len = 0;
	Graph* graph = readData("data.txt", &city_len, &capital_len);
	
	doTheDivision(graph, city_len, capital_len);
	printCountries(graph, city_len, capital_len);
	deleteGraph(&graph);
}