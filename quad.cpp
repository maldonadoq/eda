#include <iostream>
#include "src/quadtree.h"
#include "src/data.h"

using namespace std;

#define T int
#define D 0

typedef quadtree<T,D>	qtree;
typedef cnode<T,D>		node;

int main(int argc, char const *argv[]){
	qtree center(cpoint(0,0), cpoint(8,8));
	node a(cpoint(1,1), 34);	node b(cpoint(2,5), 2);
    node c(cpoint(8,7), 8);		node d(cpoint(9,8), 12);
    node e(cpoint(7,9), 5);		node f(cpoint(0,11), 6);

	center.insert(&a);	center.insert(&b);
	center.insert(&c);	center.insert(&d);
	center.insert(&e);	center.insert(&f);

	cout << center.find(cpoint(8,7))->m_data << endl;

	return 0;
}