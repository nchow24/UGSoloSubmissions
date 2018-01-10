//nchow24	CS2210A		Dec 6, 2016
//Class Node used to implement road map

public class Node {
	private int name;					//Node's name
	private Boolean mark;				//Node's mark (false = unvisited, true = visted)
	
	public Node(int name){
		this.name = name;
		mark = false;
	}
	
	//sets Node's mark
	public void setMark(boolean mark){
		this.mark = mark;
	}
	
	//gets Node's mark
	public Boolean getMark(){
		return mark;
	}
	
	//gets Node's name
	public int getName(){
		return name;
	}
}
