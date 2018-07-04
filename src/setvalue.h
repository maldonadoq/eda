#ifndef _SETVALUE_H_
#define _SETVALUE_H_

#include <iostream>
#include <vector>

#define NDATA 4				// number data node r-tree quad-tree
#define PRE 4				// precision cout
#define QDMIN 0.001			// división minima
#define RDIM 4				// r dimensionality
#define RM 2				// r number entries per node

#include "point.h"

using namespace std;

static double xmin, xmax, ymin, ymax;
static vector<qpoint> vpoints;
static vector<qpoint> vlines;
static string cardinal[4] = {"NW","NE","SW","SE"};	// cardinal

#endif