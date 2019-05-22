
/*
	Doubly-Linked-List reference - by hieutran

	Declare a list example:				List<double> myList;		O(1)
	Get size of the list:				myList.size()			O(1)
	Check whether the list is empty:		myList.isEmpty()		O(1)
	
	add an element to the back of the list:		myList.addLast(value);		O(1)
	add an element to the front of the list:	myList.addFirst(value);		O(1)
	add an element to the i-th position:		myList.add(i, value);		O(N)

	remove the first element:			myList.removeFirst();		O(1)
	remove the last element:			myList.removeLast();		O(1)
	remove all the elements:			myList.removeAll();		O(1)
	remove the i-th element:			myList.remove(i);		O(N)

	Sort the list from L to R-1:			myList.sort(myList.iterator()+L, myList.iterator()+R);	O(NlogN)

	print the list:					myList.print();			O(N)
	print the list in reversed order:		myList.printReverse();		O(N);
*/

#include <iostream>
using namespace std;

template<class T>
class ListNode {
public:
	T value;
	ListNode* prev;
	ListNode* next;

	ListNode() {
		next = nullptr;
		prev = nullptr;
	}
	ListNode(T _value, ListNode* _prev, ListNode* _next) {
		value = _value;
		next = _next;
		prev = _prev;
	}
};

template<class T> 
class ListIterator {
private:
	ListNode<T>* nodePointer;

public: 
	//create
	ListIterator() {
		nodePointer = nullptr;
	}
	ListIterator(ListNode<T>* _nodePointer) {
		nodePointer = _nodePointer;
	}

	//read
	ListNode<T>*& get() {
		return nodePointer;
	}
	T value() {
		return nodePointer->value;
	}
	
	//operators
	ListIterator<T> operator = (ListIterator<T> other) {
		this->nodePointer = other.nodePointer;
		return other.nodePointer;
	}
	ListIterator<T> operator + (int i) {
		ListIterator<T> itr = *this;
		while (i--) {
			itr.nodePointer = itr.nodePointer->next;
		}
		return itr;
	}
	ListIterator<T> operator - (int i) {
		ListIterator<T> itr = *this;
		while (i--) {
			itr.nodePointer = itr.nodePointer->prev;
		}
		return itr;
	}
	ListIterator<T>& operator ++ () {
		nodePointer = nodePointer->next;
		return *this;
	}
	ListIterator<T>& operator -- () {
		nodePointer = nodePointer->prev;
		return *this;
	}
	ListIterator<T> operator ++ (int) {
		ListIterator<T> oldValue = *this;
		++(*this);
		return oldValue;
	}
	ListIterator<T> operator -- (int) {
		ListIterator<T> oldValue = *this;
		--(*this);
		return oldValue;
	}
	bool operator == (ListIterator<T> other) {
		return this->nodePointer == other.nodePointer;
	}
	bool operator != (ListIterator<T> other) {
		return this->nodePointer != other.nodePointer;
	}
};

template<class T>
class List {
public:
	ListIterator<T> head;
	ListIterator<T> tail;
	int length;

	//Create
	List() {
		head = ListIterator<T>(new ListNode<T>(0, nullptr, nullptr));
		tail = ListIterator<T>(new ListNode<T>(1, nullptr, nullptr));

		head.get()->next = tail.get();
		tail.get()->prev = head.get();
		length = 0;
	}

	//Read
	ListIterator<T> iterator() {
		return head+1;
	}
	ListIterator<T> lastIterator() {
		return tail;
	}
	ListIterator<T> riterator() {
		return tail-1;		
	}
	ListIterator<T> rlastIterator() {
		return head;
	}

	bool isEmpty() {
		return length == 0;
	}

	int size() {
		return length;
	}
	 
	//Update
	bool add(ListIterator<T> itr, T value) {
		if (itr == head) return false;
		ListNode<T>* currentNode = itr.get();
		ListNode<T>* frontNode = itr.get()->prev;
		ListNode<T>* newNode = new ListNode<T>(value, frontNode, currentNode);

		frontNode->next = newNode;
		currentNode->prev = newNode;
		length++;

		return true;
	}
	bool add(int index, T value) {
		return add(head+index+1, value);
	}

	bool addFirst(T value) {
		return add(head+1, value);
	}
	bool addLast(T value) {
		return add(tail, value);
	}

	//Delete
	T remove(ListIterator<T> itr) {
		if (itr == head || itr == tail) return 0;
		if (length == 0) return 0;

		ListNode<T>* frontNode = itr.get()->prev;
		ListNode<T>* backNode = itr.get()->next;

		backNode->prev = frontNode;
		frontNode->next = backNode;

		T removeValue = itr.value();

		delete itr.get();
		length--;

		return removeValue;
	}
	T remove(int index) {
		if (index < 0 || length <= index) return 0;
		return remove(head+1+index);
	}
	T removeFirst() {
		return remove(head+1);
	}
	T removeLast() {
		return remove(tail-1);
	}
	void removeAll() {
		for (ListIterator<T> itr = iterator(); itr != lastIterator(); itr++) {
			delete(itr.get());
		}

		head.get()->next = tail.get();
		tail.get()->prev = head.get();
		length = 0;
	}
	
	//algorithm
	void sort(ListIterator<T> begin, ListIterator<T> end) {
		int numberOfElement = 0;
		for (ListIterator<T> itr = begin; itr != end; itr++) {
			numberOfElement++;
		}
		if (numberOfElement <= 1) return;

		ListIterator<T> midPosition = begin+numberOfElement/2;
		T mid = midPosition.value();
		
		ListIterator<T> i = begin;
		ListIterator<T> j = end-1;

		while (i != j+1 && i != j+2) {
			while (i.value() < mid) i++;
			while (j.value() > mid) j--;
			if (i != j+1 && i != j+2) {
				T temp = i.get()->value;
				i.get()->value = j.get()->value;
				j.get()->value = temp;
				i++; j--;
			}
		}
		sort(begin, j+1);
		sort(i, end);
	}
	//others
	void print() {
		cout << "List: ";
		for (ListIterator<T> itr = iterator(); itr != lastIterator(); itr++) {
			cout << itr.value() << " ";
		}
		cout << endl << endl;
	}

	void printReverse() {
		cout << "Reversed List: ";
		for (ListIterator<T> itr = riterator(); itr != rlastIterator(); itr--) {
			cout << itr.value() << " ";
		}
		cout << endl;
	}
};

int main() {
	List<double> list; // Create an empty Doubly Linked List
	
	for (int i = 0; i < 8; i++) {
		list.addFirst(i);  // Add an element to the front of the list
		list.addLast(i); // Add an element to the back of the list
	}

	list.print(); // print the list
	list.printReverse(); // print the list in reversed order

	list.add(5, -10); // add an element (-10) to the 5-th position
	
	list.removeFirst(); // remove the first element

	list.print();

	list.remove(2); // remove the element at position = 2

	list.print(); 

	list.sort(list.iterator() + 2, list.iterator()+10); // sort the list from 2-nd position to 10th position

	list.print();

	list.removeAll(); // remove all the elements

	list.print();

	return 0;
}
