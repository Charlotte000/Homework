#include "IsFloat.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

enum STATES
{
	EMPTY,
	DIGIT,
	POINT,
	POINT_DIGIT,
	E,
	E_DIGIT,
	SIGN
};


bool isFloat(const char* string)
{
	const int length = strlen(string);
	int state = EMPTY;

	for (int cursor = 0; cursor < length; cursor++)
	{
		switch (state)
		{
		case EMPTY:
		{
			if (isdigit(string[cursor]))
			{
				state = DIGIT;
			}
			else
			{
				return false;
			}
			break;
		}
		case DIGIT:
		{
			if (isdigit(string[cursor]))
			{
				state = DIGIT;
			}
			else if (string[cursor] == '.' || string[cursor] == ',')
			{
				state = POINT;
			}
			else if (string[cursor] == 'E' || string[cursor] == 'e')
			{
				state = E;
			}
			else
			{
				return false;
			}
			break;
		}
		case POINT:
		{
			if (isdigit(string[cursor]))
			{
				state = POINT_DIGIT;
			}
			else
			{
				return false;
			}
			break;
		}
		case E:
		{
			if (isdigit(string[cursor]))
			{
				state = E_DIGIT;
			}
			else if (string[cursor] == '+' || string[cursor] == '-')
			{
				state = SIGN;
			}
			else
			{
				return false;
			}
			break;
		}
		case E_DIGIT:
		{
			if (isdigit(string[cursor]))
			{
				state = E_DIGIT;
			}
			else
			{
				return false;
			}
		}
		case POINT_DIGIT:
		{
			if (isdigit(string[cursor]))
			{
				state = POINT_DIGIT;
			}
			else
			{
				return false;
			}
		}
		case SIGN:
		{
			if (isdigit(string[cursor]))
			{
				state = E_DIGIT;
			}
			else
			{
				return false;
			}
			break;
		}
		}
	}
	return state == POINT_DIGIT || state == E_DIGIT;
}