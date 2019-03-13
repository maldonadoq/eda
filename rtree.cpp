#include <iostream>
#include "src/setvalue.h"
#include "src/rtree.h"

using namespace std;

#define point_t double
#define data_t string

typedef rpoint<point_t> 		point;
typedef rdata<point_t, data_t>	data;
typedef rnode<point_t, data_t>	node;
typedef rtree<point_t, data_t>	tree;

int main(int argc, char const *argv[]){
	unsigned nd = RDIM, M=RM;
	tree *test = new tree(nd,M,0,1);

	test->insert(new data(point(nd), "A"));
	test->insert(new data(point(nd), "B"));
	test->insert(new data(point(nd), "C"));
	test->insert(new data(point(nd), "D"));
	test->insert(new data(point(nd), "E"));
	//test->insert(new data(point(nd), "F"));

	delete test;
	return 0;
}