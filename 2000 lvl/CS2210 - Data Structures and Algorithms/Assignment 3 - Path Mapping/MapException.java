//nchow24	CS2210A		Dec 6, 2016
//MapException class for exceptions:
//  - nonexistent files

public class MapException extends RuntimeException {
	
	public MapException(){
		super("Input file doesn't exist!");
	}
}
