/*
 * File: PathFinderGraph.h
 * ------------
 * Name: [Alex Maestro]
 * Section: [Also Leader here]
 * This file is the interface for a PathFinderGraph class that encapsulates
 * the idea of a path finder graph.
 */


#ifndef _pathfindergraph_h
#define _pathfindergraph_h

#include "graphtypes.h"
#include "graph.h"
#include "path.h"

/*
 * Implementation notes: PathFinderGraph SubClass
 * --------------------------------------
 * MY/NOTE1: just srarting to designing a Class, don't have any extra wanted
 * mehtods to add it.
 */

class PathFinderGraph : public Graph<Node, Arc> {
public:
/*
 * Constructor: PathFinderGraph
 * Usage: PathFinderGraph();
 * ----------------------------------
 * Creates an empty PathFinderGraph object.
 */
   PathFinderGraph();

/*
 * Destructor: ~PathFinderGraph
 * Usage: PathFinderGraph();
 * ----------------------------------
 * Frees internal storage allocated to represent a PathFinderGraph.
 */
   ~PathFinderGraph();


void storeMapImg(string img);
string getMapImg();

void setLastExecutAlgm(string lastAlgm);
string getLastExecutAlgm();



private:
	/* Instance variables */
	string image;		// map image for graph to archived.
	string algm;		// last executed algm.

	/* private methods */
	// for the moment i see no private data for PathFinderGraph.
	// Maybe:
	// - Map of all shortest paths, as AB --> A-B-C-D linked list, list of arcs
};

#endif