package progettoP2;

public class LocalTest {

	public static void main(String[] args) {
		NPDA n  = new NPDA();
		n.setEpsilon('e');
		n.addState("s");
		n.addState("p");
		n.addState("q");
		n.addState("r");
		
		n.setStartingState("s");
		n.getStato("r").setFinale(true);
		
		n.getStato("s").add(n.getStato("p"),
				'e',  
				'e', 
				"Z");
		
		n.getStato("p").add(n.getStato("p"),
				'0',  
				'Z', 
				"AZ");
		n.getStato("p").add(n.getStato("p"),
				'0',  
				'A', 
				"AA");
		n.getStato("p").add(n.getStato("q"),
				'e',
				'e',
				"e");	
		
		n.getStato("q").add(n.getStato("q"),
				'1',
				'A',
				"e");		
		n.getStato("q").add(n.getStato("r"),
				'e',
				'Z',
				"Z");		
		
		if(n.start("0011"))
			System.out.println("OK");
		else
			System.out.println("KO");
	}
}
