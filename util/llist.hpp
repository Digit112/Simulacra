#ifndef LLIST
#define LLIST

#include <stdlib.h>

template<class T>
class llist_node {
public:
	// References to adjacent nodes
	llist_node<T>* next;
	llist_node<T>* prev;
	
	// Value held by this node
	T value;
	
	llist_node();
	llist_node(T value);
	
	// If doinsert, modify prev.next and next.prev to point to this node.
	llist_node(T value, llist_node<T>* prev, llist_node<T>* next, bool doinsert=false);
};

template <class T>
class llist {
public:
	llist_node<T>* first;
	llist_node<T>* last;
	
	int size;
	
	llist();
	llist(T value);
	
	// Copies a list element by element. Individual elements are copied by their copy constructors.
	llist(const llist<T>& o);
	
	void append(const T&);
	void prepend(const T&);
	void insert(int i, const T&); // Note: Indices referring to the same location but which have different signs will insert at different locations.
	void remove(int i);
	
	// Exits the program with a message if the llist is corrupted.
	void validate();
	
	T&  operator[](int i);
	T operator[](int i) const;
	
	// Function for copying to string. Definition for custom classes is left to the user.
	// Returns number of characters written including the null terminating character.
	// Already defined for: char*, int, uint, float, double
	int debug(char* buf, int n);
	
	~llist();
};

#include "llist.cpp"
#endif
