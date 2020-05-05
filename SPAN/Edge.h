//==============================================================================================
// Edge.h
//
// This header file simply defines an edge, which connects two vertices together with a weight.
// This struct is inside its own file because it is shared between both the Prim and Kruskal
// algorithms.
//
// Author:     Nicholas Nassar, University of Toledo
// Class:      EECS 2510-001 Non-Linear Data Structures, Spring 2020
// Instructor: Dr.Thomas
// Date:       May 5, 2020
// Copyright:  Copyright 2020 by Nicholas Nassar. All rights reserved.

#pragma once
struct edge
{
	unsigned int u;	// The index of the vertice representing the first vertex of the edge.
	unsigned int v;	// The index of the vertice representing the second vertex of the edge.
	double weight;	// The weight between the vertices u and v.
};