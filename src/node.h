#ifndef _NODE_H_
#define _NODE_H_

#include "data.h"
#include <list>

using namespace std;

template <class T>
class cnode{
public:
	list<cdata<T> *> m_list;
	cnode(){	};

	void add_data(cdata<T> *a){	this->m_list.push_back(a);	}
	unsigned size(){	return this->m_list.size();	}
	friend ostream& operator<< (ostream & out, cnode<T> &c){		
		typename list<cdata<T> *>::iterator it;
    	for(it=c.m_list.begin(); it!=c.m_list.end(); it++)
    		out << "\t" << *(*it) << "\n";
		return out;
   	}

   	void printxy(){
   		typename list<cdata<T> *>::iterator it;
   		cout << "x = [";
    	for(it=m_list.begin(); it!=m_list.end(); it++)
    		cout << setprecision(pre) << (*(*it)).m_ps.x << ",";
    	cout << "]\n";
    	cout << "y = [";
    	for(it=m_list.begin(); it!=m_list.end(); it++)
    		cout << setprecision(pre) << (*(*it)).m_ps.y << ",";
    	cout << "]\n";
   	}
	//cnode(){	this->m_data = NULL;	}
	~cnode(){	};
};

#endif