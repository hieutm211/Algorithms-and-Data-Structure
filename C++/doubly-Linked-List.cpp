
/*
	Doubly-Linked-List reference - by hieutran

	Declare a list example:				List<double> myList;		O(1)
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

	ListIterator<T> mergeSort(ListIterator<T> begin, ListIterator<T> end) {
		int numberOfElement = 0;
		for (ListIterator<T> itr = begin; itr != end; itr++) {
			numberOfElement++;
		}

		if (numberOfElement <= 1) {
			return begin;
		}

		ListIterator<T> leftPtr = begin; 
		ListIterator<T> rightPtr = begin + numberOfElement/2;

		leftPtr = mergeSort(leftPtr, rightPtr);  //sort [leftPtr..endLeft-1]
		rightPtr = mergeSort(rightPtr, end); //sort [rightPtr..rightPtr-1]

		//merge
		begin = leftPtr;

		while (leftPtr != rightPtr && rightPtr != end) {
			if (leftPtr.value() <= rightPtr.value()) {
				leftPtr++;
			} else {
				add(leftPtr, rightPtr.value());	
				if (leftPtr == begin) begin--;
				ListIterator<T> temp = rightPtr;
				rightPtr++;
				remove(temp);
			}
		}
		return begin;
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

	string cmd;
	while (cin >> cmd, cmd != "end") {
		system("clear");

		if (cmd == "add") {
			cin >> cmd;
			
			if (cmd == "first") {
				int value;
				cin >> value;
				list.addFirst(value);
			} else if (cmd == "last") {
				int value;
				cin >> value;
				list.addLast(value);
			} else if (cmd == "index") {
				int index, value;
				cin >> index >> value;
				list.add(index, value);
			}
		} else if (cmd == "remove") {
			cin >> cmd;

			if (cmd == "first") {
				list.removeFirst();
			} else if (cmd == "last") {
				list.removeLast();
			} else if (cmd == "index") {
				int index;
				cin >> index;
				list.remove(index);
			}
		} else if (cmd == "sort") {
			list.sort(list.iterator(), list.lastIterator());
		} else if (cmd == "mergesort") {
			list.mergeSort(list.iterator(), list.lastIterator());	
		}

		list.print();
	}

	return 0;
}
