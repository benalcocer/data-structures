/// @author Benjamin Alcocer
/// @file main.cpp
/// @version 2019-11-25
/// @brief This program is written for Assignment 8: Rick Discovers Wormholes
/// This program uses a graph data structure. CS302.

#include <iostream>
#include <fstream>
#include <string>
#include "vertex.h"

using namespace std;

struct wormhole
{
    int destStar;
    int duration;
};

// Function Prototype
bool dfs(int curr, vertex<wormhole> *adjList, bool *visited, int weight = 0);

/// ----------------------------------------------------------------------------
/// Main entry point for this application.
/// ----------------------------------------------------------------------------
int main()
{
    int cases;              // otherwise known as c
    int numSystems;         // n, where n = [1, 1000], numbered 0 -> (n - 1)
    int numWormHoles;       // m, where m = [0, 2000]
    int x, y, t;            // x & y star system, t time in years [-1000, 1000]

    ifstream inFile;        // input file stream variable
    string fileName;        // string to indicate the file to be opened

    // Attempt to open file from user inputted file name
    cout << "Time to load data into the portal device: ";
    cin >> fileName;
    cout << endl;

    inFile.open(fileName);
    if (!inFile.is_open())
    {
        cerr << "File \"" << fileName << "\" failed to open.\n";
        cerr << "\n\"Looks like Morty picked the wrong data file to load into";
        cerr << " the portal gun.\"" << endl;
        return EXIT_FAILURE;
    }

    // Read in the amount of cases and begin processing
    inFile >> cases;
    for (int i = 0; i < cases; i++)
    {
        wormhole hole;  // temporary wormhole used to addEdge() to graph

        inFile >> numSystems >> numWormHoles;

        // Initialize the star systems
        vertex<wormhole> *stars = new vertex<wormhole>[numSystems];

        // Add edges
        for (int j = 0; j < numWormHoles; j++)
        {
            inFile >> x >> y >> t;

            hole.destStar = y;
            hole.duration = t;

            // add a new "y" destination to "x" starSystem with "t" duration
            stars[x].addEdge(hole);
        }

        // DFS to determine if time travel is possible for Rick Sanchez
        bool *visited = new bool[numSystems];
        bool isPossible = false;

        // initilize visited boolean array to false
        for (int k = 0; k < numSystems; k++)
        {
            visited[k] = false;
        }

        for (int x = 0; x < numSystems; x++)
        {
            // Call dfs on every star system "x" to find every path.
            // As soon as a negative cycle is found, break and output that it
            // is possible.
            if (dfs(x, stars, visited))
            {
                isPossible = true;
                break;
            }
        }

        if (isPossible)
        {
            cout << "Possible" << endl;
        }
        else
        {
            cout << "Not Possible" << endl;
        }

        delete [] stars;
        delete [] visited;
    }

    inFile.close();
    return EXIT_SUCCESS;
}

///-----------------------------------------------------------------------------
/// @brief dfs(): This function executes the depth-first-search algorithm on
/// the adjList. Its purpose is to find a negative cycle in the graph.
/// A negative cycle in this program indicates time travel to the past to enable
/// Rick Sanchez to cycle back to the time of the Big Bang.
///
/// @param curr         // current star system
/// @param adjList      // The graph's adjList
/// @param visited      // boolean array containing visited verticies
/// @param weight       // integer holding the current path's weight
///
/// @return A boolean indicating if time travel to the past is possible
///-----------------------------------------------------------------------------
bool dfs(int curr, vertex<wormhole> *adjList, bool *visited, int weight)
{
    // if a current wormhole has been visited already, a potential negative
    // cycle exists
    if (visited[curr])
    {
        return weight < 0;
    }

    visited[curr] = true;

    // declare iterators
    vertex<wormhole>::edgeIterator it = adjList[curr].begin();
    vertex<wormhole>::edgeIterator theEnd(NULL);

    // recursively call DFS looking for a possibility of time travel
    for (it; it != theEnd; it++)
    {
        if (dfs((*it).destStar, adjList, visited, (*it).duration + weight))
        {
            return true;
        }
    }

    visited[curr] = false;
    return false;
}
