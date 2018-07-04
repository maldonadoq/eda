#ifndef _POINT_H_
#define _POINT_H_

#include <vector>
#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;

// point table curse dimensionality
template<class T>
class kdpoint{
public:
	T *m_point;
	kdpoint(int d){
		this->m_point = new T[d];		
		for(int i=0; i<d; i++)
			this->m_point[i] = (T)rand()/(T)RAND_MAX;
	}

	kdpoint(int d, T *_point);

	~kdpoint(){	delete this->m_point;	}
};

// point quad-tree
class qpoint{
public:
	double x,y;
	qpoint(){	
		this->x = 0;
		this->y = 0;	
	}
	qpoint(double _x, double _y){
		this->x = _x;
		this->y = _y;
	}
	friend ostream& operator<< (ostream & out, const qpoint &c){
       out << setprecision(10) << "(" << c.x << "," << c.y << ")";	
       return out;
   	}
	~qpoint(){	};
};

// point r-tree
template<class T>
class rpoint{
private:	
public:
	vector<T> m_cord;
	
	rpoint(){	};

	rpoint(unsigned d){
		for(unsigned i=0; i<d; i++){
			this->m_cord.push_back((T)rand()/(T)RAND_MAX);
		}
	}

	rpoint(unsigned d, T n){
		for(unsigned i=0; i<d; i++)
			this->m_cord.push_back(n);
	}

	rpoint(vector<T> _cord){	this->m_cord = _cord;	}
	unsigned dim(){	return this->m_cord.size();	}

	~rpoint(){	};
};

#endif