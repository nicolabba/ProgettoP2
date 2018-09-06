package progettoP2;

import java.util.Vector;

public class StatoPDA extends Stato{
	private Vector<TransizionePDA> trans;
	public StatoPDA(){
		super(null, false);
		trans = new Vector<TransizionePDA>();
	}
	
	public StatoPDA(final String nome, final Boolean finale){
		super(nome,finale);
		trans = new Vector<TransizionePDA>();
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
        if(getTrans(stato,input,head,newHead) == null)
        {
            trans.addElement(new TransizionePDA(stato,input,head,newHead));
        }
	}
	
	public void remove(StatoPDA stato,final char input, final char head, final String newHead){
		 Boolean eliminato = false;
	    for(int j = 0;  j < trans.size() && !eliminato; j++)
	    {
	        if(trans.get(j).getDest() == stato && 
	        		trans.get(j).getInput() == input 
	        		&& trans.get(j).getHead() == head 
	        		&& trans.get(j).getNewHead() == newHead)
	        {
	            trans.remove(j);
	            eliminato = true;
	        }
	    }
	}
	
	public int nTrans(){
		 return trans.size();
	}
	
	@Override
	public Transizione operatorBarraBarra(int n){
		 return trans.elementAt(n);
	}
}
