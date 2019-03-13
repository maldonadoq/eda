#ifndef _TABLE_H_
#define _TABLE_H_

// table of kdpoint curse of dimensionality
template<class T>
class ctable{
public:
	int m_nd, m_ndata;
	kdpoint<T> **m_table;
	ctable(int _nd, int _ndata){
		this->m_nd = _nd;
		this->m_ndata = _ndata;
		this->m_table = new kdpoint<T> *[m_ndata];
		for(int i=0; i<m_ndata; i++)
			this->m_table[i] = new kdpoint<T>(m_nd);
	}	

	~ctable(){
		delete this->m_table;
	}

	double min_dis();
	double max_dis();
	double prm_dis();
	double mdistance(kdpoint<T>*, kdpoint<T>*);
	void print();
};


template <class T>
double ctable<T>::mdistance(kdpoint<T> *a, kdpoint<T> *b){
	double dis = 0;
	for(int i=0; i<m_nd; i++)
		dis += pow(a->m_point[i] - b->m_point[i],2);
	dis = sqrt(dis);
	return dis;
}

template<class T>
double ctable<T>::min_dis(){
	double tm,m;
	m = mdistance(m_table[0],m_table[1]);

	for(int i=0; i<m_ndata; i++){
		for(int j=i+1; j<m_ndata; j++){
			tm = mdistance(m_table[i],m_table[j]);
			if(tm<m)	m = tm;
		}
	}

	return m;
}

template<class T>
double ctable<T>::max_dis(){
	double tm,m;
	m = mdistance(m_table[0],m_table[1]);

	for(int i=0; i<m_ndata; i++){
		for(int j=i+1; j<m_ndata; j++){
			tm = mdistance(m_table[i],m_table[j]);
			if(tm>m)	m = tm;
		}
	}

	return m;
}

template<class T>
double ctable<T>::prm_dis(){
	double m = 0;
	int tm = (m_ndata*(m_ndata-1))/2;
	for(int i=0; i<m_ndata; i++)
		for(int j=i+1; j<m_ndata; j++)
			m+= mdistance(m_table[i],m_table[j]);

	m = m/tm;
	return m;
}

template <class T>
void ctable<T>::print(){
	for(int i=0; i<m_ndata; i++){
		for(int j=0; j<m_nd; j++)
			cout << m_table[i]->m_point[j] << " ";
		cout << endl;
	}
}

#endif