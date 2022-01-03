//////////////////////////////////////////////////

// FILE DESCRIPTION

// contains functions for creating, 
//	 manipulating and displaying trees

//////////////////////////////////////////////////

// includes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "tokens.h"



extern char *getSymb(int symb);

//////////////////////////////////////////////////

// --------Different node constructors----------

/**
 * Creates and returns a new node with tag
 */
struct node * newNode(int tag){
	struct node * returnable;
	returnable = malloc(sizeof(struct node));
	returnable->tag = tag;
	return returnable;
}

//----------------------------------------------//
/**
 * Creates a new node with tag, and initialises the children of that node
 */
struct node * newInternalNode(int tag)
{
	struct node * returnable = newNode(tag);
	returnable->content.branches = malloc(sizeof(struct node *)* BRANCHMAX) ;
	return returnable;
}

//----------------------------------------------//
/**
 * Creates a new leaf INT node
 */ 
struct node * newIntLeaf(int value){
	struct node * returnable = newNode(INT);
	returnable->content.value = value;
	return returnable;
}

//----------------------------------------------//
/**
 * Creates a new leaf ID node
 */ 
struct node * newIdLeaf(char * id){
	//printf("TRYING TO ADD NEW ID LEAF %s\n",id);
	struct node * returnable = newNode(ID);
	returnable->content.id = strdup(id);
	//printf("ABOUT TO RETURN ID LEAF \n");
	return returnable;
}


void rule(char * name, int depth){
	int x=0;
	for (x=0; x<depth; x++)
	{
		printf("-");
	}

	printf("%s\r\n", name);

}


//--------Tree manipulation operations-----------------------//
/**
 * Adds childnode as a child of parentnode
 */
void addBranch(struct node * parentnode, struct node * childnode){
	parentnode->content.branches[parentnode->branchcounter] = childnode;
	parentnode->branchcounter++;
}

/**
 * Recursively prints the subtree rooted at pnode, starting at depth d
 */
void printNode(struct node * pnode, int d){
	rule(getSymb(pnode->tag), d);

	if (pnode->tag == INT)
	{
		char valueasstring[100];
		sprintf(valueasstring, "%d", pnode->content.value);
		rule(valueasstring, d+1);
		return;
	}

	if (pnode->tag == ID)
	{
		rule(pnode->content.id, d+1);
		return;
	}

	int x;
	for (x=0; x<pnode->branchcounter; x++)
	{
		printNode(pnode->content.branches[x], d+1);
	}
}

/**
 *  Recursively print tree from depth 0
 */
void printTree(struct node * rootNode){
	printNode(rootNode, 0);
}



