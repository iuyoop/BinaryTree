#include "header.h"

/*							     _____ [11] _____
								|                |
							___ [7] ___      ___ [16] ___
						   |           |    |           |
					  ___ [2]         [9]  [15]     ___ [20] ___
					 |						       |		    |
				  [-10]						     [18] ___	   [36]
														 |
														[19]
*/

TREE* inputElements(void)
{
	TREE* tree;
	tree = allocationMemoryForTree(ROOT);
	if (tree == NULL) {
		return -1;
	}
	createTree(tree, 16);
	createTree(tree, 7);

	createTree(tree, 20);
	createTree(tree, 7); // Ошибочное добавление 
	createTree(tree, 15);

	createTree(tree, 9);
	createTree(tree, 2);

	createTree(tree, 36);
	createTree(tree, 18);
	createTree(tree, 19);
	createTree(tree, -10);

	return tree;
}

TREE* allocationMemoryForTree(int value)
{ 
	TREE* memory;
	memory = malloc(sizeof(TREE));
	if (memory == NULL){
		return -1;
	}
	memory->value = value;
	memory->parents = NULL;
	memory->right = NULL;
	memory->left = NULL;

	return memory;
}

void createTree(TREE* tree, int value)
{
	int hide = 0;
	hide = hideElements(tree, value, 0);
	if (hide == 1) {
		printf(" (x) Element %d is in this tree (x)\n", value);
		return -1;
	}
	if (tree == NULL) {
		return -1;
	}

	TREE* treeNode;
	treeNode = allocationMemoryForTree(value);
	treeNode->parents = tree;
	if (treeNode->value > tree->value) {
		if (tree->right == NULL) {
			printf(" Element %d >> this tree for %d [in right]\n", value, tree->value);
			tree->right = treeNode;
		}
		else {
			free(treeNode);
			return createTree(tree->right, value);
		}
	}
	if (treeNode->value < tree->value) {
		if (tree->left == NULL) {
			printf(" Element %d >> this tree for %d [in left]\n", value, tree->value);
			tree->left = treeNode;
		}
		else {
			free(treeNode);
			return createTree(tree->left, value);
		}
	}
}

TREE* hideElements(TREE* tree, int value, int flag)
{
	if (tree == NULL) {
		return -1;
	}
	if (value > tree->value) {
		if (tree->right != NULL) {
			if (value == tree->right->value) {
				if (flag == 0) {
					return 1;
				}
				else {
					return tree->right;
				}
			}
			else {
				return hideElements(tree->right, value, flag);
			}
		}
		else {
			return 0;
		}
	}
	else if (value < tree->value) {
		if (tree->left != NULL) {
			if (value == tree->left->value) {
				if (flag == 0) {
					return 1;
				}
				else {
					return tree->left;
				}
			}
			else {
				return hideElements(tree->left, value, flag);
			}
		}
		else {
			return 0;
		}
	}
	else {
		if (flag == 0) {
			return 1;
		}
		else {
			return tree;
		}
	}
}

//~~~~~~~~~~~~~~~~~~~~~~ Задание Андрея ~~~~~~~~~~~~~~~~~~~~~~~~

TREE* delElement(TREE* tree, int value)
{
	int hide = 0;
	hide = hideElements(tree, value, 0);
	if (hide == 0){
		printf(" (x) Element [%d] is no such in this tree\n", value);
		return tree;
	}

	if (hide == 1) {
		TREE* delEl;
		delEl = malloc(sizeof(TREE));
		delEl = hideElements(tree, value, 1);

		if (delEl->right == NULL && delEl->left == NULL) {
			if (delEl->value > delEl->parents->value) {
				delEl->parents->right = NULL;
			}
			if (delEl->value < delEl->parents->value) {
				delEl->parents->left = NULL;
			}

			free(delEl);
		}
		
		else if (delEl->right != NULL && delEl->left == NULL) {
			TREE* parent = delEl->parents;
			delEl = delEl->right;

			if (parent->left == delEl) {
				parent->right = delEl;
				parent->right->parents = parent;
			}
			else {
				parent->left = delEl;
				parent->left->parents = parent;
			}

			free(delEl->left);
		}
		
		else if (delEl->right == NULL && delEl->left != NULL) {
			TREE* parent = delEl->parents;
			delEl = delEl->left;

			if (parent->left == delEl) {
				parent->right = delEl;
				parent->right->parents = parent;
			}
			else {
				parent->left = delEl;
				parent->left->parents = parent;
			}

			free(delEl->left);
		}

		else if (delEl->right != NULL && delEl->left != NULL) {
			TREE* newNode = searchMinElement(delEl->left);
			TREE* parent = delEl->parents;
			if (parent != NULL) {
				if (delEl->value > parent->value) {
					newNode->parents->right = NULL;
					newNode->parents = parent;

					parent->right = newNode;
					parent->right->right = delEl->right;
					if (delEl != parent->right->left) {
						parent->right->left = delEl->left;
					}
				}
				if (delEl->value < parent->value) {
					newNode->parents->left = NULL;
					newNode->parents = parent;

					parent->left = newNode;
					parent->left->right = delEl->right;
					if (delEl != parent->left->left) {
						parent->left->left = delEl->left;
					}
				}
			}
			if (parent == NULL) {
				TREE* NEWTREE = malloc(sizeof(TREE));
				NEWTREE = tree;
				if (delEl->value == tree->value){
					newNode->right = tree->right;
					if (delEl != tree->left) {
						newNode->left = delEl->left;
					}
					newNode->left->parents = newNode;
					newNode->right->parents = newNode;

					newNode->parents->right = NULL;
					newNode->parents = NULL;
					NEWTREE = newNode;

					return NEWTREE;
				}
			}
		}
	}

}

TREE* searchMinElement(TREE* tree)
{
	if (tree->right == NULL) {
		return tree;
	}
	else {
		return searchMinElement(tree->right);
	}
}