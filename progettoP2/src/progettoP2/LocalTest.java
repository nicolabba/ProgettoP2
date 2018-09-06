package progettoP2;

public class LocalTest {

	public static void main(String[] args) {
		PDA n  = new PDA();
		
		n.setEpsilon('e');
		
		n.addState("s");
		n.addState("p");
		n.addState("q");
		n.addState("r");
		
		n.setStartingState("s");
		
		n.getStato("r").setFinale(true);
		
		n.addTransizione("s","p",'e','e',"Z");
		n.addTransizione("p","p",'0','Z',"AZ");
		n.addTransizione("p","p",'0','A',"AA");
		n.addTransizione("p","q",'e','e',"e");
		n.addTransizione("q","q",'1','A',"e");	
		n.addTransizione("q","r",'e','Z',"Z");
		n.addTransizione("r","r",'e','Z',"e");	
		
		if(n.start("00111"))
			System.out.println("OK");
		else
			System.out.println("KO");
	}
}
