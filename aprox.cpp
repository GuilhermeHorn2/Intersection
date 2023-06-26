#include <iostream>
#include <cstdlib>


class coord{
	double x;
	double y;
public:
	coord(){}

	coord(double a,double b){
		x = a;
		y = b;
	}

	~coord(){
		free(this);
	}

	double get_x(){
		return x;
	}
	double get_y(){
		return y;
	}

	void print(){
		std::string s = "";
		s.append("(");
		s.append(std::to_string(x));
		s.append(",");
		s.append(std::to_string(y));
		s.append(")");
		std::cout << s << "\n";
	}

};

class intersect{
	coord r1;
	coord r2;
	coord s1;
	coord s2;
	double error;
public:
	double max_x_r = -1.0;
	double max_y_r = -1.0;
	double max_x_s = -1.0;
	double max_y_s = -1.0;
	double min_x_r = -1.0;
	double min_y_r = -1.0;
	double min_x_s = -1.0;
	double min_y_s = -1.0;
	intersect(coord a,coord b,coord c,coord d,double err){
		r1 = a;
		r2 = b;
		s1 = c;
		s2 = d;
		error = err;
		//max from r:
		if(a.get_x() > b.get_x()){
			max_x_r = a.get_x();
			min_x_r = b.get_x();
		}
		else{
			max_x_r = b.get_x();
			min_x_r = a.get_x();
		}

		if(a.get_y() > b.get_y()){
			max_y_r = a.get_y();
			min_y_r = b.get_y();
		}
		else{
			max_y_r = b.get_y();
			min_y_r = a.get_y();
		}

		//max from s:
		if(c.get_x() > d.get_x()){
			max_x_s = c.get_x();
			min_x_s = d.get_x();
		}
		else{
			max_x_s = d.get_x();
			min_x_s = c.get_x();
		}

		if(c.get_y() > d.get_y()){
			max_y_s = c.get_y();
			min_y_s = d.get_y();
		}
		else{
			max_y_s = d.get_y();
			min_y_s = c.get_y();
		}



	}

	~intersect(){
		free(this);
	}

	bool has_inter(){

		//checking if the sets has intersections:

		if(min_x_r > max_x_s){
			return false;
		}
		if(min_x_s > max_x_r){
			return false;
		}
		if(min_y_r > max_y_s){
			return false;
		}
		if(min_y_s > max_y_r){
			return false;
		}
		return true;
	}

	double mod(double x){
		if(x < 0){
			return -x;
		}
		return x;
	}

	coord calculate_inter(){

		//coord* inter = NULL;
		coord inter = coord(-1,-1);
		if(!has_inter()){
			std::cout << "Intersect does not exist" << "\n";
			return inter;
		}

		//calculating the line functions parameters:

		//angular coeficients
		double m = (r2.get_y() - r1.get_y())/(r2.get_x() - r1.get_x());
		double a = (s2.get_y() - s1.get_y())/(s2.get_x() - s1.get_x());

		//linear coeficients
		double n = r1.get_y() - m*(r1.get_x());
		double b = s1.get_y() - a*(s1.get_x());

		/*std::cout << m << "\n";
		std::cout << n << "\n";*/
		//std::cout << b << "\n";
		double strt;
		double end;


		//search in max(min_x_r,min_x_s) to min(max_x_r,max_y_s)
		if(min_x_r > min_x_s){
			strt = min_x_r;
		}
		else{
			strt = min_x_s;
		}

		if(max_x_r < max_x_s){
			end = max_x_r;
		}
		else{
			end = max_x_s;
		}
		//std::cout << strt<< "\n";
		double x = strt;
		while(x <= end){
			double y1 = (m*x)+n;
			double y2 = (a*x)+b;
			double dist = y2 - y1;
			if(mod(dist) <= error && y1 >= min_y_r && y2 >= min_y_s && y1 <= max_y_r && y2 <= max_y_s){
				inter = coord(x,y1);
				inter.print();
				return inter;
			}
			x += error;

		}
		return inter;

	}

};


int main()
{
	/*  || \ */

	//printf("-----");

	coord p1 = coord(1.0,2.0);
	coord p2 = coord(5.0,6.0);
	coord p3 = coord(1.0,3.0);
	coord p4 = coord(6.0,5.0);

	intersect inter = intersect(p1,p2,p3,p4,0.01);
	coord x = inter.calculate_inter();





	return 0;
}


