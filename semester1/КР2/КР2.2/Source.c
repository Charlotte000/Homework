#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int** readFile(char* fileName, int* size, int* edgeSize)
{
	FILE* file = fopen(fileName, "r");
	fscanf(file, "%d", size);

	int** matrix = calloc(*size, sizeof(int*));
	for (int y = 0; y < *size; y++)
	{
		matrix[y] = calloc(*size, sizeof(int));
		for (int x = 0; x < *size; x++)
		{
			int value = 0;
			fscanf(file, "%d", &value);
			matrix[y][x] = value;
			if (value == 1)
			{
				(*edgeSize)++;
			}
		}
	}
	fclose(file);
	return matrix;
}

int** convertGraph(int** graph, int size, int edgeSize)
{

	int** matrix = calloc(size, sizeof(int*));
	for (int y = 0; y < size; y++)
	{
		matrix[y] = calloc(edgeSize, sizeof(int));
	}

	int i = 0;
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (graph[y][x] == 1)
			{
				matrix[x][i] = 1;
				matrix[y][i] = 1;
				i++;
			}
		}
	}
	return matrix;
}

void saveGraph(char* fileName, int** graph, int width, int height)
{
	FILE* file = fopen(fileName, "w");

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			fprintf(file, "%d ", graph[y][x]);
		}
		fprintf(file, "\n");
	}
	fclose(file);
}

void deleteMatrix(int** matrix, int height)
{
	for (int y = 0; y < height; y++)
	{
		free(matrix[y]);
	}
	free(matrix);
}

bool test(void)
{
	bool isPassed = true;

	int** matrix = calloc(3, sizeof(int*));
	for (int y = 0; y < 3; y++)
	{
		matrix[y] = calloc(3, sizeof(int));
	}
	matrix[0][2] = 1;

	int** graph = convertGraph(matrix, 3, 1);
	isPassed = isPassed && graph[0][0] == 1 && graph[1][0] == 0 && graph[2][0] == 1;

	deleteMatrix(matrix, 3);
	deleteMatrix(graph, 3);
	return isPassed;
}


int main()
{
	if (!test())
	{
		printf("Test Failed!\n");
		return;
	}

	int size = 0;
	int edgeSize = 0;
	int** matrix = readFile("in.txt", &size, &edgeSize);

	int** graph = convertGraph(matrix, size, edgeSize);

	saveGraph("out.txt", graph, edgeSize, size);

	deleteMatrix(matrix, size);
	deleteMatrix(graph, size);
}