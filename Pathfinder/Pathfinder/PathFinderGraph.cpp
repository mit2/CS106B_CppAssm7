/*
 * File: PathFinderGraph.cpp
 * --------------
 * Name: [Alex Maestro]
 * Section: [Also Leader here]
 * This file implements the PathFinderGraph.h interface.
 */

#include "PathFinderGraph.h"
#include "gpathfinder.h"
using namespace std;


/*
 * Implementation notes: PathFinderGraph
 * ----------------------------------------------
 * The only initialization requared at this level is creating am empty data 
 * structures, which is perfomed automaticaly by the underlying classes.
 * The destructor must free individual nodes and arcs structures.
 */

PathFinderGraph::PathFinderGraph(){
	/* Empty */
}
PathFinderGraph::~PathFinderGraph(){
	// implement here
}



void PathFinderGraph::storeHighlightedPath(Path path){
	choosenPath = path;
}


void PathFinderGraph::clearHighlightedPath(){
	choosenPath.displayPath(ARC_COLOR, "1stNodeClearAlso");
}