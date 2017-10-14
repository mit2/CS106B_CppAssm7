/*
 * File: Pathfinder.cpp
 * --------------------
 * Name: [TODO: enter name here] Alex Lavrenso
 * Section: [TODO: enter section leader here] No leader
 * This file is the starter project for the Pathfinder application
 * on Assignment #6.
 */
 
// [TODO: complete this implementation]

#include <iostream>
#include <fstream>
#include <string>
#include "console.h"
#include "graphtypes.h"
#include "gpathfinder.h"
#include "tokenscanner.h"
#include "PathFinderGraph.h"
#include "strlib.h"
#include "foreach.h"
#include "pqueue.h"
#include "path.h"
using namespace std;

/* Function prototypes */

void quitAction();
bool populateGraphFromDataFile(PathFinderGraph & graph);
void displayMap(PathFinderGraph & graph);
Path findShortestPath(Node *start, Node *finish);	// Dijkstra Algm
double getPathCost(const Vector<Arc *> & path);
Node *selectNode(PathFinderGraph graph);
void runDijkstra(PathFinderGraph & graph);
void runKruskal(PathFinderGraph & graph);
string promtUserForFile(ifstream &infile, string promt = "");

/* Main program */
/* Program outline */
   //1. Create internal graph from file.txt data param
   //2. Display graph
   //3. Add buttons to the control strip. Add, implement callback funcs for buttons to have wanted behavior.
   //4. Intergrate adapted Dijkstra Algm code into this program. Shortest Path whose arc have minim total cost.
   //5. Design & integrate Path Class. Integrate into Dijkstra code.
   //6. Implement Kruskal's Algm for finding minim spanning tree.

int main() {
   PathFinderGraph graph;
   initPathfinderGraphics();   
   addButton("Map", displayMap, graph);															// NEW CODING HERE	ok
   addButton("Dijkstra", runDijkstra, graph);
   addButton("Kruskal", runKruskal, graph);
   addButton("Quit", quitAction);


   pathfinderEventLoop();
   
   return 0;
}

/*
 * Implementation notes: promtUserForFile
 * ----------------------------------------------
 * This function ask user to provide legal graph data file. Used as a ready Stanford Lib function here.
 */
string promtUserForFile(ifstream &infile, string promt){
	while(true){
		cout << promt;
		string filename;
		getline(cin, filename);
		infile.open(filename.c_str());
		if(!infile.fail()) return filename;
		infile.clear();
		cout << "Unable to open that file. Try againe." << endl;
		if(promt == "") promt = "Input file: ";
	}
}

/*
 * Implementation notes: populateGraphFromDataFile
 * ----------------------------------------------
 * This function simply populate graph with Nodes and Arcs from wanted data file.
 * As by nature iteratively get line and scann this line by words will produce algm with O(nº2) complexity
 * was choosen algm with less complex data structures to save memory space. Originaly was designend 3 algms.
 */
