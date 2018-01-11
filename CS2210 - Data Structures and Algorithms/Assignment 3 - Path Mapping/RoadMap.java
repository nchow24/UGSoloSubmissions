//nchow24	CS2210A		Dec 6, 2016
//Class RoadMap used to implement road map graph

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.StringTokenizer;

public class RoadMap {
	private Graph graph;						//graph of road map
	private Node startN;						//starting node
	private Node endN;							//destination node
	private int initAmount;						//start amount of $ available
	private int amount;							//amount left during road trip
	private int width;							//width of map
	private int length;							//length of map
	private int toll;							//price of toll road
	private int gain;							//reward for compensation road
	private ArrayList<Node> path;				//array of nodes marking path between 2 nodes
	
	public RoadMap(String inputFile) throws MapException {	
		String line = null;
		try{
			BufferedReader file = new BufferedReader(new FileReader(inputFile));
			///process first 8 lines
			for (int i = 1; i <=8; i++){
				line = file.readLine();
				if(i==2){
					startN = new Node(Integer.parseInt(line));
				} else {
					if (i ==3){
						endN = new Node(Integer.parseInt(line));
					} else {
						if (i==4){
							initAmount = Integer.parseInt(line);
							amount = initAmount;
						} else {
							if (i == 5){
								width = Integer.parseInt(line);
							} else {
								if (i==6){
									length = Integer.parseInt(line);
								} else {
									if (i==7){
										toll = Integer.parseInt(line);
									} else {
										if (i == 8){
											gain = Integer.parseInt(line);
										}
									}
								}
							}
						}
					}
				}
			}
			graph = new Graph(width*length);
			for (int i = 0; i<((length*2)-1); i++){
				line = file.readLine();
				int edgeType = 0;
				int node1;		//name of the first endpoint node
				int node2;		//name of the second endpoint node
				
				//create edges for nodes that are on the same row (adjacent horizontally)
				if (line.startsWith("+")){
					int j = 1;
					while (j<line.length()){
						//get type of edge
						if (line.charAt(j) !='X'){
							if (line.charAt(j)== 'T'){
								edgeType = 1;
							} else {
								if (line.charAt(j)=='C'){
									edgeType = -1;
								} else { 
									if (line.charAt(j) == 'F'){
										edgeType = 0;
									}
								}
							}
							//get the 2 endpoint nodes and insert edge
							node1 = (i/2)*width + ((j-1)/2);
							node2 = (i/2)*width + ((j+1)/2);
							graph.insertEdge(graph.getNode(node1), graph.getNode(node2), edgeType);
						}
						//get index of the next edge
						j = j + 2;
					}
					
				//create edges for nodes that are on different rows (adjacent vertically)
				} else {
					int j = 0;
					//get type of edge
					while (j<line.length()){
						if (line.charAt(j)!='X'){
							if (line.charAt(j)== 'T'){
								edgeType = 1;
							} else {
								if (line.charAt(j)=='C'){
									edgeType = -1;
								} else { 
									if (line.charAt(j) == 'F'){
										edgeType = 0;
									}
								}
							}
							
							//get the 2 endpoint nodes and insert the edge
							node1 = ((i-1)/2)*width + (j/2);
							node2 = ((i+1)/2)*width + (j/2);
							graph.insertEdge(graph.getNode(node1), graph.getNode(node2), edgeType);
						}
						//get index of the next edge
						j = j +2;
					}
				}
			}
		} catch (MapException | IOException e){
			throw new MapException();
		}
	}
	
	//returns graph of road map
	public Graph getGraph(){
		return graph;
	}
	
	//returns name of starting node
	public int getStartingNode(){
		return startN.getName();
	}
	
	//returns name of destination node
	public int getDestinationNode(){
		return endN.getName();
	}
	
	//return starting money amount
	public int getInitialMoney(){
		return initAmount;
	}
	
	//returns iterator of the path from start to destination
	public Iterator<Node> findPath(int start, int destination, int initialMoney){
		path = new ArrayList<Node>();
		
		//return iterator if a path exists
		if (pathExists(start, destination)) {
			Iterator<Node> iter = path.iterator();
			return iter;
		} else {
			return null;
		}
	}

	//checks if a path exists from start to finish, if so, fills an array of the path
	private Boolean pathExists(int start, int destination){
		Node begin = graph.getNode(start);
		Node dest = graph.getNode(destination);
		markNode(begin);
		
		//add node to a path list
		path.add(begin);
		
		//return true if we are at the destination
		if (begin.getName() == dest.getName()){
			return true;
		} else {
			//get the incidents of node
			Iterator<Edge> incident = graph.incidentEdges(begin);
			while (incident.hasNext()){
				Edge edge = incident.next();
				
				//check if the edges connecting the node can lead to the destination 
				if (!isVisited(edge.secondEndpoint())){
					if (edge.getType() == 0 || edge.getType() == -1 || ((edge.getType() == 1) && amount >= toll)){
						//adjust amount of money left 
						if (edge.getType() == -1){
							amount = amount - gain;
						} else {
							if (edge.getType() == 1){
								amount = amount - toll;
							}
						}
						if (pathExists(edge.secondEndpoint().getName(), destination)){
							return true;
						}
					}
				}
			}
			
			//unmark last visited node if all incidents are exhausted
			Node prev = path.get(path.size()-1);
			unmarkNode(prev);
			if (path.size() >=2){
				//undo the toll/compensation
				if (graph.getEdge(prev, path.get(path.size()-2)).getType() == 1){
					amount = amount + toll;
				} else {
					if (graph.getEdge(prev, path.get(path.size()-2)).getType() == -1){
						amount = amount + gain;
					}
				}
			}
			
			//go back the path 1 node
			path.remove(path.size()-1);
			return false;
		}
	}
	
	//marks a node as visited 
	private void markNode(Node node){
		node.setMark(true);
	}
	
	//unmark node (mark as not visited)
	private void unmarkNode(Node node){
		node.setMark(false);
	}
	
	//checks if a node has been visited
	private Boolean isVisited(Node node){
		return node.getMark();
	}

}
