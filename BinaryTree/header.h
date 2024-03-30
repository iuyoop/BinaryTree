#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define ROOT 11

typedef struct BinaryTree{
	int value;
	struct BinaryTree* right;
	struct BinaryTree* left;
	struct BinaryTree* parents;
}TREE;

TREE* inputElements(void);

TREE* allocationMemoryForTree(int value);

void createTree(TREE* tree, int value);

TREE* hideElements(TREE* tree, int value, int flag); 

//~~~~~~~~~~~~~~~~~~~~~~ Задание Андрея ~~~~~~~~~~~~~~~~~~~~~~~~

TREE* delElement(TREE* tree, int value);

TREE* searchMinElement(TREE* tree);