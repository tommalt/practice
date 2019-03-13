
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <deque>
#include <set>

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

Tree *tree_alloc(int x)
{
	Tree *t = tree_alloc();
	t->x = x;
	return t;
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

vector<Tree *> leftmost_nodes(Tree *root)
{
	vector<Tree *> ret;
	set<Tree *> seen;
	vector<Tree *> stack;

	stack.push_back(root);
	while (!stack.empty()) {
		auto current = stack.back();
		seen.insert(current);

		int level = stack.size();

		if (level > ret.size()) {
			ret.push_back(current);
		}

		auto left_seen  = (current->left == NULL) || seen.find(current->left) != seen.end();
		auto right_seen = (current->right == NULL)|| seen.find(current->right) != seen.end();

		if (!left_seen) {
			stack.push_back(current->left);
		} else if (!right_seen) {
			stack.push_back(current->right);
		}
		if (left_seen && right_seen) {
			stack.pop_back();
		}
	}

	return ret;
}


int main()
{

	Tree *root;

	root = NULL;

	tree_insert(&root, 1);

	root->left = tree_alloc(2);
	root->right = tree_alloc(3);
	root->right->left = tree_alloc(4);
	root->right->right = tree_alloc(5);

	auto nodes = leftmost_nodes(root);
	for (auto n : nodes) { cout << n->x << '\n'; }

	return 0;
}

