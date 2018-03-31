#include "List.h"
#include"Link.h"
#include<cassert>
#include<string>
#define defaultSize 100
template <typename E> class LList : public List<E> {
private:
	Link<E>* head;       
	Link<E>* tail;      
	Link<E>* curr;       
	int cnt;    	      

	void init() 
	{       
		curr = tail = head = new Link<E>;
		cnt = 0;
	}

	void removeall()
	{   
		while (head != NULL) {
			curr = head;
			head = head->next;
			delete curr;
		}
	}

public:
	LList(int size = defaultSize) { init(); }    
	~LList() { removeall(); }                   
	void print() const;                
	void clear() { removeall(); init(); }      

	void insert(const E& it) {
		curr->next = new Link<E>(it, curr->next);
		if (tail == curr) tail = curr->next; 
		cnt++;
	}

	void append(const E& it) 
	{ 
		tail = tail->next = new Link<E>(it, NULL);
		cnt++;
	}

	E remove() {
		assert(curr->next != NULL, "the linkedList is empty");
		E it = curr->next->element;      
		Link<E>* ltemp = curr->next;    
		if (tail == curr->next) tail = curr; 
		curr->next = curr->next->next;  
		delete ltemp;                    
		cnt--;			     
		return it;
	}

	void moveToStart() 
	{
		curr = head;
	}

	void moveToEnd()   
	{
		curr = tail;
	}

	void prev() {
		if (curr == head) return;      
		Link<E>* temp = head;
		while (temp->next != curr) temp = temp->next;
		curr = temp;
	}

	void next()
	{
		if (curr != tail) curr = curr->next;
	}

	int length() const  { return cnt; } 

	int currPos() const 
	{
		Link<E>* temp = head;
		int i;
		for (i = 0; curr != temp; i++)
			temp = temp->next;
		return i;
	}

	void moveToPos(int pos) {
		assert((pos >= 0) && (pos <= cnt), "Position out of range");
		curr = head;
		for (int i=0; i<pos; i++) curr = curr->next;
	}

    E& getValue()
	{ 
		assert(curr->next!= NULL, "there is no value in this place");
		return curr->next->element;
	}
	Link<E>* getPValue()
	{
		return curr->next;
	}
};
