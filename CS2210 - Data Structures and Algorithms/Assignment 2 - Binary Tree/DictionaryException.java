//nchow24	CS2210A		Nov 18, 2016
//DictionaryException class for exceptions:
//  - removing a nonexistent record
//  - inserting a record with key that already exists

public class DictionaryException extends RuntimeException {
	
	public DictionaryException(String action, String state){
		super(action + " error: key " + state);
	}
}
