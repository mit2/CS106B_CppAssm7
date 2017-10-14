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

void storeHighlightedPath(Path path);


void clearHighlightedPath();
   

private:
	/* Instance variables */
	Path choosenPath;	// most recent path displayed by using Dijkstra and Kruskal Algm buttons.

	/* private methods */
	// for the moment i see no private data for PathFinderGraph.
	// Maybe:
	// - Map of all shortest paths, as AB --> A-B-C-D linked list, list of arcs
};

#endif