bool populateGraphFromDataFile(PathFinderGraph & graph){
	Vector <string> nodesFromDataFile;
	int i = 0;		// simple counter.
	string data[3];	// 3 space array to store data for node or arc
	string mark;	// just data marker.
	string line;	// line from file to be tokenized.
	bool mapNotSet = true; // marker that is bg image for graph is not set.
	ifstream infile;	
	TokenScanner scanner;
	promtUserForFile(infile, "Please enter the name of graph data file: ");
	while(getline(infile, line)){
		if(mapNotSet){			
				drawPathfinderMap(line);															// FINISH HERE	OK	
				mapNotSet = false;
			}
		scanner.setInput(line);
		scanner.ignoreWhitespace();
		while(scanner.hasMoreTokens()){
			string token = scanner.nextToken();			
			if(token == "NODES") mark = "Node";
			else if(token == "ARCS") mark = "Arc";
			else{
				if(mark == "Node"){
					data[i++] = token;
					if(i == 3){
						// populate node															// FINISH HERE	OK					
						Node *node = new Node;
						node->name = data[0];
						GPoint loc(stringToReal(data[1]), stringToReal(data[2]));
						node->color = NODE_COLOR;
						node->loc = loc;
						graph.addNode(node);
						i = 0;
					}
				}else if(mark == "Arc"){
					data[i++] = token;
					if(i == 3){
						// populate arc  // forward direction										// FINISH HERE	OK
						/*cout << "d0:"<<data[0] << " d1:"<<data[1] << " d2:" <<data[2]<<endl;*/
						Node *nodeStart = graph.getNode(data[0]);
						Node *nodeFinish = graph.getNode(data[1]);
						Arc *arc = new Arc;
						arc->start = nodeStart;
						arc->finish = nodeFinish;
						arc->cost = stringToReal(data[2]);
						arc->color = ARC_COLOR;
						graph.addArc(arc);
						nodesFromDataFile.add(data[0]);
						nodesFromDataFile.add(data[1]);

						// populate arc  // backward direction										// FINISH HERE	OK
						Node *nodeStart_ = graph.getNode(data[1]);
						Node *nodeFinish_ = graph.getNode(data[0]);
						Arc *arcbkw = new Arc;
						arcbkw->start = nodeStart_;
						arcbkw->finish = nodeFinish_;
						arcbkw->cost = stringToReal(data[2]);
						arcbkw->color = ARC_COLOR;
						graph.addArc(arcbkw);
						nodesFromDataFile.add(data[1]);
						nodesFromDataFile.add(data[0]);
						i = 0;
					}
				}
			}
		}
	}
	
	// Do graph checkup.
	//Returns true if the graph contains an arc from n1 to n2.										// FINISH HERE	OK
	//iterate thru vector of arcs as nodes in sequence, where node[i] is ArcStart nad node[++i] is ArcFinish
	for(int i = 0; i < nodesFromDataFile.size(); i = i + 2){
		//cout << nodesFromDataFile.get(i) << "-->" << nodesFromDataFile.get(i + 1)<<endl;
		if(graph.isConnected(nodesFromDataFile.get(i), nodesFromDataFile.get(i + 1)))
			continue;
		else 
			error("Graph creation Error!");
	}
	// populate node outgoing arcs
	foreach (Node *node in graph.getNodeSet()){
		node->arcs = graph.getArcSet(node);
	}

	cout << "Graph is populated Successfully!";
	// if test isConnected() is passed, then return true
	return true;	
}

/*
 * Implementation notes: displayMap
 * ----------------------------------------------
 * This function simply display map on the screen using previousely populated internal graph.
 * For the moment don't see any special drawing capabilities.
 * MY/NOTE: After, when some algm as Dijkstra executed, just update nodes & arcs color and call again
 * displayMap() AND HIGLIHTED PATH WILL BE VISIBLE.
 * MY/NOTE2: Or implement drawPath() in Path Class to highlight the finded path.
 */
void displayMap(PathFinderGraph & graph){
	// if(graph exist) delete previouse instance, ~PathFinderGraph();

	// populate graph
	populateGraphFromDataFile(graph);
	// display map
	foreach (Node *node in graph.getNodeSet())
		drawPathfinderNode(node->loc, node->color, node->name);

	foreach (Arc *arc in graph.getArcSet())
		drawPathfinderArc(arc->start->loc, arc->finish->loc, arc->color);
	
	repaintPathfinderDisplay();
	cout << "Map is created Successfully!" <<endl;	
}

/*
 * Implementation notes: runDijkstra
 * ----------------------------------------------
 * This function run Dijkstra Algm. O(N^2)
 */
void runDijkstra(PathFinderGraph & graph){
	graph.clearHighlightedPath();
	Set<Node *> nodes = graph.getNodeSet();
	// define min, max range for Node X and Y according to NODE_RADIUS
	double minY = 0;
	double maxY = 0;
	double minX = 0;
	double maxX = 0;
	Node *endPoints[2]; // start and finish end points holder.
	bool select;
	// promt user for strating node, use mouseClick get location,	GPoint getMouseClick();								// NEW CODING HERE
	cout << "Select Starting Location: " <<endl;
	// two cycles loop to choose only 2 end points.
	for(int i = 0; i < 2; i++){ // O(N)
		select = true;
		if(i == 1) cout << "Select Finish Location: " <<endl;
		while(select){	// O(N)
			GPoint userClick = getMouseClick();
			foreach (Node *node in graph.getNodeSet()){
				minX = node->loc.getX() - NODE_RADIUS;
				maxX = node->loc.getX() + NODE_RADIUS;

				minY = node->loc.getY() - NODE_RADIUS;
				maxY = node->loc.getY() + NODE_RADIUS;
				// check if the user clickAction in Node NODE_RADIUS range to highlight the Node in the Map.
				if(minX <= userClick.getX() && userClick.getX() <= maxX && minY <= userClick.getY() && userClick.getY() <= maxY){
					cout << "	SELECTED POINT: " << node->name << endl;
					//highlight the node, change internal node data structure color -- NOT USED FOR NOW
					//update color node on the map
					drawPathfinderNode(node->loc, HIGHLIGHT_COLOR, node->name);
					repaintPathfinderDisplay();
					endPoints[i] = node;
					select = false;
					break; // stop searching
				}
				
			}			
			if(select != false) cout << "	Wrong! Choose correct city location: " <<endl;		
		}
	}

	Path path = findShortestPath(endPoints[0], endPoints[1]);	
	path.displayPath(HIGHLIGHT_COLOR, "");
	cout << path.toString();
	cout << " " << path.getPathCost() << endl;
	cout << "OK Dijkstra" <<endl;

	graph.storeHighlightedPath(path);
}

