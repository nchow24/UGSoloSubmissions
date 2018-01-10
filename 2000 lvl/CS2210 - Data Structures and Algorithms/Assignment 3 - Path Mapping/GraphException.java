//nchow24	CS2210A		Dec 6, 2016
//GraphException class for exceptions:
//  - nonexistent nodes
//  - already existing edges 

public class GraphException extends RuntimeException {
	
	public GraphException(String object, String action){
		super("Error: " + object + " " + action);
	}
}
