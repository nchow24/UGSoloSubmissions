//nchow24	CS2210A		Nov 18, 2016
//Class Key creates a key with 2 attributes:
//  - String word
//  - Integer type

public class Key {
	
	private String word;							//Key's word
	private int type;								//Key's type
	
	public Key(String word, int type){
		word = word.toLowerCase();
		this.word = word;
		this.type = type;
	}
	
	//returns Key's word
	public String getWord(){
		return word;
	}
	
	//returns Key's type
	public int getType(){
		return type;
	}
	
	//compares 2 keys (0 if they are equal, -1 is this key is lesser, 1 is this key is greater
	public int compareTo(Key k){
		if ( (this.word.equals(k.getWord())) && this.type == (k.getType())){
			return 0;
		} else {
			if ((this.word.compareTo(k.getWord()) < 0) || ( this.word.equals(k.getWord()) && (this.type < k.getType()) )){
				return -1;
			} else {
				return 1;
			}
		}
	}
}