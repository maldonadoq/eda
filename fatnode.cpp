#include <iostream>
#include "src/bytree.h"

using namespace std;

template<class T>
class cm{
public:
	inline bool operator()(T x, T y){	return x<y;	}
};

typedef int					K;
typedef int					D;
typedef mbytree<K,D,cm<D>>	TR;

int main(int argc, char const *argv[]){
	TR *tmp = new TR();

	tmp->insert(1,1);	// v 1
	tmp->insert(2,3);	// v 2
	tmp->insert(3,8);	// v 3
	tmp->insert(5,6);	// v 4
	tmp->remove(5);		// v 5
	tmp->remove(3);		// v 6
	tmp->remove(2);		// v 7
	tmp->remove(1);		// v 8
	tmp->insert(5,6);	// v 9
	
	tmp->version(1);
	tmp->version(2);	
	tmp->version(3);
	tmp->version(4);
	tmp->version(5);
	tmp->version(6);	
	tmp->version(7);
	tmp->version(8);
	tmp->version(9);

	delete tmp;
	return 0;
}