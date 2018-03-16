#ifndef _DATA_H_
#define _DATA_H_

class cpoint{
public:
	double x,y;
	cpoint(){	
		this->x = 0;
		this->y = 0;	
	}
	cpoint(double _x, double _y){
		this->x = _x;
		this->y = _y;
	}
	~cpoint(){	};
};

#endif