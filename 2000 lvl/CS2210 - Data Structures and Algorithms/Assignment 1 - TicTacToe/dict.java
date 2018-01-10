
public class dict {
	  /*
	  ** Test program for the Dictionary class.
	  ** This program WILL NOT COMPILE if your insert or remove
	  ** methods do not throw a DictionaryException.
	  */

	  public static void main(String[] args) {
	    Dictionary dict = new Dictionary(10);
	    ConfigData pair;
	    boolean[] test = new boolean[11];
	    int i,j;

	    if (args.length == 0) 
		for (i = 0; i < 11; ++i) test[i] = true;  // Perform all tests
	    else {

		if (args[0].equals("?")) {
		    System.out.println("Usage: java TestDict, or java TestDict n1 n2 n3 ... ");
		    System.out.println("where each ni has value 1 - 10; with the second invocation");
		    System.out.println("only the specified tests will be run");
		    System.exit(0);
	        }

		for (i = 0; i < 11; ++i) test[i] = false;
		for (i = 0; i < args.length; ++i) {
		    j = Integer.parseInt(args[i]);
		    if (j >= 1 && j <= 10) test[j] = true; // Perform only specified tests
		}
	    }


	    int collisions = 0;
	    String s;


	    // Test 7: insert 10000 different values into the Dictionary
	    try {
		for (i = 0; i < 10; ++i) {
		    s = (new Integer(i)).toString();
		    for (j = 0; j < 5; ++j) s += s;
		    collisions += dict.insert(new ConfigData(s,i));
		    System.out.print(s + "  " + dict.find(s) + "\n");
		}
		System.out.println("   Test 7 succeeded");
	    } 
	    catch (DictionaryException e) {
		System.out.println("***Test 7 failed");
	    }

	   
	    
	    
	    // Test 8: check that all inserted values are in the Dictionary
	   
		for (i = 0; i < 10; ++i) {
		    s = (new Integer(i)).toString();
		    for (j = 0; j < 5; ++j) s += s;
		    System.out.print(s + "  " + dict.find(s) + "\n");
		
	    }
		
	  }	

}
