package progettoP2;

public abstract class Stato {
	
	private String nome;
	private Boolean finale;
	
	public Stato(){
		
	}
	public Stato(String n, Boolean f){
		nome = n;
		finale = f;
	}
	
	public int nTrans(){
		return 0;
	}
	
	public Transizione operatorBarraBarra(int i){
		return null;
	}
	
	public String getNome(){
		return nome;
	}
	
	public void setFinale(Boolean f){
		finale = f;
	}
	
	public Boolean isFinale(){
		return finale;
	}
	
	public void rename(final String newNome)
	{
	     nome = newNome;
	}
}
