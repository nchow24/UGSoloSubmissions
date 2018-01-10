//nchow24	CS2210A		Nov 18, 2016
//Class UI user interface to interact with OrderedDictionary using commands:
//    - first
//    - last
//    - search
//    - insert
//    - remove
//    - prev
//    - next


import java.io.BufferedReader;
import java.io.FileReader;
import java.util.StringTokenizer;  

public class UI {
	private static OrderedDictionary dict = new OrderedDictionary();

	public static void main(String[] args) {
		String fileName = args[0];							// name of the input file
		Record record;										// record of node
		Key key;											// key of record
		String command;										// command from command line
		int number;											// number of tokens in a command line input
		StringTokenizer string;								// command line input
		
		try{
			//creating binary search tree from input file
			BufferedReader file = new BufferedReader(new FileReader(fileName));
			String keyWord = file.readLine();

			while (keyWord != null) {
				String data = file.readLine();
				int type;
				//determining type of data
				if (data.endsWith(".wav") || data.endsWith(".mid")){
					type = 2;
				} else {
					if (data.endsWith(".jpg") || data.endsWith(".gif")){
						type = 3;
					} else {
						type = 1;
					}
				}
				dict.insert(new Record(new Key(keyWord,type),data));
				keyWord = file.readLine();
			}
		} catch (Exception e){
			System.out.println("Error reading input file \n");
			return;
		}
		
		boolean running = true;
		while (running) {
			//get command line input 
			StringReader keyboard = new StringReader();
			String line = keyboard.read("Enter command: ");
			try {
				string = new StringTokenizer(line);
				number = string.countTokens();
				command = string.nextToken();
			} catch (Exception e){
				continue;
			}
			if (number ==1){
				//command inputs which need 1 token (end, first, last)
				if (command.equals("end")){
					return;
				} else {
					if (command.equals("first")){
						first();
					} else {
						if (command.equals("last")){
							last();
						} else {
							System.out.println("Invalid command\n");
						}
					}
				}
			} else {
				if (number == 2){ 
					//command inputs which need 2 tokens (search)
					if (command.equals("search")){
						search(string.nextToken());
					} else {
						System.out.println("Invalid command\n");
					}
				} else {
					//the rest of the valid command inputs have a word argument and a type argument
					String word = string.nextToken();		
					String num = string.nextToken();
					int type;								//int version of num								
					
					//check if the type is a valid number
					if (num.equals("1")){ 
						type = 1;
					} else {
						if (num.equals("2")){ 
							type = 2;
						} else {
							if (num.equals("3")){ 
								type = 3;
							} else { 
								System.out.println("Invalid command, type must be 1, 2 or 3.\n");
								continue;
							}
						}
					}
					
					if (number == 3 ){
						//command inputs which need 3 tokens (remove, next and prev)
						if(command.equals("remove")){
							remove(word,type);
						} else {
							if (command.equals("next")){
								next(word, type);
							} else {
								if (command.equals("prev")){
									prev(word, type);
								}else { 
									System.out.println("Invalid command\n");
								}
							}
						}
					} else {
						//the rest of the valid command inputs need a data argument
						String data = string.nextToken();
						if ( (number == 4) && (command.equals("insert"))){
							//only 1 type of command input is accepted with 4 tokens 
							insert(word, type, data);
						} else {
							//command inputs with more than 4 tokens are invalid
							System.out.println("Invalid command\n");
						}
					}
				}
			}
		}
	}
	
	//displays the string/plays the audio/displays the image for all records 
	//whose key word is word
	private static void search(String word){
		boolean found = false;
		Record record = dict.find(new Key(word,1));
		if (record != null){
			//text string data exists for word 
			found = true;
			System.out.println(record.getData() + "\n");
		}
		record = dict.find(new Key(word,3));
		if (record != null){
			//image data exists for word
			found = true;
			PictureViewer p = new PictureViewer();
			try{
				p.show(record.getData());
			} catch (MultimediaException e){
				System.out.print(e.getMessage() + "\n");
			}
		}
		record = dict.find(new Key(word,2));
		if (record != null){
			//audio data exists for word
			found = true;
			SoundPlayer s = new SoundPlayer();
			try{
				s.play(record.getData());
			} catch (MultimediaException e){
				System.out.print(e.getMessage() + "\n");
			}
		}
		if (!found) {
			//no records exist with the key
			System.out.print("No key can be found with \"" + word + "\"\n");
		}
	}
	
	//removes a record if its key exists
	private static void remove(String word, int type){
		try{
			dict.remove(new Key(word,type));
		} catch (DictionaryException e){
			System.out.print(e.getMessage() + "\n");
		}
	}
	
	//inserts a new record if its key doesn't already exist 
	private static void insert(String word, int type, String data){
		try{
			dict.insert(new Record(new Key(word,type),data));
		} catch (DictionaryException e){
			System.out.print(e.getMessage() + "\n");
		}
	}
	
	//prints the successor if the parameter's key exists
	private static void next(String word, int type){
		if (dict.find(new Key(word,type)) == null){
			//key does not exist so successor can't be found
			System.out.print("Can't find successor, (" + word + "," + type + ") not in dictionary. \n" );
		} else {
			Record record = dict.successor(new Key(word,type));
			if (record == null){
				System.out.println("No successor, (" + word + "," + type + ") is the largest in the dictionary.\n");
			} else {
				System.out.println("(" + record.getKey().getWord() + "," + record.getKey().getType() + ")\n");
			}
		}
	}
	
	//prints the previous key 
	private static void prev(String word, int type){
		if (dict.find(new Key(word,type)) == null){
			//key does not exist so predecessor can't be found
			System.out.print("Can't find predecessor, (" + word + "," + type + ") not in dictionary.\n" );
		} else {
			Record record = dict.predecessor(new Key(word,type));
			if (record == null){
				System.out.println("No predecessor, (" + word + "," + type + ") is the smallest in the dictionary.\n");
			} else {
				System.out.println("(" + record.getKey().getWord() + "," + record.getKey().getType() + ")\n");
			}
		}
	}
	
	//prints the smallest key
	private static void first(){
		Record record = dict.smallest();
		if (record ==null){
			System.out.print("Empty dictionary: no smallest \n");
		} else {
			System.out.println("(" + record.getKey().getWord() + "," + record.getKey().getType() + ")\n");
		}
	}
	
	//prints the greatest key
	private static void last(){
		Record record = dict.largest();
		if (record ==null){
			System.out.print("Empty dictionary: no largest \n");
		} else {
			System.out.println("(" + record.getKey().getWord() + "," + record.getKey().getType() + ")\n");
		}
	}

}
