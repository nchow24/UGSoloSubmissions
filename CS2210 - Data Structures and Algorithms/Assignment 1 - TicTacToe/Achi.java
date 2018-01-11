//nchow24	CS2210A		Oct 19, 2016
// Class Achi creates gameboard to play Achi, Dictionary for configurations 
// and determines score of the game

import java.util.Arrays;


public class Achi {
	private int length;										//dimension of gameBoard
	private char[][] gameBoard;										
	
	//initialization of gameBoard
	public Achi(int board_size, int max_levels){
		length = board_size; 			
		gameBoard = new char[length][length];
		
		//each array entry initialized to " "
		for(int row=0; row < length; row++){				
			for (int col = 0; col < length; col++){
				gameBoard[row][col] = ' ';
			}
		}	
	}
	
	//creates empty dictionary
	public Dictionary createDictionary(){
		Dictionary dict = new Dictionary(9887);
		return dict;
	}
	
	//checks if dictionary already stores gameBoard configuration
	public int repeatedConfig(Dictionary configurations){
		return configurations.find(this.gameBoardToString());			
	}
	
	//inserts gameBoard configuration and score in dictionary
	public void insertConfig(Dictionary configurations, int score){
		String config = this.gameBoardToString();
		ConfigData pair = new ConfigData(config, score);
		try{
			configurations.insert(pair);
		} catch (DictionaryException e){
			System.out.print(e.getMessage() + " - " + config + "\n");
		}
	}
	
	//changes entry of a tile
	public void storePlay(int row, int col, char symbol){
		gameBoard[row][col] = symbol;
	}
	
	//checks if tile is empty
	public boolean tileIsEmpty(int row, int col){
		if (gameBoard[row][col] == ' '){
			return true;
		} else {
			return false;
		}
	}
	
	//checks if tile is marked by computer player
	public boolean tileIsComputer(int row, int col){
		if (gameBoard[row][col] == 'O'){
			return true;
		} else  {
			return false;
		}
	}
	
	//checks if a tile is marked by human player
	public boolean tileIsHuman(int row, int col){
		if (gameBoard[row][col] == 'X'){
			return true;
		} else {
			return false;
		}
	}
	
	//checks if a certain player won
	public boolean wins(char symbol){
		if (symbol == 'X'){
			return this.humanWins();
		} else {
			return this.computerWins();
		}
	}
	
	//Check if gameBoard is at a draw
	//conditions for a draw: 
	//    - human or computer can't have won
	//    - there has to be only 1 empty tile
	//    - next turn can't make any more moves (ie tiles adjacent to empty tile are not marked with symbol
	public boolean isDraw(char symbol){
		boolean draw = false;
		//not a draw if any player has won
		if (this.computerWins()==false && this.humanWins() == false){
			//check number of empty tiles in gameBoard
			int empty = 0;
			for(int row=0; row < length; row++){				
				for (int col = 0; col < length; col++){
					if (this.tileIsEmpty(row, col)){
						empty++;
					}
				}
			}
			//not a draw if there are more than 1 empty tiles
			if (empty==1){
				//find the empty tile's row and column
				int emptyR = 0;												//initialize row of the empty tile
				int emptyC = 0;												//initialize column of the empty tile
				for(int row=0; row < length; row++){
					for (int col = 0; col < length; col++){
						if (this.tileIsEmpty(row, col)){	
							emptyR = row;									//actual row of empty tile
							emptyC = col;									//actual column of empty tile
						}	
					}
				}
				//check if symbol can move on next turn by checking if adjacent tiles exist and are marked with symbol
				boolean canMove = false;
				if (symbol=='X'){
					//check top left tile
					if (0<=emptyR-1 && emptyR-1<length && 0<=emptyC-1 && emptyC-1<length && this.tileIsHuman(emptyR-1,emptyC-1))canMove=true;
					//check top tile
					if (0<=emptyR-1 && emptyR-1<length && 0<=emptyC && emptyC<length && this.tileIsHuman(emptyR-1,emptyC))canMove=true;
					//check top right diagonal tile
					if (0<=emptyR-1 && emptyR-1<length && 0<=emptyC+1 && emptyC+1<length && this.tileIsHuman(emptyR-1,emptyC+1))canMove=true;
					//check left tile
					if (0<=emptyR && emptyR<length && 0<=emptyC-1 && emptyC-1<length && this.tileIsHuman(emptyR,emptyC-1))canMove=true;
					//check right tile
					if (0<=emptyR && emptyR<length && 0<=emptyC+1 && emptyC+1<length && this.tileIsHuman(emptyR,emptyC+1))canMove=true;
					//check bottom left tile
					if (0<=emptyR+1 && emptyR+1<length && 0<=emptyC-1 && emptyC-1<length && this.tileIsHuman(emptyR+1,emptyC-1))canMove=true;
					//check bottom tile
					if (0<=emptyR+1 && emptyR+1<length && 0<=emptyC && emptyC<length && this.tileIsHuman(emptyR+1,emptyC))canMove=true;
					//check bottom right tile
					if (0<=emptyR+1 && emptyR+1<length && 0<=emptyC+1 && emptyC+1<length && this.tileIsHuman(emptyR+1,emptyC+1))canMove=true;
				} else {
					// top left tile
					if (0<=emptyR-1 && emptyR-1<length && 0<=emptyC-1 && emptyC-1<length && this.tileIsComputer(emptyR-1,emptyC-1))canMove=true;
					//check top tile
					if (0<=emptyR-1 && emptyR-1<length && 0<=emptyC && emptyC<length && this.tileIsComputer(emptyR-1,emptyC))canMove=true;
					//check top right tile
					if (0<=emptyR-1 && emptyR-1<length && 0<=emptyC+1 && emptyC+1<length && this.tileIsComputer(emptyR-1,emptyC+1))canMove=true;
					//check left tile
					if (0<=emptyR && emptyR<length && 0<=emptyC-1 && emptyC-1<length && this.tileIsComputer(emptyR,emptyC-1))canMove=true;
					//check right tile
					if (0<=emptyR && emptyR<length && 0<=emptyC+1 && emptyC+1<length && this.tileIsComputer(emptyR,emptyC+1))canMove=true;
					//check bottom left tile
					if (0<=emptyR+1 && emptyR+1<length && 0<=emptyC-1 && emptyC-1<length && this.tileIsComputer(emptyR+1,emptyC-1))canMove=true;
					//check bottom tile
					if (0<=emptyR+1 && emptyR+1<length && 0<=emptyC && emptyC<length && this.tileIsComputer(emptyR+1,emptyC))canMove=true;
					//check bottom right tile
					if (0<=emptyR+1 && emptyR+1<length && 0<=emptyC+1 && emptyC+1<length && this.tileIsComputer(emptyR+1,emptyC+1))canMove=true;
				}
				if (canMove==false) draw=true;
			}
		}
		return draw;
	}
	
