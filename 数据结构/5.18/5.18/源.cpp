#include"BST.h"
#include<iostream>
using namespace std;

template <typename Key, typename E>
void print(BSTNode<Key, E>* root) {
	if (root == NULL) return;
	print(root->left());
	cout << root->key() << "   ";
	print(root->right());
}
int main()
{
	BST<int, int>tree;
	tree.insert(1,1);
	tree.insert(20,20);
	tree.insert(21,21);
	tree.insert(5,5);
	tree.insert(56,56);
	tree.insert(88,88);
	tree.insert(30,29);
	print<int, int>(tree.getroot());
}