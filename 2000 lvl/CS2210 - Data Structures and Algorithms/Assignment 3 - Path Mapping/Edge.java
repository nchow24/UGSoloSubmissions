//nchow24	CS2210A		Dec 6, 2016
//Class Edge used to implement connections between nodes in a road map

public class Edge {
	private Node endpt1;			//Edge's first endpoint
	private Node endpt2;			//Edge's second endpoint
	private int type;				//Edge's type
	String label;					//Edge's label
	
	public Edge(Node u, Node v, int type){
		endpt1 = u;
		endpt2 = v;
		this.type = type;
		label = null;
	}
	
	//get Edge's first endpoint
	public Node firstEndpoint(){
		return endpt1;
	}
	
	//get Edge's second endpoint
	public Node secondEndpoint(){
		return endpt2;
	}
	
	//get Edge's type
	public int getType(){
		return type;
	}
	
	//set Edge's label
	public void setLabel(String label){
		this.label = label;
	}
	
	//get Edge's label
	public String getLabel(){
		return label;
	}

}
