/**
 *  Defines structs for trees with up to 25 branches. You should not need to modify this file,
 * but you are welcome to if you need.
 */

//////////////////////////////////////////////////

// definitions

#define BRANCHMAX 250

//////////////////////////////////////////////////

/**
 * Defines the contents field including an array of the children.
 */ 
union contents
{
	struct node **branches;
	int value;
	char *id;
};

/**
 * Defines the node data structure with tag and content fields, as well as the number of branches/children
 */
typedef struct node
{
	int tag;
	union contents content;
	int branchcounter;
	
} node;

//////////////////////////////////////////////////

/**
 * Tree operation function declarations
 *  (defintions are in tree.c)
 */
extern struct node *newInternalNode(int tag);

extern struct node *newIntLeaf(int value);

extern struct node *newIdLeaf(char *id);

extern void printTree(struct node *basenode);

extern void addBranch(struct node *parentnode, struct node *childnode);

extern  void printNode(struct node * pnode, int d);

//////////////////////////////////////////////////

