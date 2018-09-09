package progettoP2;
import static java.lang.Math.*;

public class Punto {
	private double x;
	private double y;

	public Punto(){
		x = 0;
		y = 0;		
	}
	public Punto(double _x, double _y){
		// int -> punto
		x = _x;
		y = _y;
	}
	
	public Boolean operatorUgualeUguale(final Punto _p){
		return x == _p.x;
	}

	public double getX(){
		return x;
	}
	
	public double getY(){
		return y;
	}

	public double getDistance(final Punto _p){
		// distanza tra due punti
		return sqrt(pow(x - _p.x,2) + pow(y - _p.y,2));
	}
	
	public static double getDistance(final Punto _p1, final Punto _p2){
		return sqrt(pow(_p1.x - _p2.x, 2) + pow(_p1.y - _p2.y, 2));
	}
	    
	public Punto getLocation(){
		return new Punto(x,y);
	}
	
	public void setLocation(int _x, int _y){
		x = _x;
	    y = _y;
	}
}
