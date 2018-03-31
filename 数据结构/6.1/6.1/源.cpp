/*#include<iostream>
#include"GenTree.h"
using namespace std;
template <class Elem>
bool Compare(GTNode<Elem>* t1, GTNode<Elem>* t2)
{
	GTNode<Elem> *c1, *c2;
	if (((t1 == NULL) && (t2 != NULL)) || ((t2 == NULL) && (t1 != NULL)))
		return false;
	if ((t1 == NULL) && (t2 == NULL))
		return true;
	if (t1->val() != t2->val())
		return false;
	c1 = t1->leftmost_child();
	c2 = t2->leftmost_child();
	while (!((c1 == NULL) && (c2 == NULL)))
	{
		if (!Compare(c1, c2))
			return false;
		if (c1 != NULL) c1 = c1->right_sibling();
		if (c2 != NULL) c2 = c2->right_sibling();
	}
}
int main()
{
	

}*/