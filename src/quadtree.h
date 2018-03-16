#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include <iostream>
#include "node.h"

template <class N, N _d>
class quadtree{
private:
	cpoint m_tlp, m_brp;
	cnode<N,_d> *m_node;
	quadtree<N,_d> *m_tlt, *m_trt, *m_blt, *m_brt;
public:
	quadtree(){
		this->m_tlp = cpoint(0,0);
		this->m_brp = cpoint(0,0);
		this->m_node = NULL;		
		this->m_tlt = NULL;
		this->m_trt = NULL;
		this->m_blt = NULL;
		this->m_brt = NULL;
	}

	quadtree(cpoint _tl, cpoint _br){
		this->m_tlp = _tl;
		this->m_brp = _br;
		this->m_node = NULL;		
		this->m_tlt = NULL;
		this->m_trt = NULL;
		this->m_blt = NULL;
		this->m_brt = NULL;
	}

	void insert(cnode<N,_d>*);
	cnode<N,_d>* search(cpoint);
	bool inboundary(cpoint);
	~quadtree(){	};	
};

template<class N, N _d>
void quadtree<N,_d>::insert(cnode<N,_d> *node){
	if (node == NULL) return;
	if (!inboundary(node->m_ps)) return;

	if(abs(this->m_tlp.x-this->m_brp.x)<=1 &&
		abs(this->m_tlp.y-this->m_brp.y)<=1){
		if (m_node == NULL)	m_node = node;
		return;
	}

	if (((this->m_tlp.x + this->m_brp.x)/2)>=node->m_ps.x){
		//this->m_tlt
		if (((this->m_tlp.y + this->m_brp.y)/2)>= node->m_ps.y){
			if (this->m_tlt == NULL)
				this->m_tlt = new quadtree<N,_d>(
					cpoint(this->m_tlp.x, this->m_tlp.y),
					cpoint((this->m_tlp.x + this->m_brp.x)/2,
						(this->m_tlp.y + this->m_brp.y)/2));
			this->m_tlt->insert(node);
		}

		//this->m_blt
		else{
			if(this->m_blt == NULL)
				this->m_blt = new quadtree<N,_d>(
					cpoint(this->m_tlp.x, (this->m_tlp.y + this->m_brp.y)/2),
					cpoint((this->m_tlp.x + this->m_brp.x)/2, this->m_brp.y));
			this->m_blt->insert(node);
		}
	}
	else{
		//this->m_trt
		if ((this->m_tlp.y + this->m_brp.y) / 2 >= node->m_ps.y){
			if (this->m_trt == NULL)
				this->m_trt = new quadtree<N,_d>(
					cpoint((this->m_tlp.x + this->m_brp.x)/2, this->m_tlp.y),
					cpoint(this->m_brp.x, (this->m_tlp.y + this->m_brp.y)/2));
			this->m_trt->insert(node);
		}

		//this->m_brt
		else{
			if (this->m_brt == NULL)
				this->m_brt = new quadtree<N,_d>(
					cpoint((this->m_tlp.x + this->m_brp.x)/2, (this->m_tlp.y + this->m_brp.y)/2),
					cpoint(this->m_brp.x, this->m_brp.y));
			this->m_brt->insert(node);
		}
	}
}

template<class N, N _d>
cnode<N,_d>* quadtree<N,_d>::search(cpoint p){
	//if (!inboundary(p)) return new cnode<N,_d>();
	if (!inboundary(p)) return NULL;
	if (m_node != NULL)	return m_node;

	if ((this->m_tlp.x + this->m_brp.x)/2 >= p.x){
		//this->m_tlt
		if ((this->m_tlp.y + this->m_brp.y)/2 >= p.y){
			if (this->m_tlt == NULL)	return NULL;
			return this->m_tlt->search(p);
		}
		//this->m_blt
		else{
			if (this->m_blt == NULL)	return NULL;
			return this->m_blt->search(p);
		}
	}
	else{
		//this->m_trt
		if ((this->m_tlp.y + this->m_brp.y)/2 >= p.y){
			if (this->m_trt == NULL)	return NULL;
			return this->m_trt->search(p);
		}
		//this->m_brt
		else{
			if (this->m_brt == NULL)	return NULL;
			return this->m_brt->search(p);
		}
	}
}

template <class T, T _d>
bool quadtree<T,_d>::inboundary(cpoint p){
    return (p.x >= m_tlp.x and p.x <= m_brp.x and
        p.y >= m_tlp.y and p.y <= m_brp.y);
}


#endif