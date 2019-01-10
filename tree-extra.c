#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _List {
	struct _List *next;
	void *item;
	int size;
} List;

typedef struct _Queue {
	List *left;
	List *right;
	int size;
} Queue;


typedef struct _Tree {
	struct _Tree *left;
	struct _Tree *right;
	struct _Tree *extra;
	int value;
} Tree;


List *new_list()
{
	List *ret = malloc(sizeof *ret);
	ret->next = NULL;
	ret->item = NULL;
	ret->size = 0;
	return ret;
}


Queue *new_queue()
{
	Queue *ret = malloc(sizeof *ret);
	ret->left = NULL;
	ret->right = NULL;
	ret->size = 0;
	return ret;
}

void queue_push(Queue *q, void *item, int itemsize)
{
	List *node = new_list();
	node->item = malloc(itemsize);
	node->size = itemsize;
	memcpy(node->item, item, itemsize);
	if (!q->right && !q->left) {
		q->right = q->left = node;
		q->size = 1;
	} else {
		q->right->next = node;
		q->right = node;
		q->size++;
	}
}

void queue_pop(Queue *q, void *out)
{
	if (!q->size)
		return;
	List *node = q->left;
	q->left = node->next;
	memcpy(out, node->item, node->size);
	q->size--;

	if (q->left == NULL)
		q->right = NULL;

	free(node->item);
	free(node);
}


Tree *new_tree()
{
	Tree *ret = malloc(sizeof *ret);
	ret->left = ret->right = ret->extra = NULL;
	return ret;
}

Tree *tree_insert(Tree **root, int x)
{
	if (*root == NULL) {
		*root = new_tree();
		(*root)->value = x;
		return *root;
	}
	if (x < (*root)->value)
		return tree_insert(&(*root)->left, x);
	else if (x > (*root)->value)
		return tree_insert(&(*root)->right, x);
	return NULL;
}

void destroy_tree(Tree *root)
{
	if (!root)
		return;
	if (root->left)
		destroy_tree(root->left);
	if (root->right)
		destroy_tree(root->right);
	free(root);
}

void tree_show(Tree *root)
{
	if (root) {
		tree_show(root->left);
		printf("%d\n", root->value);
		tree_show(root->right);
	}
}

void tree_magick(Tree *root)
{
	if (!root)
		return;
	Queue *q = new_queue();
	queue_push(q, (void*)&root, sizeof &root);
	Tree *prev = NULL;
	Tree *head;
	while (q->size != 0) {
		queue_pop(q, &head);
		if (q->size == 0) {
			head->extra = NULL;
			prev = NULL;
		} else {
			prev = head;
		}
		if (prev)
			prev->extra = head;

		if (head->left)
			queue_push(q, (void*)&head->left, sizeof &head->left);
		if (head->right)
			queue_push(q, (void*)&head->right, sizeof &head->right);
	}
	free(q);
}

int main()
{
	Tree *root;

	root = NULL;

	int value = 0;
	while (scanf("%d", &value) == 1) {
		tree_insert(&root, value);
	}

	printf("OK\n");
	tree_show(root);

	tree_magick(root);
	destroy_tree(root);
}
