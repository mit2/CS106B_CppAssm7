
/*
 * Implementation notes: populateGraphFromDataFile
 * ----------------------------------------------
 * This function simply populate graph with Nodes and Arcs from wanted data file.
 * As by nature iteratively get line and scann this line by words will produce algm with O(nº2) complexity
 * was choosen algm with less complex data structures to save memory space. Originaly was designend 3 algms.
 */
/*
bool populateGraphFromDataFile(PathFinderGraph & graph){
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
						// populate node															// FINISH HERE
						cout << "d0:"<<data[0] << " d1:"<<data[1] << " d2:" <<data[2]<<endl;
						Node *node = new Node;
						node->name = data[0];
						GPoint loc(stringToReal(data[1] + ".0"), stringToReal(data[2] + ".0"));
						node->loc = loc;
						graph.addNode(node);
						i = 0;
					}
				}else if(mark == "Arc"){
					data[i++] = token;
					if(i == 3){
						// populate arc  // forward direction										// FINISH HERE
						Node *nodeStart = graph.getNode(data[0]);
						Node *nodeFinish = graph.getNode(data[1]);
						Arc *arc = new Arc;
						arc->start = nodeStart;
						arc->finish = nodeFinish;
						arc->cost = stringToReal(data[3] + ".0");
						graph.addArc(arc);

						populate arc data[1], data[0], strToDouble(data[3]) // backward direction	// FINISH HERE
						graph.addArc(arc);
						i = 0;
					}
				}
			}
		}
	}
	
	return true;
	
}

if(graph.getNodeSet().size() == countNodes)
		cout << "Cool";
*/