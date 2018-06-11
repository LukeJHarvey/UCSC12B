public class Queue implements QueueInterface {
	private class Node {
		Object item;
		Node next;
		Node(Object item) {
			this.item = item;
			this.next = null;
		}
	}

	private Node head;
	private Node tail;
	private int numItems;

	Queue() {
		numItems = 0;
		head = null;
		tail = null;
	}

	// isEmpty()
	// pre: none
	// post: returns true if this Queue is empty, false otherwise
	public boolean isEmpty() {
		return (numItems==0);
	}

	// length()
	// pre: none
	// post: returns the length of this Queue.
	public int length() {
		return numItems;
	}

	// enqueue()
	// adds newItem to back of this Queue
	// pre: none
	// post: !isEmpty()
	public void enqueue(Object newItem) {
		if(numItems==0) {
			head = new Node(newItem);
			tail = head;
		}
		else {
			tail.next = new Node(newItem);
			tail = tail.next;
		}
		numItems++;
	}

	// dequeue()
	// deletes and returns item from front of this Queue
	// pre: !isEmpty()
	// post: this Queue will have one fewer element
	public Object dequeue() throws QueueEmptyException {
		if(isEmpty()){
			throw new QueueEmptyException("cannot dequeue() empty queue");
		}
		if(numItems==1) {
			numItems--;
			Object item = head.item;
			head = null;
			tail = null;
			return item;
		}
		else {
			numItems--;
			Object item = head.item;
			head = head.next;
			return item;
		}
	}

	// peek()
	// pre: !isEmpty()
	// post: returns item at front of Queue
	public Object peek() throws QueueEmptyException {
		if(isEmpty()) {
			throw new QueueEmptyException("cannot dequeue() empty queue");
		}
		return head.item;
	}

	// dequeueAll()
	// sets this Queue to the empty state
	// pre: !isEmpty()
	// post: isEmpty()
	public void dequeueAll() throws QueueEmptyException {
		if(isEmpty()) {
			throw new QueueEmptyException("cannot dequeue() empty queue");
		}
		head = null;
		tail = null;
		numItems = 0;
	}

	// toString()
	// overrides Object's toString() method
	public String toString() {
		String s = "";
		Node curr = head;
		while(curr != null) {
			s += curr.item + " ";
			curr = curr.next;
		}
		return s;
	}
}