#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool** readFile(char* fileName, int* size)
{
	FILE* file = fopen(fileName, "r");
	fscanf(file, "%d", size);
	bool** matrix = calloc(*size, sizeof(bool*));
	if (matrix == NULL)
	{
		fclose(file);
		return NULL;
	}
	for (int y = 0; y < *size; y++)
	{
		matrix[y] = calloc(*size, sizeof(bool));

		for (int x = 0; x < *size; x++)
		{
			int value = 0;
			fscanf(file, "%d", &value);
			matrix[y][x] = (bool)value;
		}
	}
	fclose(file);
	return matrix;
}

void writeFile(bool** matrix, int size)
{
	FILE* file = fopen("data.dot", "w+");
	fprintf(file, "digraph G { \nrankdir=LR;\n");
	for (int i = 0; i < size; i++)
	{
		fprintf(file, "%d [shape=\"circle\"label=\"%d\"];\n", i, i + 1);
	}

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (matrix[y][x])
			{
				fprintf(file, "%d -> %d;\n", y, x);
			}
		}
	}
	fprintf(file, "}");
	fclose(file);
}

int main()
{
	int size = 0;
	bool** matrix = readFile("data.txt", &size);
	writeFile(matrix, size);
}