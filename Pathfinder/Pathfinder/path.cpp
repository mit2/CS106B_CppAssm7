/*
 * File: path.cpp
 * --------------
 * Name: [Alex Maestro]
 * Section: [Also Leader here]
 * This file implements the path.h interface.
 */

/////////////////////////////////////////////////////////////////////
// Your task in this part of the assignment is to write the code   //
// that implements your path.h interface.  For the benefit of      //
// future programmers who will need to work on this interface,     //
// you must also write an extended comment (presumably replacing   //
// this to-do box) that documents the design decisions you made    //
// in structuring the Path class as you did.                       //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "path.h"
#include "foreach.h"
#include "graphtypes.h"
#include "gpathfinder.h"
using namespace std;


/*
 * Implementation notes: Path
 * ----------------------------------------------
 * The only initialization requared at this level is creating am empty data 
 * structures, which is perfomed automaticaly by the underlying classes.
 * The destructor must free individual arcs structures.
 */

Path::Path(){
	totalCost = 0;
}
Path::~Path(){
	path.clear();
	pathClone.clear();
}

/*
 * Implementation notes: getPathCost
 * ----------------------------------------------
 * Just return value of total path's cost in O(1).
 */
double Path::getPathCost(){
	return totalCost;
}

/*
 * Implementation notes: addArc
 * ----------------------------------------------
 * Adds segment to the end of the path in O(1) --> why is Stack ADT used.
 * Adds segment to the end of the path in O(1) --> why is Vector ADT used as duplicate.
 */
void Path::addArc(Arc *arc){
	path.push(arc);
	pathClone.add(arc);
	totalCost = totalCost + arc->cost;
}

/*
 * Implementation notes: removeArc
 * ----------------------------------------------
 * Removes segment from the end of the path in O(1) --> why is Stack ADT used.
 * Removes segment from the end of the path in O(N) --> why is Vector ADT used as duplicate.		// OPTIMISE IT! BELLOW
 */
void Path::removeArc(){
	Arc *arc = path.pop();
	pathClone.removeAt(pathClone.size() - 1);		// maybe build pathClone when it needed toString() representation to avoid removeAt() in O(N)
	totalCost = totalCost - arc->cost;
}

/*
 * Implementation notes: getLastEdge
 * ----------------------------------------------
 * Returns last segment in the path, without removing it in O(1) --> why is Stack ADT used.
 */
Arc *Path::getLastEdge(){
	return path.peek();
}

/*
 * Implementation notes: displayPath
 * ----------------------------------------------
 * Highlight path's segments and display on the screen in O(N) --> why is Vector ADT used.
 * Will highlight and display any spanning tree path b/c in the Vector arc stored in sequence, and will redraw if nessesary the same node twice.
 * param 'color' -- handy if we want highlight path and return back to original color  later.
 */
void Path::displayPath(string color, string marker, string marker2){
	for(int i = 0; i < pathClone.size(); i ++){
		if(marker == "1stNodeClearAlso" && i == 0) drawPathfinderNode(pathClone[i]->start->loc, color, pathClone[i]->start->name);
		if(marker2 == "kruskal")drawPathfinderNode(pathClone[i]->start->loc, color, pathClone[i]->start->name);
		if(i != 0 || i != pathClone.size() - 1)drawPathfinderNode(pathClone[i]->finish->loc, color, pathClone[i]->finish->name);	// 1st and last node not highlight, as higlighted prev by user choice.
		drawPathfinderArc(pathClone[i]->start->loc, pathClone[i]->finish->loc, color);
	}
	repaintPathfinderDisplay();
	pathClear = pathClone;	
}

int Path::getSize(){
	return pathClone.size();
}

/*
 * Implementation notes: toString
 * ----------------------------------------------
 * Returns a string composed of the nodes on the path separated by arrows formed by the two-character sequence in O(N) --> why is Vector ADT used as duplicate
 * b/c it is easy iterate thru Vector, as Stack don't have an iterator.
 */
string Path::toString(){
	// consider the case to build intare pathClone from stack only here to avoid O(N) above in removeArc()
	string strPath = "";
	bool start = false; // marker for geting value for starting node.
	foreach(Arc *arc in pathClone){		
		if(start == false){
			strPath += arc->start->name; 
			start = true;
		}
		strPath += " --> " + arc->finish->name;
	}
	cout << endl;
	return strPath;
}

