#ifndef _NODE_H_
#define _NODE_H_

#include "data.h"
#include <list>

using namespace std;

// node for quad-tree
template <class T>
class qnode{
public:
	list<qdata<T> *> m_list;    
	qnode(){	};

	void add_data(qdata<T> *a){	this->m_list.push_back(a);	}
	unsigned size(){	return this->m_list.size();	}
	
    friend ostream& operator<< (std::ostream & out, qnode<T> &c){		
		typename list<qdata<T> *>::iterator it;

    	for(it=c.m_list.begin(); it!=c.m_list.end(); it++)	out << "\t" << *(*it) << "\n";
		return out;
   	}

	~qnode(){	};
};

template<class T>
class mbox{
public:
	bool m_state;
	unsigned m_vers;
	T m_data;

	mbox(bool _state, unsigned _vers, T _data){
		this->m_state = _state;
		this->m_vers = _vers;
		this->m_data = _data;
	}
};

// node for bynary tree [fatnode]
template<class K, class T>
class bnode{
public:
    bnode<K,T> *m_node[2];
    vector<mbox<T> > m_data;
    K m_key;
    
    bnode(K _key, mbox<T> _data){
    	this->m_key = _key;
        this->m_data.push_back(_data);
        this->m_node[0] = this->m_node[1] = NULL;
    }

    friend ostream& operator<<(ostream & out, const bnode<K,T>& c){
		for(unsigned i=0; i<c.m_data.size(); i++)
			out << c.m_data[i].m_data << " ";
		return out;
	}

	bool data_state(){	return this->m_data.back().m_state;	}
	
	void data_version(unsigned _v){
		if(m_data[0].m_vers<=_v){
			unsigned i;
			for(i=0; i<this->m_data.size(); i++)
				if(m_data[i].m_vers>_v)	break;

			if(m_data[i-1].m_state)
				cout << "[" << m_key  << ": " << m_data[i-1].m_data << "] ";
		}
	}
};

#endif