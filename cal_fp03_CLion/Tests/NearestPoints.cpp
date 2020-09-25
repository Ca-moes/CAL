/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {
	Result res;

	for (int i = 0; i < vp.size(); ++i) {
        for (int j = i+1; j < vp.size(); ++j) {
            if (vp.at(i).distance(vp.at(j)) < res.dmin) {
                res = Result(vp.at(i).distance(vp.at(j)), vp.at(i), vp.at(j));
            }
        }
    }

	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	Result res;
	sortByX(vp, 0, vp.size()-1);

    for (int i = 0; i < vp.size(); ++i) {
        for (int j = i+1; j < vp.size(); ++j) {
            if (vp.at(i).distance(vp.at(j)) < res.dmin) {
                res = Result(vp.at(i).distance(vp.at(j)), vp.at(i), vp.at(j));
            }
        }
    }

	return res;
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res)
{
    // left = indice do ponto mais á esquerda dentro da faixa
    // right = indice do ponto mais á direita dentro da faixa
	// TODO
    for (int i = left; i <= right; ++i) {
        for (int j = i+1; j <= right; ++j) {
            if (vp.at(i).distance(vp.at(j)) < res.dmin) {
                res = Result(vp.at(i).distance(vp.at(j)), vp.at(i), vp.at(j));
            }
        }
    }

}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
	// Base case of two points
	if (abs(left-right) == 1)
	    return Result(vp.at(left).distance(vp.at(right)), vp.at(left), vp.at(right));
	// Base case of a single point: no solution, so distance is MAX_DOUBLE
	if (abs(left-right) == 0)
	    return Result(MAX_DOUBLE, vp[left], vp[right]);
	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
    int half = floor((left + right) / 2.0);
    np_DC(vp, left, half, numThreads);
    np_DC(vp, half+1, right, numThreads);
	// Select the best solution from left and right
	// TODO

	// Determine the strip area around middle point
	// TODO

	// Order points in strip area by Y coordinate
	// TODO

	// Calculate nearest points in strip area (using npByY function)
	// TODO

	// Reorder points in strip area back by X coordinate
	//TODO

	return Result(1, vp[0], vp[1]);
}


/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num)
{
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, 1);
}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
