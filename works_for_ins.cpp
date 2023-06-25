#include <iostream>



class coord{
	int x;
	int y;
public:
	coord(){}

	coord(int a,int b){
		x = a;
		y = b;
	}

	~coord(){
		free(this);
	}

	int get_x(){
		return x;
	}
	int get_y(){
		return y;
	}

	void print(){
		std::string s = "";
		s.append("(");
		s.append(x+",");
		s.append(y+")");
		std::cout << s << "\n";
	}

};

class intersect{
	coord r1;
	coord r2;
	coord s1;
	coord s2;
public:
	int max_x_r = -1;
	int max_y_r = -1;
	int max_x_s = -1;
	int max_y_s = -1;
	int min_x_r = -1;
	int min_y_r = -1;
	int min_x_s = -1;
	int min_y_s = -1;
	intersect(coord a,coord b,coord c,coord d){
		r1 = a;
		r2 = b;
		s1 = c;
		s2 = d;

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
			max_x_r = c.get_x();
			min_x_r = d.get_x();
		}
		else{
			max_x_r = d.get_x();
			min_x_r = c.get_x();
		}

		if(c.get_y() > d.get_y()){
			max_y_r = c.get_y();
			min_y_r = d.get_y();
		}
		else{
			max_y_r = d.get_y();
			min_y_r = c.get_y();
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

	coord* calculate_inter(){

		coord* inter = NULL;
		if(!has_inter()){
			std::cout << "Intersect is null" << "\n";
			return inter;
		}

		//calculating the line functions parameters:

		//angular coeficients
		int m = (max_y_r - min_y_r)/max_x_r - min_x_r;
		int a = (max_y_s - min_y_s)/max_x_s - min_x_s;

		//linear coeficients
		int n = max_y_r - m*(max_x_r);
		int b = max_y_s - a*(max_x_s);

		int strt;
		int end;


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

		for(int i = strt;i <= end;i++){
			if((m*i + n) == (a*i+b)){
				inter = new coord(i,m*i+n);
			}
		}

		inter->print();
		return inter;

	}

};


int main()
{
	/*  || \ */

	coord p1 = coord(1,2);
	coord p2 = coord(5,6);
	coord p3 = coord(2,3);
	coord p4 = coord(6,5);

	intersect inter = intersect(p1,p2,p3,p4);
	coord* x = inter.calculate_inter();



	return 0;
}


