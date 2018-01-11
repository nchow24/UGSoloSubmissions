//nchow24	CS2210A		Dec 6, 2016
//Class Graph used to implement road map of nodes and edges

import java.util.ArrayList;
import java.util.Iterator;

public class Graph implements GraphADT {
	private int nodes;						//# of nodes
	private ListNode<Object>[] list;		//adjacency list where list[i] = node with name = i and list[i]'s links hold edges connecting node with name = i and another node
	
	public Graph(int n){
		list = (ListNode<Object>[]) new ListNode[n];
		nodes = n;
		
		//set nodes with name = i in list[i]
		for (int i = 0; i<nodes; i++){
			Node node = new Node(i);
			ListNode<Object> listNode = new ListNode<Object>(node);
			list[i] = listNode;
		}
	}

	//return node with target name if it exists, else throw exception 
	public Node getNode(int name) throws GraphException{
		if (name >= nodes){
			throw new GraphException("node", "doesn't exist");
		} else {
			return (Node) ((list[name]).getElem());
		}
	}
	
	//insert edge between 2 nodes if the nodes exist and there isn't already an existing edge
	public void insertEdge(Node u, Node v, int edgeType) throws GraphException{
		//throw exception if at least 1 node doesn't exist
		if (u.getName()>=nodes || v.getName()>=nodes){
			throw new GraphException("At least 1 node", "doesn't exist");
		} else {
			ListNode<Object> node = list[u.getName()];
			while (node.getNext() != null){
				node = node.getNext();
				//throw exception if target edge exists
				if (((((Edge) node.getElem()).secondEndpoint()).getName()) == v.getName()){
					throw new GraphException("edge", "already exists");
				}
			}
			//add edge to the list linked to list[u.getName]
			//the edges in this list will have the first endpoint as u
			Edge edge1 = new Edge(u,v,edgeType);
			ListNode<Object> listNode1 = new ListNode<Object>(edge1);
			if (list[u.getName()].getNext() == null){
				list[u.getName()].setNext(listNode1);
			} else {
				listNode1.setNext(list[u.getName()].getNext());
				list[u.getName()].setNext(listNode1);
			}
			
			//add edge to the list linked to list[v.getName]
			//the edges in this list will have the first endpoint as v
			Edge edge2 = new Edge(v,u,edgeType);
			ListNode<Object> listNode2 = new ListNode<Object>(edge2);
			if (list[v.getName()].getNext() == null){
				list[v.getName()].setNext(listNode2);
			} else {
				listNode2.setNext(list[v.getName()].getNext());
				list[v.getName()].setNext(listNode2);
			}
		}
	}
	
	//return iterator of the edges that are incident to u
	public Iterator<Edge> incidentEdges(Node u) throws GraphException{
		//throw exception if u doesn't exist
		if (u.getName()>= nodes){
			throw new GraphException("node", "doesn't exists");
		}
		//create ArrayList of incident edges
		ArrayList<Edge> incident = new ArrayList<Edge>();
		Boolean incidentExists = false;
		
		ListNode<Object> node = list[u.getName()];
		while (node.getNext() != null){
			node = node.getNext();
			incident.add((Edge)node.getElem());
			incidentExists = true;
		}
		
		//return iterator only if incidents exist
		if (incidentExists){
			Iterator<Edge> iter = incident.iterator();
			return iter;
		} else {
			return null;
		}
	}
	
	//return the edge connecting u and v if it exists
	public Edge getEdge(Node u, Node v) throws GraphException{
		//throw exception if at least 1 node doesn't exist
		if (u.getName()>=nodes || v.getName()>= nodes){
			throw new GraphException("At least 1 node", "doesn't exist");
		} else {
			//search for target edge
			ListNode<Object> node = list[u.getName()];
			while (node.getNext() != null){
				node = node.getNext();
				if (((((Edge) node.getElem()).secondEndpoint()).getName()) == v.getName()){
					return (Edge) node.getElem();
				}
			} 
			//throw exception if target edge doesn't exist
			throw new GraphException("edge", "doesn't exist");
		}
	}
	
	//check if 2 nodes are adjacent
	public boolean areAdjacent(Node u, Node v) throws GraphException{
		//throw exception if at least 1 node doesn't exist
		if (u.getName()>=nodes || v.getName()>= nodes){
			throw new GraphException("At least 1 node", "doesn't exist");
		} else {
			if (((u.getName()-1)== v.getName()) || ((u.getName()+1)== v.getName()) || ((u.getName() + 3)==v.getName()) || ((u.getName()-3)==v.getName())){
				return true;
			} else {
				return false;
			}
		}
	}
	
}

