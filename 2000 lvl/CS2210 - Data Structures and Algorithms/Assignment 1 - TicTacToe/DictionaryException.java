//nchow24	CS2210A		Oct 19, 2016
//DictionaryException class for exceptions:
//  - removing a nonexistent configuration
//  - inserting an already existing configuration

public class DictionaryException extends RuntimeException {
	
	public DictionaryException(String action, String state){
		super(action + " error: configuration " + state);
	}
}
