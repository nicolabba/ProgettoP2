package progettoP2;

import java.util.ArrayList;
import java.util.Iterator;

public class PDA implements AbstractAutoma {
	protected ArrayList<StatoPDA> stati;
    protected StatoPDA partenza; 
	protected PDA(){
		
	}
	protected PDA(StatoPDA s){
    	partenza = s;
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
	    for(Iterator<StatoPDA> i = stati.iterator();  i.hasNext() && !eliminato;)
	    {
	        if(i.next().getNome() == s)
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
		Iterator<StatoPDA> i = stati.iterator();		
	    while(i.hasNext() && i.next().getNome() != s){}
	    return i.next(); 
	}
	public StatoPDA operatorBarraBarra(final String s){
		return getStato(s);
	}
	
	@Override
	public void renameState(final String oldName, final String newName) {
		StatoPDA s = null;
	    Boolean trovato = false;
	    for(StatoPDA i : stati)
	    {
	        if(i.getNome() == newName){
	            trovato = true;
	            break;
	        }
	        else if(i.getNome() == oldName){
	            s = i;
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
