
import java.util.ArrayList;

public class Grafico {
	private ArrayList<Punto> idp;
	
	private static double getPartialArea(final Punto p1, final Punto p2){
		    double partArea = 0;
		    if(p1.getY() == p2.getY())
		        partArea += getAreaRet(p1,p2);
		    else
		    {
		        Boolean p1Closer;
		        if(p1.getY() < 0 || p2.getY() < 0)
		            p1Closer = p1.getY() > p2.getY();
		        else
		            p1Closer = p1.getY() < p2.getY();

		        if (p1Closer)
		            partArea += getAreaRet(p1,new Punto(p2.getX(), p1.getY()));
		        else
		            partArea += getAreaRet(new Punto(p1.getX(),p2.getY()),p2);
		        partArea += getAreaTri(p1,p2);
		    }
		    return partArea;
	}
    
	private static double getAreaTri(final Punto p1, final Punto p2){
		 Punto p3 = p1.getY()<p2.getY()? new Punto(p1.getX(),p2.getY()) : new Punto(p2.getX(),p1.getY());
		 return (p3.getDistance(p1) * p3.getDistance(p2))/2;
    	}
    
	private static double getAreaRet(final Punto p1, final Punto p2){
		if(p1.getY() == p2.getY())
	        return Math.abs(p2.getX() - p1.getX()) * Math.abs(p2.getY());
	    return -1;
    }

    public Grafico(){
    	idp = new ArrayList<Punto>();
    }
    
    public Grafico(ArrayList<Punto> x){
    	idp = x;
    }
    public Grafico(final Grafico g){
    	idp = g.idp;
    }    
    public Grafico operatorUguale(final Grafico g){
    	idp.clear();
    	for(Punto temp : g.idp){
    		idp.add(temp);
    	}
    	return this;
    }
    
    public ArrayList<Punto> clone(){
    	ArrayList<Punto> tmp = new ArrayList<Punto>();
    	for(Punto p : idp){
    		tmp.add(p);
    	}
    	return tmp;
    }
    
    public void remove(final Punto p){
    	int index = search(p); 
    	if(index != -1){
    		idp.remove(index);
    	}
    }
    
    public int search(final Punto p){
    	int i = 0;
    	for(Punto tmp : idp){
    		if(p.operatorUgualeUguale(tmp))
    			return i;
    		else
    			i++;
    	}
    	return -1;
    }
    
    public Boolean insert(final Punto p){
    	int index = search(p);
    	if(index == -1){
    		int i;
    		for(i = 0; i < idp.size() 
    				&& p.getX() > idp.get(i).getX(); i++);
    		idp.add(i, p);
    		return true;
    	}
    	else
    		return false;
    }
    
    public double[] getXvalues(){
    	double[] tmp = new double[idp.size()];
    	int i = 0;
    	for(Punto p : idp){
    		tmp[i] = p.getX();
    		i++;
    	}
    	return tmp;
    }
        
    public double[] getYvalues(){
    	double[] tmp = new double[idp.size()];
    	int i = 0;
    	for(Punto p : idp){
    		tmp[i] = p.getY();
    		i++;
    	}
    	return tmp;
    }
    
    public double getArea(){
    	double area = 0;
        int i = 0;
        while(i < size()-1)
        {
            Punto p1 = idp.get(i);
            Punto p2 = idp.get(i +1);
            if(p1.getY() * p2.getY() < 0){
                double x = (-(p2.getX()-p1.getX())*p1.getY())/(p2.getY()-p1.getY()) + p1.getX();
                area += getPartialArea(p1,new Punto(x,0));
                area += getPartialArea(new Punto(x,0),p2);
            }
            else
                area += getPartialArea(p1,p2);
            i++;
        }
        return area;
    }
    
    public double getLenght(){
    	double tmp = 0;
        int i = 0;
        while(i < idp.size() -1){
            tmp += Punto.getDistance(
            		idp.get(i),
            		idp.get(i +1));           
            i++;
        }
        return tmp;
    }
    
    public double size(){
    	return idp.size();
    }
    
    public double getMaxX(){
    	return idp.get(idp.size() -1).getX();
    }
    
    public double getMinX(){
    	return idp.get(0).getX();
    }
    
    public double getMaxY(){
    	double max = idp.get(0).getY();
    	for(int i = 1; i<idp.size(); i++){
    		double tmp = idp.get(i).getY();
    		if(max < tmp){
    			max = tmp;
    		}
    	}
    	return max;
    }
    
    public Punto getMax(){
    	Punto p = idp.get(0);
    	for(int i = 1; i < idp.size(); i++){
    		Punto tmp = idp.get(i);
    		if(tmp.getY() > p.getY()){
    			p = tmp;
    		}
    	}
    	return p;
    }
    
    public Punto getMin(){
    	Punto p = idp.get(0);
    	for(int i = 1; i < idp.size(); i++){
    		Punto tmp = idp.get(i);
    		if(tmp.getY() < p.getY()){
    			p = tmp;
    		}
    	}
    	return p;
    }
}
