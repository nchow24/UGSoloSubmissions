//nchow24	CS2210A		Oct 19, 2016
//Class Node used to implement a linked list

public class Node<T>
{
    private Node<T> next;				//Node's next element
    private T element;					//Node's element
 
    //creates an empty Node
    public Node(){
        next = null;
        element = null;
    }
    
    //creates a Node with an element
    public Node(T elem){
        next = null;
        element = elem;
    }
    
    //gets Node's next node
    public Node<T> getNext(){
        return next;
    }
    
    //sets Node's next node
    public void setNext(Node<T> node){
        next = node;
    }
    
    //gets Node's element
    public T getElement(){
        return element;
    }
    
    //sets Node's element
    public void setElement(T elem){
        element = elem;
    }
}