

public interface AbstractAutoma {	
	public Boolean start(String s);
	public void addState(String s);
	public void removeState(String s);
	public void setStartingState(String s);
	public void renameState(final String oldName,final String newName);
	public Stato getStartingState();
}
