/* LLIST_NODE */
template <class T>
llist_node<T>::llist_node() : next(NULL), prev(NULL) {}

template <class T>
llist_node<T>::llist_node(T value) : next(NULL), prev(NULL), value(value) {}

template <class T>
llist_node<T>::llist_node(T value, llist_node<T>* prev, llist_node<T>* next, bool doinsert) : value(value), next(next), prev(prev) {
	if (doinsert) {
		if (prev != NULL) {
			prev->next = this;
		}
		if (next != NULL) {
			next->prev = this;
		}
	}
}

/* LLIST */
template <class T>
llist<T>::llist() : first(NULL), last(NULL), size(0) {}

template <class T>
llist<T>::llist(T value) : size(1) {
	first = new llist_node<T>(value);
	last = first;
}

template <class T>
llist<T>::llist(const llist<T>& o) {
	size = o.size;
	
	llist_node<T>* ocur = o.first;
	llist_node<T>* ncur = new llist_node<T>(ocur->value);
	first = ncur;
	
	for (int i = 0; i < size-1; i++) {
		ocur = ocur->next;
		ncur->next = new llist_node<T>(ocur->value);
		ncur->next->prev = ncur;
		ncur = ncur->next;
	}
	last = ncur;
}

template <class T>
T llist<T>::operator[](int i) const {
	if (i >= 0) {
		if (i >= size) {
			printf("LList index out of bounds\n");
			exit(1);
		}
		
		llist_node<T>* cursor = first;
		for (int j = 0; j < i; j++) {
			cursor = cursor->next;
		};
		
		return cursor->value;
	}
	else {
		if (-i > size) {
			printf("LList index out of bounds\n");
			exit(1);
		}
		
		llist_node<T>* cursor = last;
		for (int j = -1; j > i; j--) {
			cursor = cursor->prev;
		}
		return cursor->value;
	}
}

template <class T>
T& llist<T>::operator[](int i) {
	if (i >= 0) {
		if (i >= size) {
			printf("LList index out of bounds\n");
			exit(1);
		}
		
		llist_node<T>* cursor = first;
		for (int j = 0; j < i; j++) {
			cursor = cursor->next;
		};
		
		return cursor->value;
	}
	else {
		if (-i > size) {
			printf("LList index out of bounds\n");
			exit(1);
		}
		
		llist_node<T>* cursor = last;
		for (int j = -1; j > i; j--) {
			cursor = cursor->prev;
		}
		return cursor->value;
	}
}

template <class T>
void llist<T>::prepend(const T& value) {
	first = new llist_node<T>(value, NULL, first, true);
	size++;
	if (size == 1) {
		last = first;
	}
}

template <class T>
void llist<T>::append(const T& value) {
	last = new llist_node<T>(value, last, NULL, true);
	size++;
	if (size == 1) {
		first = last;
	}
}

template <class T>
void llist<T>::insert(int i, const T& value) {
	llist_node<T>* cursor;
	if (i >= 0) {
		if (i >= size) {
			printf("LList index out of bounds\n");
			exit(1);
		}
		
		cursor = first;
		for (int j = 0; j < i; j++) {
			cursor = cursor->next;
		}
	
		if (cursor == first) {
			prepend(value);
			return;
		}
		else {
			new llist_node<T>(value, cursor->prev, cursor, true);
		}
	}
	else {
		if (-i > size) {
			printf("LList index out of bounds\n");
			exit(1);
		}
		
		cursor = last;
		for (int j = -1; j > i; j--) {
			cursor = cursor->prev;
		}
	
		if (cursor == last) {
			append(value);
			return;
		}
		else {
			new llist_node<T>(value, cursor, cursor->next, true);
		}
	}
	size++;
}

template <class T>
void llist<T>::remove(int i) {
	llist_node<T>* cursor;
	if (i >= 0) {
		if (i >= size) {
			printf("LList index out of bounds\n");
			exit(1);
		}
		
		cursor = first;
		for (int j = 0; j < i; j++) {
			cursor = cursor->next;
		}
	}
	else {
		if (-i > size) {
			printf("LList index out of bounds\n");
			exit(1);
		}
		
		cursor = last;
		for (int j = -1; j > i; j--) {
			cursor = cursor->prev;
		}
	}
	if (cursor == first) {
		if (size == 1) {
			delete first;
			first = NULL;
			last = NULL;
		}
		else {
			first = first->next;
			delete first->prev;
			first->prev = NULL;
		}
	}
	else if (cursor == last) {
		last = last->prev;
		delete last->next;
		last->next = NULL;
	}
	else {
		cursor->prev->next = cursor->next;
		cursor->next->prev = cursor->prev;
		delete cursor;
	}
	
	size--;
}

template <class T>
void llist<T>::validate() {
	llist_node<T>** known_p = new llist_node<T>*[size];
	
	llist_node<T>* cur = first;
	
	if (size == 0) {
		if (first != NULL) {
			printf("llist corrupted; first node is not null but size is 0.\n");
			exit(1);
		}
		if (last != NULL) {
			printf("llist corrupted; last node is not null but size is 0.\n");
			exit(1);
		}
		return;
	}
	
	if (first == NULL) {
		printf("llist corrupted; size is %d but first node is null.\n", size);
		exit(1);
	}
	if (last == NULL) {
		printf("llist corrupted; size is %d but last node is null.\n", size);
		exit(1);
	}
	if (size == 1 && first != last) {
		printf("llist corrupted; size is 1 but first and last node are not equal.\n");
		exit(1);
	}
	
	if (cur->prev != NULL) {
		printf("llist corrupted; first node has a predecessor.\n");
		exit(1);
	}
	if (last->next != NULL) {
		printf("llist corrupted; last node has a successor.\n");
		exit(1);
	}
	
	for (int i = 0; i < size; i++) {
		known_p[i] = cur;
		
		for (int j = 0; j < i; j++) {
			if (known_p[i] == known_p[j]) {
				printf("llist corrupted; nodes %d and %d are identical.\n", i, j);
				exit(1);
			}
		}
		
		if (i == size-1) {
			if (last != cur) {
				printf("llist corrupted; last is not set to the final list element.\n");
				exit(1);
			}
		}
		
		cur = cur->next;
	}
}

