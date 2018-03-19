#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include "setvalue.h"
#include <fstream>
#include "node.h"
#include "mmath.h"

/*
		N
		|		[0]: NW 	[0]: NW
	W --I-- E 	[1]: NE 	[1]: SE
		|		[2]: SW
		S 		[3]: SE	
*/

template <class N, class D>
class quadtree{
private:
	cnode<D> *m_node;	
	quadtree<N,D> *m_dir[4];
	cpoint m_quad[2];
	N m_umin;
public:
	quadtree(){
		this->m_quad[0] = cpoint(0,0);
		this->m_quad[1] = cpoint(0,0);
		this->m_umin = 1;
		this->m_node = new cnode<D>();
		this->m_dir[0] = NULL;	this->m_dir[1] = NULL;
		this->m_dir[2] = NULL;	this->m_dir[3] = NULL;
	}

	quadtree(cpoint _tl, cpoint _br, N _min){
		this->m_quad[0] = _tl;
		this->m_quad[1] = _br;
		this->m_umin = _min;
		this->m_node = new cnode<D>();
		this->m_dir[0] = NULL;	this->m_dir[1] = NULL;
		this->m_dir[2] = NULL;	this->m_dir[3] = NULL;
	}

	void insert(cdata<D> *);
	cnode<D>* find(cpoint);
	void rdfile(string);
	void qtprint();
	bool inside(cpoint);
	~quadtree(){	};	
};

template <class N, class D>
bool quadtree<N,D>::inside(cpoint p){
    return ((p.x>=m_quad[0].x and p.x <= m_quad[1].x) and
        (p.y>=m_quad[0].y and p.y<=m_quad[1].y));
}

template<class N, class D>
void quadtree<N,D>::insert(cdata<D> *data){
	if (data == NULL) return;
	if (!inside(data->m_ps)) return;
	

	if(absolute(this->m_quad[0].x-this->m_quad[1].x)<=m_umin and
		absolute(this->m_quad[0].y-this->m_quad[1].y)<=m_umin){		
		if(m_node->size()<=m_ndt)	m_node->add_data(data);
		return;
	}

	if (((this->m_quad[0].x + this->m_quad[1].x)/2)>=data->m_ps.x){
		//NW
		if (((this->m_quad[0].y + this->m_quad[1].y)/2)>= data->m_ps.y){
			if (this->m_dir[0] == NULL)
				this->m_dir[0] = new quadtree<N,D>(
					cpoint(this->m_quad[0].x, this->m_quad[0].y),
					cpoint((this->m_quad[0].x + this->m_quad[1].x)/2,
						(this->m_quad[0].y + this->m_quad[1].y)/2),m_umin);
			this->m_dir[0]->insert(data);
		}

		//SW
		else{
			if(this->m_dir[2] == NULL)
				this->m_dir[2] = new quadtree<N,D>(
					cpoint(this->m_quad[0].x, (this->m_quad[0].y + this->m_quad[1].y)/2),
					cpoint((this->m_quad[0].x + this->m_quad[1].x)/2, this->m_quad[1].y),m_umin);
			this->m_dir[2]->insert(data);
		}
	}
	else{
		//NE
		if ((this->m_quad[0].y + this->m_quad[1].y) / 2 >= data->m_ps.y){
			if (this->m_dir[1] == NULL)
				this->m_dir[1] = new quadtree<N,D>(
					cpoint((this->m_quad[0].x + this->m_quad[1].x)/2, this->m_quad[0].y),
					cpoint(this->m_quad[1].x, (this->m_quad[0].y + this->m_quad[1].y)/2),m_umin);
			this->m_dir[1]->insert(data);
		}

		//SE
		else{
			if (this->m_dir[3] == NULL)
				this->m_dir[3] = new quadtree<N,D>(
					cpoint((this->m_quad[0].x + this->m_quad[1].x)/2, (this->m_quad[0].y + this->m_quad[1].y)/2),
					cpoint(this->m_quad[1].x, this->m_quad[1].y),m_umin);
			this->m_dir[3]->insert(data);
		}
	}
}

template<class N, class D>
cnode<D>* quadtree<N,D>::find(cpoint p){
	//if (!inside(p)) return new cnode<D>(cpoint(0,0),"NULL");
	if(!inside(p)) return NULL;	
	if(m_node->size()>0)	return m_node;

	if((this->m_quad[0].x + this->m_quad[1].x)/2 >= p.x){
		//NW
		if ((this->m_quad[0].y + this->m_quad[1].y)/2 >= p.y){
			if(this->m_dir[0] == NULL)	return NULL;
			return this->m_dir[0]->find(p);
		}
		//SW
		else{
			if(this->m_dir[2] == NULL)	return NULL;
			return this->m_dir[2]->find(p);
		}
	}
	else{
		//NE
		if((this->m_quad[0].y + this->m_quad[1].y)/2 >= p.y){
			if(this->m_dir[1] == NULL)	return NULL;
			return this->m_dir[1]->find(p);
		}
		//SE
		else{
			if (this->m_dir[3] == NULL)	return NULL;
			return this->m_dir[3]->find(p);
		}
	}
}

template<class N, class D>
void quadtree<N,D>::rdfile(string filename){
	ifstream file(filename);
	string lat,lon,nam,tmp;
	if(!file.is_open()){
		cout << "error! cvs wrong!!" << endl;
		return;
	}

	while(file.good()){
		getline(file,nam,',');		//Country
		getline(file,tmp,',');		//Capital
		getline(file,lat,',');		//Latitude
		getline(file,lon,',');		//Longitude
		getline(file,tmp,',');		//Code
		getline(file,tmp,'\n');		//Continent

		//cout << lat << " " << lon << " " << nam << endl;
		insert(new cdata<D>(cpoint(stod(lat),stod(lon)),nam));
	}
	file.close();
}

template<class N, class D>
void quadtree<N,D>::qtprint(){
    if(m_node->size()>0){
    	cout << "\n[" << m_quad[0] << ":" << m_quad[1] << "]" << endl;
    	cout << *m_node << endl;
    }    
        
    for(int i=0; i<4; i++)
    	if(m_dir[i]!=NULL){
    		cout << cardinal[i] << "->";
    		m_dir[i]->qtprint();
    	}
}

#endif