/*
 * Implementation notes: runKruskal
 * ----------------------------------------------
 * This function run Kruskal Algm.
 */
void runKruskal(PathFinderGraph & graph){
	/*Empty*/
	cout << "ok Kruskal" <<endl;
}

/*
 * Implementation notes: findShortestPath
 * ----------------------------------------------
 * This function run Dijkstra Algm: 
 * Explore all paths from the starting node in order of increasing total path
 * cost until you encounter a path that takes you to your destination. This path must be
 * the best one, because you have already explored all paths beginning at the starting
 * node that have a lower cost.
 */
Path findShortestPath(Node *start, Node *finish){
	Path path;
	PriorityQueue<Path> queue;
	Map<string, double> fixed;
	while(start != finish){
		if(!fixed.containsKey(start->name)){
			fixed.put(start->name, path.getPathCost());															// NEW CODING HERE replace getPathCost with path.getPathCost() -> O(1)
			foreach(Arc *arc in start->arcs){						
				if(!fixed.containsKey(arc->finish->name)){
					path.addArc(arc);
					queue.enqueue(path, path.getPathCost());														// NEW CODING HERE replace getPathCost with path.getPathCost() -> O(1)
					path.removeArc();
				}
			}
		}
		if(queue.isEmpty()){
			path.~Path();
			return path;
		}
		path = queue.dequeue();
		start = path.getLastEdge()->finish;
	}
	return path;
}

/*
 * Implementation notes: getPathCost
 * ----------------------------------------------
 * This function returns the total of the path, which is just the sum of the costs of the arcs.
 */
double getPathCost(const Vector<Arc *> & path){
	double cost = 0;
	foreach(Arc *arc in path){
		cost += arc->cost;
	}
	return cost;
}

/*
 * Implementation notes: selectNode
 * ----------------------------------------------
 * This function check if user point write city location on the map.
 * Use mouseClick get location,	GPoint getMouseClick();
 * MY/NOTE: CAN'T FIX IT, RETURN BAD POINTER?!
 */
Node *selectNode(PathFinderGraph graph){
	Set<Node *> nodes = graph.getNodeSet();
	// define min, max range for Node X and Y according to NODE_RADIUS
	double minY = 0;
	double maxY = 0;
	double minX = 0;
	double maxX = 0;
	while(true){
		GPoint userClick = getMouseClick();
		foreach (Node *node in graph.getNodeSet()){
			minX = node->loc.getX() - NODE_RADIUS;
			maxX = node->loc.getX() + NODE_RADIUS;

			minY = node->loc.getY() - NODE_RADIUS;
			maxY = node->loc.getY() + NODE_RADIUS;
			// check if the user clickAction in Node NODE_RADIUS range to highlight the Node in the Map.
			if(minX <= userClick.getX() && userClick.getX() <= maxX && minY <= userClick.getY() && userClick.getY() <= maxY){
				cout << "	SELECTED POINT: " << node->name << endl;
				//highlight the node, change internal node data structure color -- NOT USED FOR NOW
				//update color node on the map
				drawPathfinderNode(node->loc, HIGHLIGHT_COLOR, node->name);
				repaintPathfinderDisplay();
				//return graph.getNode(node->name); // stop searching
				return node;
			}
			
		}
		cout << "	Wrong! Choose correct city location: " <<endl;		
	}
}
/* Sample callback function */

void quitAction() {
   exit(0);
}
