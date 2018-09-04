package progettoP2;

import java.util.ArrayList;
import java.util.Iterator;

public abstract class PDA implements AbstractAutoma {
	protected ArrayList<StatoPDA> stati;
    protected StatoPDA partenza; 
	protected PDA(){
		stati = new ArrayList<StatoPDA>();
	}
	protected PDA(StatoPDA s){
    	partenza = s;
    	stati = new ArrayList<StatoPDA>();
    }
	
	@Override
	public Boolean start(String s) {		
		return null;
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
	        if(stati.get(i).getNome() == s)
	        {
	            if(partenza.getNome() == s)
	                partenza = null;
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
	
	@Override
	public Stato getStartingState() {
		return partenza;
		
	}

}
