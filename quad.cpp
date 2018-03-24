#include <iostream>
#include "src/quadtree.h"

using namespace std;

#define T double
#define D string

typedef quadtree<T,D>	qtree;
typedef cnode<D>		node;

int main(int argc, char const *argv[]){
	//qtree test(cpoint(-90,-200), cpoint(90,200),DM);
	qtree test(cpoint(41.6,-88), cpoint(42.1,-87.3),DM);
	
	test.rdfile("data/crime.csv");
	test.qtprint();		//print all data
	//test.qtmax();		//print x[] and y[] to draw point
	node *r = test.find(cpoint(41.996260753597305,-87.67036581294042));
	if(!r)	cout << "NULL" << endl;
	//else	(*r).printxy();		//point in this quad find
	else	cout << *r << endl;

	return 0;
}