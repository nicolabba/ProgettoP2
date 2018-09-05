package progettoP2;

import java.util.ArrayList;

public class NPDA extends PDA{
	private ArrayList<ArrayList<String>> chiusure;
	private char epsilon; 
	
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
	        if(stack == "")
	            for(int i = 0; i < chiusuraCorr.size(); i++)
	                if(chiusuraCorr.get(i).isFinale())
	                    return true;
	    }
	    else
	    {
	        for(int i = 0; i < chiusuraCorr.size(); i++)
	        {
	            for(int t = 0; t < chiusuraCorr.get(i).nTrans(); t++)
	            {
	                tempTrans = (TransizionePDA) chiusuraCorr.get(i).operatorBarraBarra(t);
	                
	                if(tempTrans.getInput() == input.charAt(0) 
	                		&& (tempTrans.getHead() == stack.charAt(0)
	                				|| tempTrans.getHead() == epsilon))
	                {
	                    tempStack = stack;
	                    if(tempTrans.getHead() != epsilon)
	                    {
	                        tempStack = tempStack.substring(1);
	                        if(tempTrans.getNewHead().length() != 0)
	                        {
	                            tempStack = tempTrans.getNewHead().charAt(0) + tempStack;
	                            if(tempTrans.getNewHead().length() == 2)
	                                tempStack = tempTrans.getNewHead().charAt(1) + tempStack;
	                        }
	                    }
	                    else if(tempTrans.getNewHead().length() == 1)
	                    {
	                        tempStack = tempTrans.getNewHead().charAt(0) + tempStack;
	                    }
	                    if(check((StatoPDA) tempTrans.getDest(),input.substring(1),tempStack))
	                        return true;
	                }
	            }
	        }
	    }
	    return false;
	}
	
	public NPDA(){
		chiusure = new ArrayList<ArrayList<String>>();
	}
	
	public NPDA(StatoPDA s){
		super(s);
		chiusure = new ArrayList<ArrayList<String>>();
	}
	
	public NPDA(StatoPDA s, char eps){
		super(s);
		chiusure = new ArrayList<ArrayList<String>>();
		epsilon = eps;
	}
	
	public Boolean start(final String input){
		 updateChiusure();
	    if(partenza != null)
	        return check(partenza, input, "e");
	    else
	        return false;
	}

	public char getEpsilon() {
		return epsilon;
	}

	public void setEpsilon(char epsilon) {
		this.epsilon = epsilon;
	}
}