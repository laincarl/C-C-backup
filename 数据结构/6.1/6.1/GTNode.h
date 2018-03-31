//General tree node ADT
template<typename E> class GTNode{
public:
	E value();
	bool isLeaf();
	GTNode* parent();
	GTNode* leftmostChild();
	GTNode* rightSilling();
	void setValue(E&);
	void insertFirst(GTNode<E>*);
	void insertNext(GTNode<E>*);
	void removeFirst();
	void removeNext();
};