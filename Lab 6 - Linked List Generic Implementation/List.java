public class List<T> implements ListInterface<T>{

	private class Node<T>{
		T item;
		Node<T> next;
		Node(T x) {
			item = x;
			next = null;
		}
	}

	private Node<T> head;
	private int numItems;

	public List(){
		head = null;
		numItems = 0;
	}

	private Node<T> find(int index) {
		Node<T> N = head;
		for(int i=1; i<index; i++) {
			N = N.next;
		}
		return N;
	}

	public boolean isEmpty() {
		return(numItems == 0);
	}

	public int size() {
		return numItems;
	}

	public T get(int index) throws ListIndexOutOfBoundsException {
		if( index<1 || index>numItems ){
        	throw new ListIndexOutOfBoundsException(
        		"List Error: get() called on invalid index: " + index);
    	}
    	return find(index).item;
	}

	public void add(int index, T newItem) throws ListIndexOutOfBoundsException {
		if( index<1 || (index-1>numItems) ){
        	throw new ListIndexOutOfBoundsException(
        		"List Error: get() called on invalid index: " + index);
    	}
    	if(index == 1) {
    		Node<T> temp = head;
    		head = new Node<T>(newItem);
    		head.next = temp;
    	}
    	else {
	    	Node<T> N = find(index-1);
	    	N.next = new Node<T>(newItem);
	    }
    	numItems++;
	}

	public void remove(int index) throws ListIndexOutOfBoundsException {
		if( index<1 || index>numItems ){
        	throw new ListIndexOutOfBoundsException(
        		"List Error: get() called on invalid index: " + index);
    	}
    	if(index==1) {
    		head = head.next;
    		numItems--;
    	}
    	else {
    		Node<T> N = find(index-1);
    		N.next = N.next.next;
    		numItems--;
    	}
	}
	public void removeAll() {
		head = null;
		numItems = 0;
	}
	public String toString(){ 
		String str = "";
		for(int i = 1; i < numItems+1; i++) {
			str += find(i).item + " ";
		}
		return str;

	}  
}