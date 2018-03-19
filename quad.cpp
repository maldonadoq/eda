#include <iostream>
#include "src/quadtree.h"

using namespace std;

#define T double
#define D string
#define MI -180
#define MX 180
#define DM 20

typedef quadtree<T,D>	qtree;
typedef cnode<D>		node;

int main(int argc, char const *argv[]){
	qtree test(cpoint(MI,MI), cpoint(MX,MX),DM);
	
	test.rdfile("data/tdata.csv");	
	test.qtprint();
	/*node *r = test.find(cpoint(31.7666666667,35.233333));
	if(!r)	cout << "NULL" << endl;
	else	cout << *r << endl;*/

	return 0;
}