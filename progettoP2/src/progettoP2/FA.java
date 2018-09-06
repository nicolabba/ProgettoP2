package progettoP2;

import java.util.ArrayList;
import java.util.Iterator;

public abstract class FA implements AbstractAutoma{	
	protected ArrayList<StatoFA> stati;
	protected StatoFA partenza; 
	
	protected FA(){
		stati = new ArrayList<StatoFA>();
	}
	protected FA(StatoFA s ){
		stati = new ArrayList<StatoFA>();
		stati.add(s);
		partenza = s;
	}
	
	public StatoFA getStato(final String s){
		int i = 0;
	    while(i < stati.size() && stati.get(i).getNome() != s){ 
	    	i++; 
	    }
	    if(i < stati.size()){
	    	return stati.get(i);	    	
	    }
	    else{
	    	return null;
	    }
	}
	
	public StatoFA operatorBarraBarra(final String s){
		return getStato(s);
	}
	
	@Override
	public Boolean start(String s) {
		return false;
	}
	
	@Override
	public void addState(String s) {
		 if(getStato(s) == null)
	            stati.add(new StatoFA(s));
	}
	
	@Override
	public void removeState(String s) {
	
	    for(StatoFA temp : stati)
	    {
	        for(int j = 0; j < temp.nTrans(); j++)
	        {
	            Transizione t = temp.operatorBarraBarra(j);
	            if(t.getDest().getNome() == s){
	                temp.remove(((StatoFA)t.getDest()), t.getInput());
	            }
	        }
	    }	    
	    
	    for(StatoFA i : stati)
	    {
	        if(i.getNome() == s)
	        {
	            if(partenza.getNome() == s)
	                partenza = null;
	            stati.remove(i);
            	break;
	        }
	    }
	}
	
	@Override
	public void setStartingState(String s) {
		partenza = getStato(s);
		
	}
	
	@Override
	public void renameState(String oldName, String newName) {
		StatoFA s = null;
	    Boolean trovato = false;
	    for(int i = 0; i < stati.size() && !trovato; i++)
	    {
	    	StatoFA temp = stati.get(i);	    
	    	if(temp.getNome() == newName)
	            trovato = true;
	        else if(temp.getNome() == oldName)
	            s = temp;
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
