package progettoP2;

import java.util.ArrayList;
import java.util.Iterator;

public class PDA implements AbstractAutoma {
	private ArrayList<StatoPDA> stati;
    private StatoPDA partenza; 
    private ArrayList<ArrayList<String>> chiusure;
    private char epsilon; 
    
	protected PDA(){
		stati = new ArrayList<StatoPDA>();
		chiusure = new ArrayList<ArrayList<String>>();
	}
	protected PDA(StatoPDA s, char e){
    	partenza = s;
    	stati = new ArrayList<StatoPDA>();
    	chiusure = new ArrayList<ArrayList<String>>();
    	epsilon = e;
    }
	
	@Override
	public Boolean start(String s) {		
		updateChiusure();
	    if(partenza != null)
	        return check(partenza, s, "");
	    else
	        return false;
	}
	
	private void updateChiusure(){
		ArrayList<String> curr;
	    chiusure.clear();
	    for (StatoPDA temp : stati)
	    {
	        curr = new ArrayList<String>();
			curr.add(temp.getNome());
	        supportChiusure(curr,temp);
	        chiusure.add(curr);
	    }
	}
	
	private void supportChiusure(ArrayList<String> curr , Stato s ){
	    Boolean presente;
	    for (int i = 0; i<s.nTrans(); i++)
	    {
	        if(s.operatorBarraBarra(i).getInput() == epsilon)
	        {
	            presente = false;
	            for(int j = 0; j < curr.size() && !presente; j++)
	            {
	                if(curr.get(j) == s.operatorBarraBarra(i).getDest().getNome())
	                    presente = true;
	            }
	            if(!presente)
	            {
	                curr.add(s.operatorBarraBarra(i).getDest().getNome());
	                supportChiusure(curr,s.operatorBarraBarra(i).getDest());
	            }
	        }
	    }
	}
	
	private Boolean check(StatoPDA s, final String input, final String stack){
	    String tempStack;
	    TransizionePDA tempTrans;
	    ArrayList<StatoPDA> chiusuraCorr = new ArrayList<StatoPDA>();
	    for(int i = 0; i < chiusure.size(); i++)
	    {
	        if(chiusure.get(i).get(0) == s.getNome())
	        {
	            for(int j = 0; j < chiusure.get(i).size(); j++)
	            {
	                chiusuraCorr.add(getStato(chiusure.get(i).get(j)));
	            }
	        }
	    }
	    if(input.length() == 0)
	    {
	        if(stack.length() == 0)
	            for(int i = 0; i < chiusuraCorr.size(); i++)
	                if(chiusuraCorr.get(i).isFinale())
	                    return true;
	        
	        for(int i = 0; i < chiusuraCorr.size(); i++)
	        {
	            for(int t = 0; t < chiusuraCorr.get(i).nTrans(); t++)
	            {
	                tempTrans = (TransizionePDA) chiusuraCorr.get(i).operatorBarraBarra(t);
	                
	                if(tempTrans.getInput() == epsilon
	                		&& (stack.length() != 0 && (tempTrans.getHead()) == stack.charAt(0)))
	                {
	                    tempStack = stack;
	                    if(tempTrans.getHead() != epsilon)
	                    {
	                        tempStack = tempStack.substring(1);
	                        if(tempTrans.getNewHead().charAt(0) != epsilon)
	                        {
	                            tempStack = tempTrans.getNewHead() + tempStack;
	                        }
	                    }
	                    else 
	                    {	         
	                    	if(tempTrans.getNewHead().charAt(0) != epsilon) 
	                        {
	                    		tempStack = tempTrans.getNewHead().charAt(0) + tempStack;
	                        }
	                    }
	                    if(check((StatoPDA) tempTrans.getDest(),
	                    		tempTrans.getInput()==epsilon?
	                    		input:   
	                    		input.substring(1), tempStack))
	                        return true;
	                }
	            }
	        }
	    }
	    else
	    {
	    	   for(int i = 0; i < chiusuraCorr.size(); i++)
		        { 
		            for(int t = 0; t < chiusuraCorr.get(i).nTrans(); t++)
		            {
		                tempTrans = (TransizionePDA) chiusuraCorr.get(i).operatorBarraBarra(t);
		                
	                if((tempTrans.getInput() == input.charAt(0) &&  stack.length()!= 0 && tempTrans.getHead() == stack.charAt(0)) 
	                		|| tempTrans.getHead() == epsilon)
	                {
	                    tempStack = stack;
	                    if(tempTrans.getHead() != epsilon)
	                    {
	                        tempStack = tempStack.substring(1);
	                        if(tempTrans.getNewHead().charAt(0) != epsilon) // !!!!!
	                        {
	                            tempStack = tempTrans.getNewHead() + tempStack;
	                        }
	                    }
	                    else if(tempTrans.getNewHead().length() == 1)
	                    {
	                        if(tempTrans.getNewHead().charAt(0) != epsilon) // !!!!!
	                        {
	                            tempStack = tempTrans.getNewHead().charAt(0) + tempStack;
	                        }
	                    }
	                    if(check((StatoPDA)(tempTrans.getDest()),
	                    		tempTrans.getInput()==epsilon? input : input.substring(1),tempStack))
	                        return true;
	                }
	            }
	        }
	    }
	    return false;
	}
	
