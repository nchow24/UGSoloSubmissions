//nchow24	CS2210A		Dec 6, 2016
//Class ListNode used to implement an adjacency list

public class ListNode<T>
{
    private ListNode<T> next;			//ListNode's next element
    private T element;					//ListNode's element

    
    //creates a ListNode with an element
    public ListNode(T elem){
        next = null;
        element = elem;
    }
    
    //gets ListNode's next node
    public ListNode<T> getNext(){
        return next;
    }
    
    //returns ListNode's element
    public T getElem(){
    	return element;
    }
    
    //returns ListNode's next ListNode
    public void setNext(ListNode<T> n){
    	next = n;
    }
}