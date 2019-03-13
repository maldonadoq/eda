#ifndef _BYTREE_H_
#define _BYTREE_H_

#include <iostream>
#include <stdio.h>
#include <queue>
#include <stack>
#include <math.h>
#include "node.h"

using namespace std;

template<class K, class T, class C>
class mbytree{
public:
	unsigned ver;
public:
	C cmp;
	bnode<K,T> *m_root;
	unsigned size;

	mbytree(){
		this->m_root = NULL;
		this->ver = 0;
	}

	bool find(T, bnode<K,T> **&);
	bool insert(K, T);
	bool remove(T);
	void version(unsigned);
	void version(bnode<K,T> *, unsigned);
	~mbytree();
};

template<class K, class T, class C>
bool mbytree<K,T,C>::find(T x, bnode<K,T> **&p){
	for(p=&(this->m_root); *p and ((*p)->m_key!=x); p=&((*p)->m_node[cmp((*p)->m_key,x)]));
	return !!*p;
}

template<class K, class T, class C>
bool mbytree<K,T,C>::insert(K _key, T _data){
	bnode<K,T> **p;
	this->ver++;
	if(find(_key,p)){
		(*p)->m_data.push_back(mbox<T>(true,ver,_data));
		return false;
	}

	*p = new bnode<K,T>(_key,mbox<T>(true,ver,_data));
	return true;
}

template<class K, class T, class C>
bool mbytree<K,T,C>::remove(T x){
	bnode<K,T> **p;	
	if(find(x,p) and (*p)->data_state()){
		this->ver++;
		(*p)->m_data.push_back(mbox<T>(false,ver,x));
		return false;	
	}
	return false;
}

template<class K, class T, class C>
void mbytree<K,T,C>::version(unsigned _version){
	cout << "v[" << _version << "]:\t";
	version(this->m_root, _version);
	cout << endl;
}

template<class K, class T, class C>
void mbytree<K,T,C>::version(bnode<K,T> *p, unsigned _version){
	if(!p)	return;
	p->data_version(_version);
	version(p->m_node[0], _version);
	version(p->m_node[1], _version);
}

template<class K, class T, class C>
mbytree<K,T,C>::~mbytree(){
	if(this->m_root != NULL){
		queue<bnode<K,T> *> *a = new queue<bnode<K,T> *>();
		a->push(m_root);
		while(!a->empty()){
			if((a->front())->m_node[0])	a->push((a->front())->m_node[0]);
			if((a->front())->m_node[1])	a->push((a->front())->m_node[1]);
			delete a->front();
			a->pop();
		}
		delete a;
	}
}

#endif