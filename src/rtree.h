#ifndef _RTREE_H_
#define _RTREE_H_

#include "node.h"
#include "point.h"
#include <assert.h>

template<class T, class D>
class rtree{
private:
	rnode<T,D> *m_root;
	rpoint<T> m_limit[2];
	unsigned rdim, M;
public:
	rtree(unsigned _rdim, unsigned _M, T _lim1, T _lim2){		
		this->rdim = _rdim;
		this->M = _M;
		this->m_root = new rnode<T,D>(this->M, true);
		this->m_limit[0] = rpoint<T>(this->rdim, _lim1);
		this->m_limit[1] = rpoint<T>(this->rdim, _lim2);
	}

	rtree(rpoint<T> _lim1, rpoint<T> _lim2){
		this->m_limit[0] = _lim1;
		this->m_limit[1] = _lim2;
	}

	bool inside(rpoint<T> &);
	void chooseleaf(rdata<T,D> *, rnode<T,D> **&);
	void linearpickseeds(rnode<T,D> **&, rnode<T,D> **&, rnode<T,D> **&);
	void splitnode(rnode<T,D> **&, rnode<T,D> **&, rnode<T,D> **&);
	void picknext(rnode<T,D> **&, rnode<T,D> **&, rnode<T,D> **&);
	void adjusttree(rnode<T,D> **&);
	void insert(rdata<T,D> *_data);

	~rtree(){	delete this->m_root;	}
};

template <class T, class D>
bool rtree<T,D>::inside(rpoint<T> &p){
	bool ins;
	for(unsigned i=0; i<p.dim(); i++){
		ins = (p.m_cord[i]>=m_limit[0].m_cord[i] 
			and p.m_cord[i]<=m_limit[1].m_cord[i]);
		if(!ins) return false;
	}
    return true;
}

template<class T, class D>
void rtree<T,D>::chooseleaf(rdata<T,D> *_data, rnode<T,D> **& _node){
	unsigned index = 0;
	double auxarea, minarea, tmparea, tmpenla;
	while(!(*_node)->isleaf()){
		auxarea = (*_node)->m_nodes[0]->area();
		minarea = (*_node)->m_nodes[0]->enlargement(_data) - auxarea;

		for(unsigned i=1; i<(*_node)->nodesize(); i++){
			tmparea = (*_node)->m_nodes[i]->area();
			tmpenla = (*_node)->m_nodes[i]->enlargement(_data) - tmparea;
			if(tmpenla < minarea)	index = i;
			else if(tmpenla == minarea){
				if(tmparea < auxarea)
					index = i;
			}
		}
		_node = &((*_node)->m_nodes[index]);
	}
}

template<class T, class D>
void rtree<T,D>::picknext(rnode<T,D> **&_node, rnode<T,D> **& G1, rnode<T,D> **& G2){
	double min1, min2;

	rdata<T,D> *tmp;

	while((*_node)->datasize()>0){
		tmp = (*_node)->getdata();

		min1 = (*G1)->enlargement(tmp);
		min2 = (*G2)->enlargement(tmp);

		if(min1 < min2)
			(*G1)->insert_data(tmp);
		else
			(*G2)->insert_data(tmp);
	}	
}

template<class T, class D>
void rtree<T,D>::linearpickseeds(rnode<T,D> **&_node, rnode<T,D> **&_G1, rnode<T,D> **&_G2){
	rdata<T,D> *S1, *S2;
	(*_node)->lseeds(S1, S2);

	(*_G1)->insert_data(S1);
	(*_G2)->insert_data(S1);

	picknext(_node, _G1, _G2);
}

template<class T, class D>
void rtree<T,D>::splitnode(rnode<T,D> **& _node, rnode<T,D> **& _G1, rnode<T,D> **& _G2){
	(*_G1) = new rnode<T,D>(this->M, true);
	(*_G2) = new rnode<T,D>(this->M, true);	
	linearpickseeds(_node, _G1, _G2);	
}

template<class T, class D>
void rtree<T,D>::adjusttree(rnode<T,D> **& _node){

}

template<class T, class D>
void rtree<T,D>::insert(rdata<T,D> *_data){
	if(!inside(_data->m_point))	return;

	rnode<T,D> **_cnode = &(this->m_root);
	chooseleaf(_data, _cnode);
	if(!(*_cnode)->insert_data(_data)){		
		rnode<T,D> **G1, **G2;	
		assert(_cnode!=NULL);
		splitnode(_cnode, G1, G2);
		(*G1)->m_parent = *_cnode;
		(*G2)->m_parent = *_cnode;
		(*_cnode)->m_data = NULL;
		(*_cnode)->m_leaf = false;
		adjusttree(_cnode);
	}
}

#endif