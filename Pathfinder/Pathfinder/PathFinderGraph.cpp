/*
 * File: PathFinderGraph.cpp
 * --------------
 * Name: [Alex Maestro]
 * Section: [Also Leader here]
 * This file implements the PathFinderGraph.h interface.
 */

#include "PathFinderGraph.h"
#include "gpathfinder.h"
#include "path.h"
using namespace std;


/*
 * Implementation notes: PathFinderGraph
 * ----------------------------------------------
 * The only initialization requared at this level is creating am empty data 
 * structures, which is perfomed automaticaly by the underlying classes.
 * The destructor must free individual nodes and arcs structures.
 */

PathFinderGraph::PathFinderGraph(){
}
PathFinderGraph::~PathFinderGraph(){
	clear();
}



void PathFinderGraph::storeMapImg(string img){
	image = img;
}


string PathFinderGraph::getMapImg(){
	return image;
}

void PathFinderGraph::setLastExecutAlgm(string lastAlgm){
	algm = lastAlgm;
}
string PathFinderGraph::getLastExecutAlgm(){
	return algm;
}


