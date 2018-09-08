public class TransizionePDA extends Transizione{
	private char head;
	private String newHead;
	
	public TransizionePDA(Stato st, char i, char h, String nh){
		super(st, i);
		head = h;
		
		if(nh.length() <= 2){
			newHead = nh;
		}
	}
	
	char getHead(){
		return head;
	}
	
	String getNewHead(){
		return newHead;
	}
}
