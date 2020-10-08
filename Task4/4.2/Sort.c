void swapItems(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void quickSort(int* massive, int first, int last)
{
	int cursor = last;
	int aim = first;
	while (cursor != aim)
	{
		if (cursor > aim)
		{
			if (massive[cursor] < massive[aim])
			{
				swapItems(&massive[cursor], &massive[aim]);
				swapItems(&cursor, &aim);
			}
			else
			{
				aim++;
			}
		}
		else if (cursor < aim)
		{
			if (massive[cursor] > massive[aim])
			{
				swapItems(&massive[cursor], &massive[aim]);
				swapItems(&cursor, &aim);
			}
			else
			{
				aim--;
			}
		}
	}
	if (cursor - 1 > first)
	{
		quickSort(massive, first, cursor - 1);
	}
	if (cursor + 1 < last)
	{
		quickSort(massive, cursor + 1, last);
	}
}