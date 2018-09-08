public class Transizione {
	
	private Stato dest;
	private char input;
	
	public Transizione(Stato s, char i){
		dest = s;
		input = i;
	}
	
	public Stato getDest(){
		return dest;
	}
	
	public char getInput(){
		return input;
	}
}
