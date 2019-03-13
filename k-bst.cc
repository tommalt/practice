#include <stdio.h>

#include <deque>
#include <vector>

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

using namespace std;

struct Tree {
	int x;
	struct Tree *left;
	struct Tree *right;
};

Tree *tree_alloc()
{
	Tree *root = new Tree;
	root->x = 0;
	root->left = root->right = NULL;
	return root;
}

Tree *tree_insert(Tree **root, int x)
{
	if (!*root) {
		*root = tree_alloc();
		(*root)->x = x;
		return *root;
	}

	if (x > (*root)->x) {
		return tree_insert(&(*root)->right, x);
	} else {
		return tree_insert(&(*root)->left, x);
	}
}

int height(Tree *root)
{
	if (!root)
		return 0;
	int left = height(root->left);
	int right = height(root->right);
	return 1 + MAX(left, right);
}

int tree_size(Tree *root)
{
	if (!root) {
		return 0;
	}
	return 1 + tree_size(root->left) + tree_size(root->right);
}

void show(Tree *root)
{
	deque<Tree *> q;
	q.push_back(root);

	while (!q.empty()) {
		Tree *tmp = q.front(); q.pop_front();
		if (tmp->left)
			q.push_back(tmp->left);
		if (tmp->right)
			q.push_back(tmp->right);
		printf("Element, height: %d %d\n", tmp->x, height(tmp));
	}
}

void k_largest_bst_impl(Tree *root, int k, int *count, vector<int> *values)
{
	if (!root || *count == k)
		return;

	k_largest_bst_impl(root->right, k, count, values);
	if (++(*count) <= k) {
		values->push_back(root->x);
	}
	k_largest_bst_impl(root->left, k, count, values);
}

vector<int> k_largest_bst(Tree *root, int k)
{
	int count = 0;
	vector<int> values;
	k_largest_bst_impl(root, k, &count, &values);
	return values;
}

int main()
{
	Tree *root;

	root = NULL;

	tree_insert(&root, 3);

	tree_insert(&root, 2);
	tree_insert(&root, 1);

	tree_insert(&root, 6);
	tree_insert(&root, 4);
	tree_insert(&root, 5);

	printf("In order traversal\n");
	show(root);

	putchar('\n');
	int size = tree_size(root);
	for (int k = 0; k < size; k++) {
		auto nums = k_largest_bst(root, k);

		printf("Largest %d elements:", k);
		for (auto n : nums) {
			printf(" %d", n);
		}
		putchar('\n');
	}

	// auto k_largest = 

}
