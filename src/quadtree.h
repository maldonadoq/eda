#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include <fstream>
#include "node.h"


/*
		N
		|		[0]: NW 	[0]: NW
	W --I-- E 	[1]: NE 	[1]: SE
		|		[2]: SW
		S 		[3]: SE	
*/

template <class N, N _d>
class quadtree{
private:
	cnode<N,_d> *m_node;	
	quadtree<N,_d> *m_dir[4];
	cpoint m_quad[2];	
public:
	quadtree(){
		this->m_quad[0] = cpoint(0,0);
		this->m_quad[1] = cpoint(0,0);
		this->m_node = NULL;		
		this->m_dir[0] = NULL;	this->m_dir[1] = NULL;
		this->m_dir[2] = NULL;	this->m_dir[3] = NULL;
	}

	quadtree(cpoint _tl, cpoint _br){
		this->m_quad[0] = _tl;
		this->m_quad[1] = _br;
		this->m_node = NULL;		
		this->m_dir[0] = NULL;	this->m_dir[1] = NULL;
		this->m_dir[2] = NULL;	this->m_dir[3] = NULL;
	}

	void insert(cnode<N,_d>*);
	cnode<N,_d>* find(cpoint);
	//void rdle(string);
	bool inside(cpoint);
	~quadtree(){	};	
};

template <class N, N _d>
bool quadtree<N,_d>::inside(cpoint p){
    return ((p.x>=m_quad[0].x and p.x <= m_quad[1].x) and
        (p.y>=m_quad[0].y and p.y<=m_quad[1].y));
}

template<class N, N _d>
void quadtree<N,_d>::insert(cnode<N,_d> *node){
	if (node == NULL) return;
	if (!inside(node->m_ps)) return;

	if(abs(this->m_quad[0].x-this->m_quad[1].x)<=1 and
		abs(this->m_quad[0].y-this->m_quad[1].y)<=1){
		if (m_node == NULL)	m_node = node;
		return;
	}

	if (((this->m_quad[0].x + this->m_quad[1].x)/2)>=node->m_ps.x){
		//NW
		if (((this->m_quad[0].y + this->m_quad[1].y)/2)>= node->m_ps.y){
			if (this->m_dir[0] == NULL)
				this->m_dir[0] = new quadtree<N,_d>(
					cpoint(this->m_quad[0].x, this->m_quad[0].y),
					cpoint((this->m_quad[0].x + this->m_quad[1].x)/2,
						(this->m_quad[0].y + this->m_quad[1].y)/2));
			this->m_dir[0]->insert(node);
		}

		//SW
		else{
			if(this->m_dir[2] == NULL)
				this->m_dir[2] = new quadtree<N,_d>(
					cpoint(this->m_quad[0].x, (this->m_quad[0].y + this->m_quad[1].y)/2),
					cpoint((this->m_quad[0].x + this->m_quad[1].x)/2, this->m_quad[1].y));
			this->m_dir[2]->insert(node);
		}
	}
	else{
		//NE
		if ((this->m_quad[0].y + this->m_quad[1].y) / 2 >= node->m_ps.y){
			if (this->m_dir[1] == NULL)
				this->m_dir[1] = new quadtree<N,_d>(
					cpoint((this->m_quad[0].x + this->m_quad[1].x)/2, this->m_quad[0].y),
					cpoint(this->m_quad[1].x, (this->m_quad[0].y + this->m_quad[1].y)/2));
			this->m_dir[1]->insert(node);
		}

		//SE
		else{
			if (this->m_dir[3] == NULL)
				this->m_dir[3] = new quadtree<N,_d>(
					cpoint((this->m_quad[0].x + this->m_quad[1].x)/2, (this->m_quad[0].y + this->m_quad[1].y)/2),
					cpoint(this->m_quad[1].x, this->m_quad[1].y));
			this->m_dir[3]->insert(node);
		}
	}
}

template<class N, N _d>
cnode<N,_d>* quadtree<N,_d>::find(cpoint p){
	//if (!inside(p)) return new cnode<N,_d>();
	if (!inside(p)) return NULL;
	if (m_node != NULL)	return m_node;

	if ((this->m_quad[0].x + this->m_quad[1].x)/2 >= p.x){
		//NW
		if ((this->m_quad[0].y + this->m_quad[1].y)/2 >= p.y){
			if (this->m_dir[0] == NULL)	return NULL;
			return this->m_dir[0]->find(p);
		}
		//SW
		else{
			if (this->m_dir[2] == NULL)	return NULL;
			return this->m_dir[2]->find(p);
		}
	}
	else{
		//NE
		if ((this->m_quad[0].y + this->m_quad[1].y)/2 >= p.y){
			if (this->m_dir[1] == NULL)	return NULL;
			return this->m_dir[1]->find(p);
		}
		//SE
		else{
			if (this->m_dir[3] == NULL)	return NULL;
			return this->m_dir[3]->find(p);
		}
	}
}

/*template<class N, N _d>
void quadtree<N,_d>::rdfile(string filename){
	string lat,lon;
	ifstream file(filename);
	if(!file.is_open())	cout << "error! cvs wrong!!" << endl;

	while(file.good()){
		getline(file,lat,',');
		getline(file,lon,'\n');

		cout << lat << " " << lon << endl;
	}

	file.close();
}*/

#endif