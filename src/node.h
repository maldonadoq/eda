#ifndef _NODE_H_
#define _NODE_H_

#include "data.h"

template <class T, T _d>
class cnode{
public:
	cpoint m_ps;
	T m_data;
	cnode(cpoint _mps, T _data){
		this->m_ps = _mps;
		this->m_data = _data;
	}

	cnode(){	this->m_data = _d;	}
	~cnode(){	};
};

#endif