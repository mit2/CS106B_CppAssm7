/*
 * File: path.h
 * ------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the interface for a Path class that encapsulates
 * the idea of a multistep path.
 */

/////////////////////////////////////////////////////////////////////
// Your task in this part of the assignment is to design a Path    //
// class that supports the implementation of Dijkstra's algorithm. //
// As noted in the assignment handout, your class must meet the    //
// following conditions:                                           //
//                                                                 //
// 1. The class must not export any public instance variables.     //
//    All data required to store the path must be private to the   //
//    class.                                                       //
//                                                                 //
// 2. The method that returns the total cost of the path must      //
//    run in constant time.                                        //
//                                                                 //
// 3. The class must export a toString method that returns a       //
//    string composed of the nodes on the path separated by        //
//    arrows formed by the two-character sequence ->.              //
//                                                                 //
// 4. Any heap storage allocated by this class must be freed       //
//    when the object is deleted.                                  //
//                                                                 //
// Beyond those restrictions, you are free to design and implement //
// this class as you see fit.  You must, however, document your    //
// design decisions in the corresponding path.cpp file.            //
/////////////////////////////////////////////////////////////////////

#ifndef _path_h
#define _path_h

#include "stack.h"
#include "vector.h"
#include "graphtypes.h"
using namespace std;

class Path {

public:
/*
 * Constructor: Path
 * Usage: Path();
 * ----------------------------------
 * Creates an empty Path object.
 */
   Path();

/*
 * Destructor: ~Path
 * Usage: Path();
 * ----------------------------------
 * Frees internal storage allocated to represent a Path.
 */
   ~Path();

/*
 * Function: getPathCost
 * Usage: double cost = path.getPathCost();
 * ----------------------------------
 * Returns path's total cost as a sum of all edges in constant time.
 */
   double getPathCost();	// O(1)

/*
 * Function: addArc
 * Usage: path.addArc(arc);
 * ----------------------------------
 * Adds new segment/arc at the end of the path and increment total path's cost counter.
 */
   void addArc(Arc *arc);		// O(1)

/*
 * Function: removeArc
 * Usage: path.removeArc();
 * ----------------------------------
 * Removes segment/arc at the end of the path and decrement total path's cost counter.
 */
   void removeArc();		// O(1)

/*
 * Function: toString
 * Usage: path.toString();
 * ----------------------------------
 * Returns a string composed of the nodes on the path separated by arrows formed by the two-character sequence ->.
 */
   string toString();		// O(N)

 /*
 * Function: getLastEdge
 * Usage: path.getLastEdge();
 * ----------------------------------
 * Returns last segment in the path, without removing it.
 */  
   Arc *getLastEdge();		// O(1)
   

private:
	/* Instance variables */
	Stack<Arc *> path;
	Vector<Arc *> pathClone;	// path's copy in terms of vector, used only for path.toString() method.
	double totalCost;			// path's total cost.

};

#endif
