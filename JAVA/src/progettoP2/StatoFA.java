

import java.util.Vector;

public class StatoFA extends Stato{
	private Vector<Transizione> trans = new Vector<Transizione>();
    public StatoFA(final String nome, final Boolean finale){
    	super(nome, finale);
    }
    public StatoFA(String s) {
		super(s,false);
	}
    
	public Transizione getTrans(StatoFA stato, final char input){
    	int j = 0;
        while(j<trans.size() && (trans.get(j).getDest() != stato 
        		|| trans.get(j).getInput() != input))
            j++;
        if(j == trans.size())
            return null;
        else
            return trans.get(j);
    }
    public void add(StatoFA stato, final char input){
    	if(getTrans(stato,input) == null)
        {
            trans.addElement(new Transizione(stato,input));
        }
    }
    public void remove(StatoFA stato, final char input){
    	Boolean eliminato = false;
        for(int j = 0;  j < trans.size() && !eliminato; j++)
        {
            if(trans.get(j).getDest() == stato && trans.get(j).getInput() == input)
            {
                trans.remove(j);
                eliminato = true;
            }
        }
    }
    public int nTrans(){
    	return trans.size();
    }
    public Transizione operatorBarraBarra(int i){
    	return trans.get(i);
    }
}
