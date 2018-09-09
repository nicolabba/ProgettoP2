
import java.util.ArrayList;

public class NFA extends FA{	
	private ArrayList<ArrayList<String>> chiusure;
	
	private void supportChiusure(ArrayList<String> curr, Stato s){
		Boolean presente;
	    for (int i = 0; i< s.nTrans(); i++)
	    {
	        if(s.operatorBarraBarra(i).getInput() == '\u0000')
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
	    for (int i = 0; i < stati.size() ; i++)
	    {
	        curr = new ArrayList<String>();
	        curr.add(stati.get(i).getNome());
	        supportChiusure(curr,stati.get(i));
	        chiusure.add(curr);
	    }
	}
	private Boolean check(StatoFA s, final String input){
		ArrayList<StatoFA> chiusuraCorr = new ArrayList<StatoFA>();
	    for(int i = 0; i < chiusure.size(); i++)
	    {
	        if(chiusure.get(i).get(0) == s.getNome())
	        {
	            for(int j = 0; j <  chiusure.get(i).size(); j++)
	            {
	                chiusuraCorr.add(getStato(chiusure.get(i).get(j)));
	            }
	        }
	    }
	    if(input.length() == 0){
	        
	    	for(int i = 0; i < chiusuraCorr.size(); i++){
	            
	    		if(chiusuraCorr.get(i).isFinale())
	                return true;
	        }
	    }
	    else{
	       
	    	for(int i = 0; i < chiusuraCorr.size(); i++){
	           
	        	for(int t = 0; t < chiusuraCorr.get(i).nTrans(); t++){
	                
	            	if(chiusuraCorr.get(i).operatorBarraBarra(t).getInput() == input.charAt(0)){
	                    
	            		if(check((StatoFA) chiusuraCorr.get(i).operatorBarraBarra(t).getDest(),
	                    		input.substring(1))){
	                    	return true;
	                    }                        
	                }
	            }
	        }
	    }
	    return false;
	}
	
	protected NFA(StatoFA s) {
		super(s);
	}
	
	public NFA() {
		chiusure = new ArrayList<ArrayList<String>>();
	}
	
	@Override
	public Boolean start(String input){
		updateChiusure();
	    if(partenza != null)
	        return check((StatoFA)(partenza), input);
	    else
	        return false;
	}

}
