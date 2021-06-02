#include "bst.h"

using namespace std;

int rangeSum(Node *root, int L, int R)
{
	if (root == nullptr)
	{
		return 0;
	}
	if (root->key >= L && root->key <= R)
	{
		return root->key + rangeSum(root->left, L, R) + rangeSum(root->right, L, R);
	}
	else
	{
		return rangeSum(root->left, L, R) + rangeSum(root->right, L, R);
	}
}
