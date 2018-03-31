#include"GTNode.h"
template <typename E> class GenTree{
public:
	void clear();
	GTNode<E>* root();
	void newroot(E&, GTNode<E>*, GTNode<E>*);
	void print();
};