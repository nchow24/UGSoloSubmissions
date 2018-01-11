//nchow24	CS2210A		Nov 18, 2016
//Class Node used to implement a binary search tree

public class Node<T>
{
    private Node<T> left;				//Node's left node
    private Node<T> right;				//Node's right node
    private Node<T> parent;				//Node's parent node
    private T element;					//Node's element
 
    //creates an empty Node
    public Node(){
        left = null;
        right = null;
        parent = null;
        element = null;
    }
    
    //creates a Node with an element
    public Node(T elem){
        left = null;
        right = null;
        parent = null;
        element = elem;
    }
    
    //gets Node's left node
    public Node<T> getLeft(){
        return left;
    }
    
    //sets Node's left node
    public void setLeft(Node<T> node){
        left = node;
    }
    //gets Node's right node
    public Node<T> getRight(){
        return right;
    }
    
    //sets Node's right node
    public void setRight(Node<T> node){
        right = node;
    }
    
    //gets Node's parent node
    public Node<T> getParent(){
        return parent;
    }
    
    //sets Node's parent node
    public void setParent(Node<T> node){
        parent = node;
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