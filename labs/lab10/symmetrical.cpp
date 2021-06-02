#include "symmetrical.h"

bool checkChilds(Node *left, Node *right)
{

	if (!left && !right)
	{
		return true;
	}
	if (right && left && left->key == right->key)
	{
		return checkChilds(left->left, right->right) && checkChilds(left->right, right->left);
	}
	return false;
}

bool isSymmetrical(Node *root)
{
	if (!root)
	{
		return true;
	}
	return checkChilds(root->left, root->right);
}