	public int evalBoard(char symbol){
		//human wins
		if (this.wins('X')){															
			return 0;	
		//computer wins
		} else if (this.wins('O')){															
			return 3;					
		//draw
		} else if (this.isDraw(symbol)) {												
			return 2;
		//game undecided
		} else {													
			return 1;
		}
	}
	
	
	//checks if computer won
	private boolean computerWins(){
		boolean win = false;
		int symbolCount = 0;										//number of O's in a row/column/diagonal
		
		//checks for a computer win in a row
		for(int row=0; row < length; row++){				
			for (int col = 0; col < length; col++){
				if (this.tileIsComputer(row, col)){
					symbolCount++;
				}
			}
			//checks if a full row has O's
			if (symbolCount == length){													
				win = true;
				return win;
			} else {
				symbolCount = 0;
			}
		}
		//checks for a computer win in a column
		for(int col=0; col < length; col++){				
			for (int row = 0; row < length; row++){
				if (this.tileIsComputer(row, col)){
					symbolCount++;
				}
			}
			//checks if a full column has O's
			if (symbolCount == length){													
				win = true;
				return win;
			} else {
				symbolCount = 0;
			}
		}
		//checks for a computer win in a diagonal
		//checks the diagonal from top left to bottom right 
		for (int row=0; row < length; row++){											
			if (this.tileIsComputer(row, row)){
				symbolCount++;
			}
		}
		//checks for a full diagonal of O's
		if (symbolCount==length){														
			win = true;
			return win;
		} else {
			symbolCount = 0;
		}
		//checks the diagonal from bottom left to top right
		int row = length-1;																
		for (int col = 0; col < length; col++){
			if (this.tileIsComputer(row, col)){
				symbolCount++;
			}
			row--;
		}
		//checks for a full diagonal of O's
		if (symbolCount==length){														
			win = true;
			return win;
		}
		return win;											
	}
	
	//checks if human won
	private boolean humanWins(){
		boolean win = false;
		int symbolCount = 0;										//number of X's in a row/column/diagonal
		
		//checks for a human win in a row
		for(int row=0; row < length; row++){				
			for (int col = 0; col < length; col++){
				if (this.tileIsHuman(row, col)){
					symbolCount++;
				}
			}
			//checks if a full row has X's
			if (symbolCount == length){													
				win = true;
				return win;
			} else {
				symbolCount = 0;
			}
		}
		//checks for a human win in a column
		for(int col=0; col < length; col++){				
			for (int row = 0; row < length; row++){
				if (this.tileIsHuman(row, col)){
					symbolCount++;
				}
			}
			//checks if a full column has X's
			if (symbolCount == length){													
				win = true;
				return win;
			} else {
				symbolCount = 0;
			}
		}
		//checks for a human win in a diagonal
		//checks the diagonal from top left to bottom right 
		for (int row=0; row < length; row++){											
			if (this.tileIsHuman(row, row)){
				symbolCount++;
			}
		}
		//checks if the full diagonal has X's
		if (symbolCount==length){														
			win = true;
			return win;
		} else {
			symbolCount = 0;
		}
		//checks the diagonal from bottom left to top right
		int row = length-1;																
		for (int col = 0; col < length; col++){
			if (this.tileIsHuman(row, col)){
				symbolCount++;
			}
			row--;
		}
		//checks if the full diagonal has X's
		if (symbolCount==length){														
			win = true;
			return win;
		}
		return win;					
	}
	
	//creates a string representation of gameBoard
	private String gameBoardToString(){
		String string = "";
		for(int row=0; row < length; row++){				
			for (int col = 0; col < length; col++){
				string = string + Character.toString(gameBoard[row][col]);
			}
		}
		return string;
	}

}
