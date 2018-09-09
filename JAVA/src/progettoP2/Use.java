
public class Use{

	public static void main(String[] args) {
		
		System.out.println("pda per 0^n + 1^n  con input: 0011:");
		PDA p  = new PDA();
		p.setEpsilon('e');
		p.addState("s");
		p.addState("p");
		p.addState("q");
		p.addState("r");
		p.setStartingState("s");
		p.getStato("r").setFinale(true);
		p.addTransizione("s","p",'e','e',"Z");
		p.addTransizione("p","p",'0','Z',"AZ");
		p.addTransizione("p","p",'0','A',"AA");
		p.addTransizione("p","q",'e','e',"e");
		p.addTransizione("q","q",'1','A',"e");	
		p.addTransizione("q","r",'e','Z',"Z");
		p.addTransizione("r","r",'e','Z',"e");	
		if(p.start("0011"))
			System.out.println("OK");
		else
			System.out.println("KO");
		
		
		
		System.out.println("nfa che accetta stringhe che finiscono con 1 con input: 1001:");
		NFA n = new NFA();
		n.addState("s1");
		n.addState("s2");
		n.setStartingState("s1");
		n.getStato("s2").setFinale(true);
		n.getStato("s1").add(n.getStato("s1"), '0');
		n.getStato("s1").add(n.getStato("s1"), '1');
		n.getStato("s1").add(n.getStato("s2"), '1');
		if(n.start("1001"))
			System.out.println("OK");
		else
			System.out.println("KO");
		
		
		System.out.println("dfa che accetta stringhe con numero pari di 0 con input: 10101010:");
		DFA d = new DFA();
		d.addState("s1");
		d.addState("s2");
		d.setAlfabeto("01");
		d.setStartingState("s1");
		d.getStato("s1").setFinale(true);
		d.getStato("s1").add(d.getStato("s1"), '1');
		d.getStato("s1").add(d.getStato("s2"), '0');
		d.getStato("s2").add(d.getStato("s2"), '1');
		d.getStato("s2").add(d.getStato("s1"), '0');
		if(d.start("10101010"))
			System.out.println("OK");
		else
			System.out.println("KO");
		

		Grafico g = new Grafico();
		g.insert(new Punto(0,0));
		g.insert(new Punto(1,1));
		g.insert(new Punto(-1,-1));
		g.remove(new Punto(0,0));
		g.insert(new Punto(3,0));
		g.insert(new Punto(3,1));
		System.out.println("grafico per punti: ");
		for(Punto temp : g.clone())
			System.out.print("(" + temp.getX() + "," + temp.getY() + "),  ");
		System.out.println("\narea: " + g.getArea());
		System.out.println("max: " + g.getMax().getX() + "," + g.getMax().getY());
		System.out.println("min: " + g.getMin().getX() + "," + g.getMin().getY());
		System.out.println("lunghezza: " + g.getLenght());
		
		System.out.println("esempio per stringa pippo: ");
		Stringa s = new Stringa(new char[]{'p','i','p','p', 'o'}, 5);
		Stringa s2 = new Stringa(new char[]{'p','l','u','t', 'o'}, 5);
		System.out.println("hash di pippo: " + s.hash());
		s.append(s2);
		System.out.println("pippo+pluto: " + s.toString()) ;
		System.out.println("pippopluto con  split su pp: ") ;
		for(Stringa temp : s.split(new Stringa(new String("pp").toCharArray(),2))){
			System.out.print(temp.toString() + ",  ") ;
		}
		System.out.println("\nFINE TEST......");
		
	}
}