template <class T>
llist<T>::~llist() {
	if (first == NULL) {
		return;
	}
	
	llist_node<T>* cursor = first;
	while (1) {
		if (cursor->next == NULL) {
			delete cursor;
			return;
		}
		
		cursor = cursor->next;
		delete cursor->prev;
	}
}

// Converting array to string representation. Each variant has its own specialized function definition.
template <>
int llist<int>::debug(char* buf, int n) {
	if (n > 1) {
		buf[0] = '{';
		buf[1] = '\0';
	} else {
		buf[0] = '\0';
		return 1;
	}
	
	int rn = 1;
	
	llist_node<int>* cursor = first;
	rn += snprintf(buf+1, n-1, "%d", cursor->value);
	
	while (1) {
		if (rn >= n) {
			buf[n-1] = '\0';
			return n;
		}
		
		cursor = cursor->next;
		if (cursor == NULL) {
			if (n-rn >= 2) {
				buf[rn] = '}';
				buf[rn+1] = '\0';
				return rn+2;
			}
			return rn+1;
		}
		
		rn += snprintf(buf+rn, n-rn, ", %d", cursor->value);
	}
}

template <>
int llist<int*>::debug(char* buf, int n) {
	if (n > 1) {
		buf[0] = '{';
		buf[1] = '\0';
	} else {
		buf[0] = '\0';
		return 1;
	}
	
	int rn = 1;
	
	llist_node<int*>* cursor = first;
	rn += snprintf(buf+1, n-1, "%d", *(cursor->value));
	
	while (1) {
		if (rn >= n) {
			buf[n-1] = '\0';
			return n;
		}
		
		cursor = cursor->next;
		if (cursor == NULL) {
			if (n-rn >= 2) {
				buf[rn] = '}';
				buf[rn+1] = '\0';
				return rn+2;
			}
			return rn+1;
		}
		
		rn += snprintf(buf+rn, n-rn, ", %d", *(cursor->value));
	}
}

template <>
int llist<unsigned int>::debug(char* buf, int n) {
	if (n > 1) {
		buf[0] = '{';
		buf[1] = '\0';
	} else {
		buf[0] = '\0';
		return 1;
	}
	
	int rn = 1;
	
	llist_node<unsigned int>* cursor = first;
	rn += snprintf(buf+1, n-1, "%u", cursor->value);
	
	while (1) {
		if (rn >= n) {
			buf[n-1] = '\0';
			return n;
		}
		
		cursor = cursor->next;
		if (cursor == NULL) {
			if (n-rn >= 2) {
				buf[rn] = '}';
				buf[rn+1] = '\0';
				return rn+2;
			}
			return rn+1;
		}
		
		rn += snprintf(buf+rn, n-rn, ", %u", cursor->value);
	}
}

template <>
int llist<float>::debug(char* buf, int n) {
	if (n > 1) {
		buf[0] = '{';
		buf[1] = '\0';
	} else {
		buf[0] = '\0';
		return 1;
	}
	
	int rn = 1;
	
	llist_node<float>* cursor = first;
	rn += snprintf(buf+1, n-1, "%f", cursor->value);
	
	while (1) {
		if (rn >= n) {
			buf[n-1] = '\0';
			return n;
		}
		
		cursor = cursor->next;
		if (cursor == NULL) {
			if (n-rn >= 2) {
				buf[rn] = '}';
				buf[rn+1] = '\0';
				return rn+2;
			}
			return rn+1;
		}
		
		rn += snprintf(buf+rn, n-rn, ", %f", cursor->value);
	}
}

template <>
int llist<double>::debug(char* buf, int n) {
	if (n > 1) {
		buf[0] = '{';
		buf[1] = '\0';
	} else {
		buf[0] = '\0';
		return 1;
	}
	
	int rn = 1;
	
	llist_node<double>* cursor = first;
	rn += snprintf(buf+1, n-1, "%lf", cursor->value);
	
	while (1) {
		if (rn >= n) {
			buf[n-1] = '\0';
			return n;
		}
		
		cursor = cursor->next;
		if (cursor == NULL) {
			if (n-rn >= 2) {
				buf[rn] = '}';
				buf[rn+1] = '\0';
				return rn+2;
			}
			return rn+1;
		}
		
		rn += snprintf(buf+rn, n-rn, ", %lf", cursor->value);
	}
}

template <>
int llist<char*>::debug(char* buf, int n) {
	if (n > 1) {
		buf[0] = '{';
		buf[1] = '\0';
	} else {
		buf[0] = '\0';
		return 1;
	}
	
	int rn = 1;
	
	llist_node<char*>* cursor = first;
	rn += snprintf(buf+1, n-1, "%s", cursor->value);
	
	while (1) {
		if (rn >= n) {
			buf[n-1] = '\0';
			return n;
		}
		
		cursor = cursor->next;
		if (cursor == NULL) {
			if (n-rn >= 2) {
				buf[rn] = '}';
				buf[rn+1] = '\0';
				return rn+2;
			}
			return rn+1;
		}
		
		rn += snprintf(buf+rn, n-rn, ", %s", cursor->value);
	}
}






