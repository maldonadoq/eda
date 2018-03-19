#include <iostream>
#include <fstream>
#include "octree/octree.h"

using namespace std;


/*template<class N, N _d>
void rdfile(string filename){
	ifstream file(filename);
	string lat,lon;
	if(!file.is_open()){
		cout << "error! cvs wrong!!" << endl;
		return;
	}

	while(file.good()){
		getline(file,lat,',');
		getline(file,lon,'\n');
		cout << lat << " " << lon << endl;
	}

	file.close();
}*/


int main(int argc, char const *argv[]){
	Octree<double> o(4096); //Create 4096x4096x4096 octree containing doubles.
    o(1,2,3) = 3.1416;
    o(1,1,9) = 3;
    o(1,5,5) = 34;
    o(1,27,7) = 6;
    cout << o.at(1,2,7) << endl;
	return 0;
}