	@Override
	public void addState(String s) {
		if(getStato(s) == null)
            stati.add(new StatoPDA(s, false));
	}

	@Override
	public void removeState(String s) {
		Boolean eliminato = false;
	    for(int i = 0; i<stati.size() && !eliminato; i++)
	    {
	    	for(int j = 0; j<stati.get(i).nTrans(); j++){
	    		 TransizionePDA temp = (TransizionePDA)(stati.get(i).operatorBarraBarra(j));
	             if(temp.getDest().getNome() == s)
	                 stati.get(i).remove((StatoPDA)(temp.getDest()),temp.getInput(),temp.getHead(),temp.getNewHead());
	    	}
	    }
	    for(int i= 0; i<stati.size(); i++){
	    	if(stati.get(i).getNome() == s){
	    		if(partenza.getNome() == s){
	    			partenza = null;
	    		}
	    		stati.remove(i);
	    		eliminato = true;
	    	}
	    }
	}

	@Override
	public void setStartingState(String s) {
		partenza = getStato(s);
	}
	
	public StatoPDA getStato(final String s){	
		for(StatoPDA tmp : stati){
			if(s == tmp.getNome()){
				return tmp;
			}
		}
		return null;		 
	}
	
	public StatoPDA operatorBarraBarra(final String s){
		return getStato(s);
	}
	
	public StatoPDA operatorBarraBarra(final int ind){
		int i = 0;
		for(StatoPDA s : stati){
			if(i == ind){
				return s;
			}
			i++;
		}
		return null;
	}
	
	public int getNStati(){
		return stati.size();
	}
	
	@Override
	public void renameState(final String oldName, final String newName) {
		StatoPDA s = null;
	    Boolean trovato = false;
	    for(int i = 0 ; i < stati.size() && !trovato; i++)
	    {
	        if(stati.get(i).getNome() == newName){
	            trovato = true;
	        }
	        else if(stati.get(i).getNome() == oldName){
	            s = stati.get(i);
	        }
	    }
	    if(!trovato && s != null)
	    {
	        s.rename(newName);
	    }
		
	}
	
	public void addTransizione(final String da,
			final String  a,
			char input,
			char head, 
			String newHead)
	{
	    StatoPDA daStato = getStato(da);
	    StatoPDA aStato = getStato(a);
	    if (daStato != null && aStato != null)
	        daStato.add(aStato,input,head,newHead);
	}
	@Override
	public Stato getStartingState() {
		return partenza;
		
	}
	public char getEpsilon() {
		return epsilon;
	}
	public void setEpsilon(char epsilon) {
		this.epsilon = epsilon;
	}

}
