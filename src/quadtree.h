#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include <fstream>
#include "mmath.h"
#include "node.h"

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
	qnode<D> *m_node;
	quadtree<N,D> *m_dir[4];
	qpoint m_quad[2];
	N m_umin;
public:
	quadtree(){
		this->m_quad[0] = qpoint(0,0);
		this->m_quad[1] = qpoint(0,0);
		this->m_umin = 1;
		this->m_node = new qnode<D>();
		this->m_dir[0] = NULL;	this->m_dir[1] = NULL;
		this->m_dir[2] = NULL;	this->m_dir[3] = NULL;
	}

	quadtree(qpoint _tl, qpoint _br, N _min){
		this->m_quad[0] = _tl;
		this->m_quad[1] = _br;
		this->m_umin = _min;
		this->m_node = new qnode<D>();
		this->m_dir[0] = NULL;	this->m_dir[1] = NULL;
		this->m_dir[2] = NULL;	this->m_dir[3] = NULL;
	}

	bool inside(qpoint);	
	void insert(qdata<D> *);	
	qnode<D>* find(qpoint);	

	void rdfile(string);
	void qtsaveline();
	void qtline();	
	~quadtree(){	};	
};

template <class N, class D>
bool quadtree<N,D>::inside(qpoint p){
    return ((p.x>=m_quad[0].x and p.x <= m_quad[1].x) and
        (p.y>=m_quad[0].y and p.y<=m_quad[1].y));
}

template<class N, class D>
void quadtree<N,D>::insert(qdata<D> *data){
	if (data == NULL) return;
	if (!inside(data->m_ps)) return;
	

	if(absolute(this->m_quad[0].x-this->m_quad[1].x)<=m_umin and
		absolute(this->m_quad[0].y-this->m_quad[1].y)<=m_umin){		
		if(m_node->size()<=NDATA){
			m_node->add_data(data);
			vpoints.push_back(data->m_ps);
		}
		return;
	}

	if (((this->m_quad[0].x + this->m_quad[1].x)/2)>=data->m_ps.x){
		//NW
		if (((this->m_quad[0].y + this->m_quad[1].y)/2)>= data->m_ps.y){
			if (this->m_dir[0] == NULL)
				this->m_dir[0] = new quadtree<N,D>(
					qpoint(this->m_quad[0].x, this->m_quad[0].y),
					qpoint((this->m_quad[0].x + this->m_quad[1].x)/2,
						(this->m_quad[0].y + this->m_quad[1].y)/2),m_umin);
			this->m_dir[0]->insert(data);
		}

		//SW
		else{
			if(this->m_dir[2] == NULL)
				this->m_dir[2] = new quadtree<N,D>(
					qpoint(this->m_quad[0].x, (this->m_quad[0].y + this->m_quad[1].y)/2),
					qpoint((this->m_quad[0].x + this->m_quad[1].x)/2, this->m_quad[1].y),m_umin);
			this->m_dir[2]->insert(data);
		}
	}
	else{
		//NE
		if ((this->m_quad[0].y + this->m_quad[1].y) / 2 >= data->m_ps.y){
			if (this->m_dir[1] == NULL)
				this->m_dir[1] = new quadtree<N,D>(
					qpoint((this->m_quad[0].x + this->m_quad[1].x)/2, this->m_quad[0].y),
					qpoint(this->m_quad[1].x, (this->m_quad[0].y + this->m_quad[1].y)/2),m_umin);
			this->m_dir[1]->insert(data);
		}

		//SE
		else{
			if (this->m_dir[3] == NULL)
				this->m_dir[3] = new quadtree<N,D>(
					qpoint((this->m_quad[0].x + this->m_quad[1].x)/2, (this->m_quad[0].y + this->m_quad[1].y)/2),
					qpoint(this->m_quad[1].x, this->m_quad[1].y),m_umin);
			this->m_dir[3]->insert(data);
		}
	}
}

template<class N, class D>
qnode<D>* quadtree<N,D>::find(qpoint p){
	//if (!inside(p)) return new qnode<D>(qpoint(0,0),"NULL");
	if(!inside(p)) return NULL;	
	if(m_node->size()>0)	return m_node;

	if((this->m_quad[0].x + this->m_quad[1].x)/2 >= p.x){
		//NW
		if ((this->m_quad[0].y + this->m_quad[1].y)/2 >= p.y){
			cout << "NW->";
			if(this->m_dir[0] == NULL)	return NULL;
			return this->m_dir[0]->find(p);
		}
		//SW
		else{
			cout << "SW->";
			if(this->m_dir[2] == NULL)	return NULL;
			return this->m_dir[2]->find(p);
		}
	}
	else{
		//NE
		if((this->m_quad[0].y + this->m_quad[1].y)/2 >= p.y){
			cout << "NE->";
			if(this->m_dir[1] == NULL)	return NULL;
			return this->m_dir[1]->find(p);
		}
		//SE
		else{
			cout << "SE->";
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

	xmin = 500;
    xmax = -500;

    ymin = 500;
    ymax = -500;

    double latit, longi;
	getline(file,tmp,'\n');		//RowName
	while(file.good()){		
		getline(file,nam,',');		//Country	
		getline(file,lat,',');		//Latitude
		getline(file,lon,'\n');		//Longitude

		latit = stod(lat);
		longi = stod(lon);

        if(latit<xmin)    xmin = latit;
        if(latit>xmax)    xmax = latit;

        if(longi<ymin)    ymin = longi;
        if(longi>ymax)    ymax = longi;

		//cout << lat << " " << lon << " " << nam << endl;
		insert(new qdata<D>(qpoint(latit,longi),nam));
	}
	file.close();
}

template<class N, class D>
void quadtree<N,D>::qtsaveline(){
    qtline();        
    for(int i=0; i<4; i++)
    	if(m_dir[i]!=NULL){
    		m_dir[i]->qtsaveline();
    	}
}

template<class N, class D>
void quadtree<N,D>::qtline(){
	double yt,xt;
	yt = (m_quad[1].y+m_quad[0].y)/2;
	xt = (m_quad[1].x+m_quad[0].x)/2;

	vlines.push_back(qpoint(m_quad[0].x,yt));	
	vlines.push_back(qpoint(m_quad[1].x,yt));	
	vlines.push_back(qpoint(xt,m_quad[0].y));	
	vlines.push_back(qpoint(xt,m_quad[1].y));	
}

#endif