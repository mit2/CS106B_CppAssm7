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
	redraw = false;
}
PathFinderGraph::~PathFinderGraph(){
	// implement here
}



void PathFinderGraph::storeHighlightedPath(Path path){
	choosenPath = path;
}


void PathFinderGraph::clearHighlightedPath(){
	choosenPath.displayPath(ARC_COLOR, "1stNodeClearAlso", "");
}

void PathFinderGraph::setLastExecutedAlgm(string algmName){
	algm = algmName;
}

string PathFinderGraph::getLastExecutedAlgm(){
	return algm;
}

void PathFinderGraph::storeMapImg(string img){
	image = img;
}


string PathFinderGraph::getMapImg(){
	return image;
}

void PathFinderGraph::clearAll(PathFinderGraph & graph){
	graph.clear();
	choosenPath.~Path();
}

void PathFinderGraph::setRedraw(bool flag){
	redraw = flag;
}
bool PathFinderGraph::getRedraw(){
	return redraw;
}

int PathFinderGraph::getchoosenPathSize(){
	return choosenPath.getSize();
}
