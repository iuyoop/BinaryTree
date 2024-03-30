#include "header.h"

#define HideEl 52
#define DelEl 11

int main()
{
	int HideElements = 0;
	printf(" | The root of binary tree is %d |\n\n", ROOT);

	TREE* BinaryTree;
	BinaryTree = inputElements();

	HideElements = hideElements(BinaryTree, HideEl, 0);
	if (HideElements == 1) {
		printf(" \n The element %d is in this tree\n", HideEl);
	} 
	else {
		printf(" \n (x) The element %d is not in this tree (x)\n", HideEl);
	}

	if (DelEl == ROOT) {
		BinaryTree = delElement(BinaryTree, DelEl);
	}
	else {
		delElement(BinaryTree, DelEl);
	}

	return 0;
}