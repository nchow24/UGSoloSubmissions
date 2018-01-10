//nchow24	CS2210A		Oct 19, 2016
//Class ConfigData containing attributes:
//   - configuration 
//   - score

public class ConfigData {
	private String configKey; 				// configuration attribute
	private int scoreRecord;				// score attribute
	
	public ConfigData(String config, int score){
		configKey = config;
		scoreRecord = score;
	}
	
	//gets configuration
	public String getConfig(){
		return configKey;
	}
	
	//gets score
	public int getScore(){
		return scoreRecord;
	}

}
