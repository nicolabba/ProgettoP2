package progettoP2;

import java.util.Vector;

public class Stringa {	
	
	private static final int A = 27983;/* Numero primo per la generazione di hash */
	private static final int B = 47701;/* Numero primo per la generazione di hash */
	private static final int C = 68111;/* Numero primo per la generazione di hash */
	private char[] a;
	private int dim;

	private char[] copy(){		
		if(dim==0){
			return null;
		}	    		
		else{
		    char[] ret = new char[dim];		    
		    for(int i=0; i<dim; ++i){
		        ret[i]=a[i];
		    }		    
		    return ret;
	    }
	}
	
	static Boolean check(int to, char[] a, char[] b, int dim){
		Boolean ret = true;
	    for(int i = 0; ret && i<dim; i++){
	        if(a[to]!=b[i])
	            ret = false;
	    }
	    return ret;
	}
	
	public int size(){
		return dim;
	}
	
	public Stringa(){
		this.a = null;
		this.dim = 0;
	}
	public Stringa(Stringa s){
		this.a = s.copy();
		this.dim = s.dim;
	}
		
	public Stringa(char[] c, int n){		
		if(n > 0){
	        dim = n;
	        a = new char[dim];
	        for(int i = 0; i<dim; i++){
	            a[i] = c[i];
	        }
	    }
	}
		
	public Stringa operatorUguale (final Stringa s){
		 if(this != s){	       
	        a = s.copy();
	        dim = s.dim;
		 }
	     return this;
	}
	
	public Stringa operatorPiu (final Stringa s){
		 Stringa x = new Stringa();
		 x.a = new char[dim + s.dim];
		 x.dim = dim + s.dim;
         int i=0;
		 for(; i<dim; ++i) x.a[i]=a[i];
		 for( ; i<x.dim; ++i) x.a[i] = s.a[i-dim];
		 return x;
	}
	
	public Boolean operatorUgualeUguale (final Stringa s){
		if(dim != s.dim) return false;
	    for(int i=0; i<dim; ++i)
	      if(a[i] != s.a[i]) return false;
	    return true;
	}
	
	public char operatorDoppiaBarra (int i){
		return a[i];
	}
	
	public void append(final Stringa s){
		 Stringa x = this.operatorPiu(s);
		 this.operatorUguale(x);		 
	}
	
	public void remove(final Stringa s){
		 int id = search(s);
	     if(id != -1) {
	        remove(id,s.dim);
	     }
	}
	
	public void remove(int id,int q){
	 	dim-=q;
	    char[] c = new char[dim];
	    for(int i = 0; i<dim; i++)
	    {
	        if(i<id)
	            c[i] = a[i];
	        else
	            c[i] = a[i+q];
	    }	    
	    a = c;
	}
	
	public int search(final Stringa s){
		 Boolean found = false;
	     int ret = -1;
	     for(int i = 0; !found && i<=dim-s.dim; i++)
	     {
	        if(a[i] == s.a[0] && check(i, a, s.a, s.dim))
	        {
	            found = true;
	            ret = i;
	        }
	    }
	    return ret;
	} // ritorna id della prima apparenza o -1 se non viene trovato niente
	
	public int hash() {
		 int ret = A;
	     for (int i = 0; i<dim; i++)
	        ret = (ret * B) ^ (a[i] * C);
	     return ret;
	}
	public Vector<Stringa> split(final Stringa s){
		 	Vector<Stringa> ret = new Vector<Stringa>();
		    Stringa temp = new Stringa(copy(),dim), al;
		    int index = temp.search(s);
		    while(index != -1)
		    {
		        al = temp.subString(0,index);
		        ret.addElement(al);
		        temp.remove(0,index+s.size());
		        index = temp.search(s);
		    }
		    ret.addElement(temp);
		    return ret;
	}
	public Stringa subString(int start,int len){
		Stringa x = new Stringa();
		char[] _a = new char[len];
		for(int i = 0; i < len; i++){
			_a[i] = this.a[len + i];
		}
		x.a = _a;
		x.dim = len;
		return x;
	}
}
