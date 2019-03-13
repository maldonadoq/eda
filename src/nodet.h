// btree node
#include <iostream>
using namespace std;

template<class T>
class btnode{
public:
    T *m_data;
    unsigned m_min, m_num;
    btnode<T> **m_child;
    bool m_leaf;

    btnode(unsigned _min, bool _leaf){
        this->m_min = _min;
        this->m_leaf = _leaf;

        this->m_data = new T[(2*_min)-1];
        this->m_child = new btnode<T> *[2*_min];
     
        this->m_num = 0;
    }
     
    void traverse(); 
    btnode<T> *search(T);
    int findKey(T);
     
    void insertNonFull(T); 
    void splitChild(int i, btnode<T> *);
    void remove(T); 
    void removeFromLeaf(unsigned idx);
    void removeFromNonLeaf(unsigned idx);
    T getPred(unsigned idx);
    T getSucc(unsigned idx);
    void fill(unsigned idx);
 
    void borrowFromPrev(unsigned idx); 
    void borrowFromNext(unsigned idx);
    void merge(unsigned idx);
};
 
template<class T>
int btnode<T>::findKey(T k){
    unsigned idx=0;
    while (idx<this->m_num and m_data[idx]<k)
        ++idx;
    return idx;
}

template<class T>
void btnode<T>::remove(T k){
    unsigned idx = findKey(k);
 
    if (idx<this->m_num and m_data[idx] == k){
        if (this->m_leaf)   removeFromLeaf(idx);
        else    removeFromNonLeaf(idx);
    }
    else{
        if (this->m_leaf){
            cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }
 
        bool flag = ( (idx==this->m_num)? true : false );
        cout << flag << " ";

        if (m_child[idx]->m_num < m_min)  fill(idx);
 
        if (flag and idx>this->m_num)    this->m_child[idx-1]->remove(k);
        else    this->m_child[idx]->remove(k);
    }
    return;
}
 
template<class T>
void btnode<T>::removeFromLeaf (unsigned idx){
    for (unsigned i=idx+1; i<this->m_num; ++i)
        m_data[i-1] = m_data[i]; 
    this->m_num--;
    return;
}

template<class T>
void btnode<T>::removeFromNonLeaf(unsigned idx){ 
    T k = m_data[idx];

    if (this->m_child[idx]->m_num >= this->m_min){
        T pred = getPred(idx);
        m_data[idx] = pred;
        this->m_child[idx]->remove(pred);
    }
    else if  (this->m_child[idx+1]->m_num >= this->m_min){
        T succ = getSucc(idx);
        m_data[idx] = succ;
        this->m_child[idx+1]->remove(succ);
    }
 
    else{
        merge(idx);
        this->m_child[idx]->remove(k);
    }
    return;
}
 
template<class T>
T btnode<T>::getPred(unsigned idx){
    btnode<T> *cur = m_child[idx];
    while (!cur->m_leaf)
        cur = cur->m_child[cur->m_num];
 
    return cur->m_data[cur->m_num-1];
}

template<class T>
T btnode<T>::getSucc(unsigned idx){
    btnode<T> *cur = m_child[idx+1];
    while (!cur->m_leaf)
        cur = cur->m_child[0];
 
    return cur->m_data[0];
}

template<class T>
void btnode<T>::fill(unsigned idx){
    if (idx!=0 && m_child[idx-1]->m_num>=this->m_min)   borrowFromPrev(idx);
    else if (idx!=this->m_num and this->m_child[idx+1]->m_num>=m_min)  
        borrowFromNext(idx);
    else{
        if (idx != this->m_num)   merge(idx);
        else    merge(idx-1);
    }
    return;
}

template<class T>
void btnode<T>::borrowFromPrev(unsigned idx){
 
    btnode<T> *child = this->m_child[idx];
    btnode<T> *sibling = this->m_child[idx-1];
 
    for (int i=child->m_num-1; i>=0; --i)
        child->m_data[i+1] = child->m_data[i];
 
    if (!child->m_leaf){
        for(int i=child->m_num; i>=0; --i)
            child->m_child[i+1] = child->m_child[i];
    }
 
    child->m_data[0] = m_data[idx-1];
 
    if (!m_leaf)
        child->m_child[0] = sibling->m_child[sibling->m_num];
 
    m_data[idx-1] = sibling->m_data[sibling->m_num-1];
 
    child->m_num += 1;
    sibling->m_num -= 1;
 
    return;
}

