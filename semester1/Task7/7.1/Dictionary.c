#include "Dictionary.h"
#include <stdlib.h>
#include <stdbool.h>

Dictionary* createDictionary(void)
{
	Dictionary* newDictionary = calloc(1, sizeof(Dictionary));
	if (newDictionary == NULL)
	{
		return NULL;
	}
	return newDictionary;
}

void addValue(Dictionary** head, int key, char* value)
{
	// Head is empty or has the same key
	if ((*head)->value == NULL || (*head)->key == key)
	{
		(*head)->key = key;
		(*head)->value = value;
		return;
	}

	// Turn left
	if (key < (*head)->key)
	{
		if ((*head)->left == NULL)
		{
			(*head)->left = createDictionary();
			(*head)->left->key = key;
			(*head)->left->value = value;
			return;
		}

		addValue(&((*head)->left), key, value);
		return;
	}

	// Turn right
	if ((*head)->right == NULL)
	{
		(*head)->right = createDictionary();
		(*head)->right->key = key;
		(*head)->right->value = value;
		return;
	}
	addValue(&((*head)->right), key, value);
}

char* getValue(Dictionary* head, int key)
{
	// Head is a searching node
	if (head->key == key)
	{
		return head->value;
	}

	// Turn left
	if (key < head->key)
	{
		if (head->left)
		{
			return getValue(head->left, key);
		}
		return NULL;
	}

	// Turn right
	if (head->right)
	{
		return getValue(head->right, key);
	}
	return NULL;
}

bool isExists(Dictionary* head, int key)
{
	// Head is a searching node
	if (head->key == key)
	{
		return true;
	}

	// Turn left
	if (key < head->key)
	{
		if (head->left)
		{
			return isExists(head->left, key);
		}
		return false;
	}

	// Turn right
	if (head->right)
	{
		return isExists(head->right, key);
	}
	return false;
}

void _deleteNode(Dictionary** node)
{
	// Has no child
	if ((*node)->left == NULL && (*node)->right == NULL)
	{
		free((*node)->value);
		free(*node);
		*node = NULL;
		return;
	}

	// Has only right child
	if ((*node)->left == NULL && (*node)->right != NULL)
	{
		Dictionary* oldHead = *node;
		*node = (*node)->right;
		free(oldHead->value);
		free(oldHead);
		return;
	}

	// Has left child
	if ((*node)->left != NULL)
	{
		Dictionary* cursor = (*node)->left;
		Dictionary* prevCursor = cursor;
		bool prevMove = false;
		while (true)
		{
			prevCursor = cursor;
			if (cursor->right != NULL)
			{
				cursor = cursor->right;
				prevMove = true;
			}
			else if (cursor->left != NULL)
			{
				cursor = cursor->left;
				prevMove = false;
			}

			if (cursor->right == NULL)
			{
				// Swap nodes
				if (prevMove)
				{
					prevCursor->right = cursor->left;
				}
				else
				{
					prevCursor->left = cursor->left;
				}

				if ((*node)->left != cursor)
				{
					cursor->left = (*node)->left;
					cursor->right = (*node)->right;
				}
				free((*node)->value);
				free(*node);
				*node = cursor;
				return;
			}
		}
	}
}

void deleteValue(Dictionary** head, int key)
{
	// Head is a searching node
	if ((*head)->key == key)
	{
		_deleteNode(head);
		return;
	}

	// Turn left
	if (key < (*head)->key)
	{
		if ((*head)->left)
		{
			deleteValue(&((*head)->left), key);
		}
		return;
	}

	// Turn right
	if ((*head)->right)
	{
		deleteValue(&((*head)->right), key);
	}
}
