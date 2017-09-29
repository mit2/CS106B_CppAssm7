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
#include <string>
#include "console.h"
#include "graphtypes.h"
#include "gpathfinder.h"
using namespace std;

/* Function prototypes */

void quitAction();

/* Main program */
/* Program outline */
   //1. Create internal graph from file.txt data param
   //2. Display graph
   //3. Add buttons to the control strip. Add, implement callback funcs for buttons to have wanted behavior.
   //4. Intergrate adapted Dijkstra Algm code into this program. Shortest Path whose arc have minim total cost.
   //5. Design & integrate Path Class. Integrate into Dijkstra code.
   //6. Implement Kruskal's Algm for finding minim spanning tree.

int main() {
   initPathfinderGraphics();
   addButton("Quit", quitAction);
   pathfinderEventLoop();
   
   return 0;
}

/* Sample callback function */

void quitAction() {
   exit(0);
}
