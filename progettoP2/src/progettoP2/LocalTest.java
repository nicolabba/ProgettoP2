package progettoP2;

public class LocalTest {

	public static void main(String[] args) {
// 		dfa che riconosce tutte le stringhe con numero di '0' pari. VA
//		DFA d = new DFA();
//		d.addState("s1");
//		d.addState("s2");
//		d.addState("s3");
//		
//		d.setAlfabeto("01");
//		d.setStartingState("s1");
//		d.getStato("s1").setFinale(true);		
//
//		d.getStato("s1")
//			.add(d.getStato("s1"), '0');
//		d.getStato("s1")
//			.add(d.getStato("s2"), '1');
//		
//		d.getStato("s2")
//			.add(d.getStato("s1"), '1');
//		d.getStato("s2")
//			.add(d.getStato("s3"), '0');
//		
//		d.getStato("s3")
//			.add(d.getStato("s3"), '1');
//		d.getStato("s3")
//			.add(d.getStato("s2"), '0');
//	
//		Boolean res = d.start("10011111");
//		if(res){
//			System.out.println("OK.");
//		}
//		else{
//			System.out.println("KO.");
//		}

//		nfa che riconosce le stringhe che finiscono con 1. NON VA
		NFA n = new NFA();
		
		n.addState("s1");
		n.addState("s2");
		
		n.setStartingState("s1");
		n.getStato("s2").setFinale(true);
		
		n.getStato("s1").add(n.getStato("s1"), '1');
		n.getStato("s1").add(n.getStato("s1"), '0');
		
		n.getStato("s1").add(n.getStato("s2"), '1');
		
		Boolean res2 = n.start("001");
		
		if(res2){
			System.out.println("OK.");
		}
		else {
			System.out.println("KO.");
		}
		
//		pda per 0^n1^n.
//		PDA p = new PDA();
//		p.addState("s1");
//		p.addState("s2");
//		p.addState("s3");
//		p.setStartingState("s1");
//		p.getStato("s3").setFinale(true);
//		p.getStato("s1").add(
//				p.getStato("s1"),
//				'0',
//				'\000', 
//				"az");
		
		
	}


}
