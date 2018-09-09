package progettoP2;

public class DFA  extends FA{
	private String alfabeto;
	
	private Boolean checkAlfa(StatoFA s){
	    int[] controllo = new int[alfabeto.length()];
	    int pos;
	    for(int i = 0; i < s.nTrans(); i++)
	    {
	        pos = alfabeto.indexOf(s.operatorBarraBarra(i).getInput());
	        if(pos != -1)
	            controllo[pos] ++;
	        else
	            return false;
	    }
	    for (int i = 0; i < alfabeto.length(); i++)
	    {
	        if(controllo[i] != 1)
	            return false;
	    }
	    return true;
	}
	
    private Boolean check(Stato s,final String input){
		if(input.length() != 0)
	    {
	        for(int i = 0; i < s.nTrans(); i++)
	        {
	        	char x = s.operatorBarraBarra(i).getInput();
	        	char y = input.charAt(0);
	            if( x==y  )
	                return this.check(s.operatorBarraBarra(i).getDest(), input.substring(1));
	        }
	        return false;
	    }
		   return s.isFinale();
    }
    
	public DFA(StatoFA s) {
		super(s);
	}
	
	public DFA(final String s, StatoFA t){
		super(t);
		alfabeto = s;		
	}		
	
	public DFA() {
		alfabeto = "";
	}
	public String getAlfabeto(){
		return alfabeto;
	}
	
	public void setAlfabeto(final String a){
		alfabeto = a;
	}
	
	@Override
	public Boolean start(final String input){
		for(StatoFA temp : stati)
	    {
	        if(!checkAlfa(temp))
	            return false;
	    }
	    return check(partenza,input);
	}
}
