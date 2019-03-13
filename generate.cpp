#include <iostream>
#include <random>

using namespace std;

int main(int argc, char const *argv[]){
	srand(time(NULL));
	unsigned dim = 50, record = 100;

	for(unsigned i=0; i<record; i++){
		for(unsigned j=0; j<dim; j++)
			cout << GetRandom(2100, -100) << " ";
			//cout << dist(rng) << " ";	
			//cout << (double)rand()/(double)RAND_MAX << " ";
		cout << endl;
	}
	return 0;
}