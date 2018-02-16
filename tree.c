#include <stdio.h>
#include <stdlib.h>

#define MAX(x,y) ((x) > (y) ? (x) : (y))

struct Tree {
	int data;
	struct Tree *left;
	struct Tree *right;
};

struct Tree *newTree(void)
{
	struct Tree *root;
	root = malloc(sizeof *root);
	root->left = root->right = NULL;
	return root;
}
void destroyTree(struct Tree *root)
{
	if (!root) return;
	destroyTree(root->left);
	destroyTree(root->right);
	free(root);
}
struct Tree *treeAdd(struct Tree **root, int x)
{
	if (!*root) {
		*root = newTree();
		(*root)->data = x;
		return *root;
	}
	if (x <= (*root)->data) {
		return treeAdd(&(*root)->left, x);
	} else {
		return treeAdd(&(*root)->right, x);
	}
}
struct Tree *treeFind(struct Tree *root, int x)
{

}
void treeRemove(struct Tree **root, int x)
{

}
int maxElt(struct Tree *root)
{
	while (root->right) {
		root = root->right;
	}
	return root->data;
}
int minElt(struct Tree *root)
{
	while (root->left) {
		root = root->left;
	}
	return root->data;
}
int height_impl(struct Tree *root, int cur)
{
	if (!root || (!root->left && !root->right))
		return cur;
	int l = height_impl(root->left, cur + 1);
	int r = height_impl(root->right, cur + 1);
	return MAX(l,r);
}
int height(struct Tree *root)
{
	return height_impl(root, 0);
}
void show(struct Tree *root)
{
	if (!root) return;
	show(root->left);
	printf("%d\n", root->data);
	show(root->right);
}
int main()
{
	struct Tree *root;
	root = newTree();
	root->data = 42;

	treeAdd(&root, 20);
	treeAdd(&root, 11);
	treeAdd(&root, 29);
	treeAdd(&root, 26);
	treeAdd(&root, 65);
	treeAdd(&root, 50);

	show(root);

	int minel = minElt(root);
	int maxel = maxElt(root);
	int h = height(root);
	printf("min:%8d\n", minel);
	printf("max:%8d\n", maxel);
	printf("height:%5d\n", h);
	destroyTree(root);
}
