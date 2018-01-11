//nchow24	CS2210A		Oct 19, 2016
//Dictionary class creates a hashTable with each entry pointing to a linked list
//hashTable uses polynomial hash function to determine keys

public class Dictionary implements DictionaryADT {
	
	private Node<ConfigData>[] hashTable;
	
	
	//creates an empty array 
	public Dictionary(int size){
		hashTable = (Node<ConfigData>[]) new Node[size];
	}

	//insert data into Dictionary if it is not already there
		public int insert(ConfigData pair) throws DictionaryException{
			//check if pair already exists
			if (find(pair.getConfig())!=-1){
				throw new DictionaryException("insertion", "already exists");
			} else {
				int code = polyHashCode(pair.getConfig());
				Node<ConfigData> node = new Node<ConfigData>(pair);
				//Determine if a collision has occurred. Insert at hashTable[code] if no collision, else link the node in linked list
				if (hashTable[code]==null){
					hashTable[code]=node;
					return 0;
				} else {
					node.setNext(hashTable[code]);
					hashTable[code]=node;
					return 1;
				}				
			}		
		}
	
	//remove configuration from Dictionary if it exists, else throw exception
	public void remove(String config) throws DictionaryException{
		//check if config exists
		if (find(config)==-1){
			throw new DictionaryException("removal", "doesn't exist");
		} else {
			int code = polyHashCode(config);
			Node<ConfigData> node = hashTable[code];
			//if hashTable[code] is the target to be removed, make the next node hashTable[code]
			if (node.getElement().getConfig().equals(config)){
				hashTable[code]=node.getNext();
			} else {
				//find location of target in linked list, make target's previous node point to target's next node
				Node<ConfigData> prevnode = node;
				node = node.getNext();
				while (!node.getElement().getConfig().equals(config)){
					prevnode = node;
					node = node.getNext();
				}
				prevnode.setNext(node.getNext());
			}
		}
	}
	
	//finds config in Dictionary, return config's score if in Dictionary, else -1
	public int find(String config){
		int code = polyHashCode(config);
		Node<ConfigData> node = hashTable[code];
		//find target node
		while ((node!=null) && (!node.getElement().getConfig().equals(config))){
			node = node.getNext();
		}
		//if node is  null then config doesn't exist, else config has been found in hashTable
		if (node==null){
			return -1;
		} else {
			return node.getElement().getScore();
		}
	}
		
	//computes the polynomial hashcode to find the target key
	private int polyHashCode(String config){
		int code=0;
		for (int i=0; i<config.length(); i++){
			code = (int) ((code + ((int)config.charAt(i)*Math.pow(33, i))% hashTable.length))% hashTable.length;	
		}
		return code;
	}

}