template<class T>
void btnode<T>::borrowFromNext(unsigned idx){
 
    btnode<T> *child = this->m_child[idx];
    btnode<T> *sibling = this->m_child[idx+1];
 
    child->m_data[(child->m_num)] = m_data[idx];

    if (!(child->m_leaf))
        child->m_child[child->m_num+1] = sibling->m_child[0];
 
    m_data[idx] = sibling->m_data[0];
 
    for (unsigned i=1; i<sibling->m_num; ++i)
        sibling->m_data[i-1] = sibling->m_data[i];
 
    if (!sibling->m_leaf){
        for(unsigned i=1; i<=sibling->m_num; ++i)
            sibling->m_child[i-1] = sibling->m_child[i];
    }
 
    child->m_num += 1;
    sibling->m_num -= 1;
 
    return;
}

template<class T>
void btnode<T>::merge(unsigned idx){
    btnode<T> *child = m_child[idx];
    btnode<T> *sibling = m_child[idx+1];

    child->m_data[m_min-1] = m_data[idx];
 
    for (unsigned i=0; i<sibling->m_num; ++i)
        child->m_data[i+m_min] = sibling->m_data[i];
 
    if (!child->m_leaf){
        for(unsigned i=0; i<=sibling->m_num; ++i)
            child->m_child[i+m_min] = sibling->m_child[i];
    }

    for (unsigned i=idx+1; i<m_num; ++i)
        m_data[i-1] = m_data[i];

    for (unsigned i=idx+2; i<=m_num; ++i)
        m_child[i-1] = m_child[i];
 
    child->m_num += sibling->m_num+1;
    this->m_num--;

    delete(sibling);
    return;
}

template<class T>
void btnode<T>::insertNonFull(T k){
    int i = this->m_num-1;

    if (m_leaf == true){
        while (i >= 0 and m_data[i] > k){
            m_data[i+1] = m_data[i];
            i--;
        }
 
        m_data[i+1] = k;
        m_num = m_num+1;
    }
    else{
        while (i >= 0 and m_data[i] > k)
            i--;
    
        cout << "insert: " << i << endl;
        if (m_child[i+1]->m_num == 2*m_min-1){
            splitChild(i+1, m_child[i+1]);

            if (m_data[i+1] < k)  i++;
        }
        m_child[i+1]->insertNonFull(k);
    }
}
 
template<class T>
void btnode<T>::splitChild(int i, btnode<T> *y){
    btnode<T> *z = new btnode<T>(y->m_min, y->m_leaf);
    z->m_num = this->m_min - 1;
 
    for (unsigned j = 0; j < this->m_min-1; j++)
        z->m_data[j] = y->m_data[j+this->m_num];
 
    if (y->m_leaf == false){
        for (unsigned j = 0; j < this->m_min; j++)
            z->m_child[j] = y->m_child[j+this->m_min];
    }
 
    y->m_num = this->m_min - 1;
 
    for (int j = this->m_num; j >= i+1; j--)
        this->m_child[j+1] = this->m_child[j];
 
    this->m_child[i+1] = z;
 
    for (int j = this->m_num-1; j >= i; j--)
        m_data[j+1] = m_data[j];
 
    m_data[i] = y->m_data[this->m_min-1];
    this->m_num = this->m_num + 1;
}

template<class T>
void btnode<T>::traverse(){
    unsigned i;
    for (i = 0; i < this->m_num; i++){
        if (this->m_leaf == false)  this->m_child[i]->traverse();
        cout << " " << m_data[i];
    }
 
    if (this->m_leaf == false)
        this->m_child[i]->traverse();
}
 
template<class T>
btnode<T> *btnode<T>::search(T k){
    int i = 0;
    while (i < this->m_num and k > m_data[i])
        i++;
 
    if (m_data[i] == k)   return this;
    if (this->m_leaf == true)   return NULL;
 
    return this->m_child[i]->search(k);
}


template<class T>
class mbtree{
    btnode<T> *root;
    unsigned m_min;
public:
 
    mbtree(unsigned _min){
        root = NULL;
        this->m_min = _min;
    }
 
    void traverse(){
        if (root != NULL) root->traverse();
    }
 
    btnode<T>* search(T k){
        return (root == NULL)? NULL : root->search(k);
    }
 
    void insert(T);
    void remove(T);
 
};
 
template<class T>
void mbtree<T>::insert(T k){
    if (root == NULL){
        root = new btnode<T>(this->m_min, true);
        root->m_data[0] = k;
        root->m_num = 1;
    }
    else{
        if (root->m_num == 2*this->m_min-1){
            btnode<T> *s = new btnode<T>(this->m_min, false);
 
            s->m_child[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->m_data[0] < k) i++;
            s->m_child[i]->insertNonFull(k);
 
            this->root = s;
        }
        else
            this->root->insertNonFull(k);
    }
}

template<class T>
void mbtree<T>::remove(T k){
    if (!this->root){
        cout << "The tree is empty\n";
        return;
    }
 
    this->root->remove(k);
  
    if (this->root->m_num==0){
        btnode<T> *tmp = this->root;
        if (this->root->m_leaf) root = NULL;
        else    this->root = this->root->m_child[0];
 
        delete tmp;
    }
    return;
}