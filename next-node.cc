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

void tree_destroy(Tree *root)
{
	if (!root)
		return;
	tree_destroy(root->left);
	tree_destroy(root->right);
	delete root;
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

int tree_max(Tree *root)
{
	if (!root->right)
		return root->x;
	return tree_max(root->right);
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

Tree *find_parent_greater(Tree *root, Tree *node)
{
	vector<Tree *> stack;
	for (; root;) {
		stack.push_back(root);
		if (node->x < root->x) {
			root = root->left;
		} else if (node->x > root->x) {
			root = root->right;
		} else { //equal
			break;
		}
	}

	for (; !stack.empty();) {
		Tree *back = stack.back(); stack.pop_back();
		if (back->x > node->x) {
			return back;
		}
	}
	return NULL;
}

Tree *next_node(Tree *root, Tree *node)
{
	if (node->right) {
		Tree *next = node->right;
		for (;;) {
			if (next->left)
				next = next->left;
			else
				return next;
		}
	} else {
		return find_parent_greater(root, node);
	}
}

void test(Tree *root)
{
	int max_element;
	deque<Tree *> q;

	max_element = tree_max(root);
	q.push_back(root);
	while (!q.empty()) {
		Tree *t = q.front(); q.pop_front();
		Tree *next = next_node(root, t);

		if (t->left)
			q.push_back(t->left);
		if (t->right)
			q.push_back(t->right);

		if (t->x != max_element) {
			if (next->x != t->x + 1) {
				printf("ERROR: next is not current + 1. (current,next): %d, %d\n", t->x, next->x);
			} else {
				printf("Current,Next: %d, %d\n", t->x, next->x);
			}
		} else {
			printf("Current,Next: %d, MAX\n", t->x);
		}
	}
}

void make_permutations(vector<int> *nums, int size, int n, vector<vector<int> > *out)
{
	if (size == 1) {
		out->emplace_back(*nums);
		return;
	}

	for (int i = 0; i < size; i++) {
		make_permutations(nums, size - 1, n, out);

		if (size % 2 == 1) {
			swap((*nums)[0], (*nums)[size - 1]);
		} else {
			swap((*nums)[i], (*nums)[size - 1]);
		}
	}
}

vector<vector<int> > permutations(int n)
{
	vector<int> nums;
	vector<vector<int> > perms;

	nums.reserve(n);
	for (int i = 1; i <= n; i++)
		nums.push_back(i);
	make_permutations(&nums, n, n, &perms);
	return perms;
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

	test(root);

	tree_destroy(root);
	root = NULL;

	for (int i = 1; i <= 10; i++) {
		auto perms = permutations(i);
		for (auto && p : perms) {
			tree_destroy(root);
			root = NULL;
			printf("Permutation:");
			for (auto x : p) {
				printf(" %d", x);
				tree_insert(&root, x);
			}
			putchar('\n');
			test(root);
		}
	}
}
