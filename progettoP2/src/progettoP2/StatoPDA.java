package progettoP2;

import java.util.Vector;

public class StatoPDA extends Stato{
	private Vector<TransizionePDA> trans;
	public StatoPDA(){
		super(null, false);
	}
	
	public StatoPDA(final String nome, final Boolean finale){
		super(nome,finale);
	}
	
	public TransizionePDA getTrans(StatoPDA stato, final char input ,final char head,final String newHead){
		 int j = 0;
	     while(j<trans.size() && (trans.elementAt(j).getDest() != stato || trans.elementAt(j).getInput() != input ||
	    		 trans.elementAt(j).getHead() != head || trans.elementAt(j).getNewHead().charAt(0) != newHead.charAt(0) ||
                 trans.elementAt(j).getNewHead().charAt(1) != newHead.charAt(1))){
	         j++;
	     }
	     if(j == trans.size()){
	        return null;
	     }
	     else{
	        return trans.get(j);
	     }
	}
	
	public void add(StatoPDA stato, final char input, final char head, final String newHead){

	    if(newHead.length() <= 1 || (newHead.length() == 2 && head != '\u0000' && newHead.charAt(0) != '\u0000')) //accetto: s/s, s/e, e/s, e/e, s/ss
	        if(getTrans(stato,input,head,newHead) == null)
	        {
	            trans.addElement(new TransizionePDA(stato,input,head,newHead));
	        }
	}
	
	public void remove(StatoPDA st,final char c1, final char c2, final String s){
		
	}
	
	public int nTrans(){
		 return trans.size();
	}
	
	@Override
	public Transizione operatorBarraBarra(int n){
		 return trans.elementAt(n);
	}
}
