/*
 * Binary-Tree.
 *
 * (C) 2019.05.12 <buddy.zhang@aliyun.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <stdio.h>
#include <stdlib.h>

/* binary-tree node */
struct binary_node {
	int idx;
	struct binary_node *left;
	struct binary_node *right;
};

/* Perfect Binary Tree  
 *                               (200)
 *                                 |
 *                 o---------------+---------------o
 *                 |                               |
 *               (143)                           (876)  
 *                 |                               |
 *          o------+-----o                  o------+-----o
 *          |            |                  |            |
 *        (754)        (386)              (486)        (740)
 *          |            |                  |            |
 *      o---+---o    o---+---o          o---+---o    o---+---o
 *      |       |    |       |          |       |    |       |
 *     (6)     (3)  (7)     (9)        (8)     (2)  (1)     (5)
 */
static int Perfect_BinaryTree_data[] = { 
                                   -1, -1, 6, -1, -1, 3, 754, -1, -1, 7,
                                   -1, -1, 9, 386, 143, -1, -1, 8, -1, -1,
                                   2, 486, -1, -1, 1, -1, -1, 5, 740, 876,
                                   200 };
/* Must indicate the number of counter on Postorder Create binary-tree */
static int counter = 31;
static int *BinaryTree_data = Perfect_BinaryTree_data;

/* Preorder Create Binary-tree 
 *
 *   Don't direct Postorder create binary-tree, but we can find the last
 *   node is root, and previous node is right-child for root, and pre-previous
 *   node is left-child for root..... So, we can create binary tree like this.
 */
static struct binary_node *Postorder_Create_BinaryTree(struct binary_node *node)
{
	int ch = BinaryTree_data[--counter];

	/* input from terminal */
	if (ch == -1) {
		return NULL;
	} else {
		node= 
		   (struct binary_node *)malloc(sizeof(struct binary_node));	
		node->idx = ch;

		/* Create right child */
		node->right  = Postorder_Create_BinaryTree(node->right);
		/* Create left child */
		node->left = Postorder_Create_BinaryTree(node->left);
		return node;
	}
}

/* Pre-Traverse Binary-Tree */
static void Preorder_Traverse_BinaryTree(struct binary_node *node)
{
	if (node == NULL) {
		return;
	} else {
		printf("%d ", node->idx);
		/* Traverse left child */
		Preorder_Traverse_BinaryTree(node->left);
		/* Traverse right child */
		Preorder_Traverse_BinaryTree(node->right);
	}
}

/* Midd-Traverse Binary-Tree */
static void Middorder_Traverse_BinaryTree(struct binary_node *node)
{
	if (node == NULL) {
		return;
	} else {
		Middorder_Traverse_BinaryTree(node->left);
		printf("%d ", node->idx);
		Middorder_Traverse_BinaryTree(node->right);
	}
}

/* Post-Traverse Binary-Tree */
static void Postorder_Traverse_BinaryTree(struct binary_node *node)
{
	if (node == NULL) {
		return;
	} else {
		Postorder_Traverse_BinaryTree(node->left);
		Postorder_Traverse_BinaryTree(node->right);
		printf("%d ", node->idx);
	}
}

/* The deep for Binary-Tree */
static int BinaryTree_Deep(struct binary_node *node)
{
	int deep = 0;

	if (node != NULL) {
		int leftdeep  = BinaryTree_Deep(node->left);
		int rightdeep = BinaryTree_Deep(node->right);

		deep = leftdeep >= rightdeep ? leftdeep + 1: leftdeep + 1;
	}
	return deep;
}

/* Leaf counter */
static int BinaryTree_LeafCount(struct binary_node *node)
{
	static int count;

	if (node != NULL) {
		if (node->left == NULL && node->right == NULL)
			count++;

		BinaryTree_LeafCount(node->left);
		BinaryTree_LeafCount(node->right);
	}
	return count;
}

/* Post-Free BinaryTree */
static void Postorder_Free_BinaryTree(struct binary_node *node)
{
	if (node == NULL) {
		return;
	} else {
		Postorder_Free_BinaryTree(node->left);
		Postorder_Free_BinaryTree(node->right);
		free(node);
		node = NULL;
	}
}

int main()
{
	/* Define binary-tree root */
	struct binary_node *BiscuitOS_root;
	
	printf("Postorder Create BinaryTree\n");
	BiscuitOS_root = Postorder_Create_BinaryTree(BiscuitOS_root);

	/* Preoder traverse binary-tree */
	printf("Preorder Traverse Binary-Tree:\n");
	Preorder_Traverse_BinaryTree(BiscuitOS_root);
	printf("\n");

	/* Middorder traverse binary-tree */
	printf("Middorder Traverse Binary-Tree:\n");
	Middorder_Traverse_BinaryTree(BiscuitOS_root);
	printf("\n");

	/* Postorder traverse binary-tree */
	printf("Postorder Traverse Binary-Tree:\n");
	Postorder_Traverse_BinaryTree(BiscuitOS_root);
	printf("\n");

	/* The deep for Binary-Tree */
	printf("The Binary-Tree Deep: %d\n", 
				BinaryTree_Deep(BiscuitOS_root));

	/* The leaf number for Binary-Tree */
	printf("The Binary-Tree leaf: %d\n", 
				BinaryTree_LeafCount(BiscuitOS_root));

	/* Postorder free binary-tree */
	Postorder_Free_BinaryTree(BiscuitOS_root);

	return 0;
}
