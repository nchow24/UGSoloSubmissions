//nchow24	CS2210A		Nov 18, 2016
// Class Record creates a record with 2 attributes:
//   - Key data
//   - String data

public class Record {
	private Key key;										//Record's key
	private String data;									//Record's data
	
	public Record(Key k, String data){
		this.key = k;
		this.data = data;
	}
	
	//returns Record's key
	public Key getKey(){
		return key;
	}
	
	//returns Record's data
	public String getData(){
		return data;
	}

}
