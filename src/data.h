#ifndef _DATA_H_
#define _DATA_H_

#include <iostream>
#include "point.h"

using namespace std;

// data for quad-tree
template<class T>
class qdata{
public:
	qpoint m_ps;
	T m_data;
	qdata(qpoint _mps, T _data){
		this->m_ps = _mps;
		this->m_data = _data;
	}
	friend ostream& operator<< (ostream & out, const qdata &c){
       out << c.m_ps << ": " << c.m_data;
       return out;
   	}   	
	~qdata(){	};
};

template<class T, class D>
class rdata{
public:
	rpoint<T> m_point;
	D m_data;
	rdata(rpoint<T> _mpoint, D _data){
		this->m_point = _mpoint;
		this->m_data = _data;
	}
	~rdata(){	};
};

template<class T, class D>
class rbox{
public:
	rdata<T,D> *p[2];
	double dist;
	rbox(){
		this->p[0] = NULL;
		this->p[1] = NULL;
		this->dist = 0;
	}

	void setmin(rdata<T,D> *p){	this->p[0] = p;	}
	void setmax(rdata<T,D> *p){	this->p[1] = p;	}
	void setdis(double _d){	this->dist = _d;	}
};

#endif