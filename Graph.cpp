#include "Graph.h"



Graph::Graph()
{
	count_edge = 0;
}


Graph::~Graph()
{
}

int Graph::VertexLegal(int vertex)
{
	return vertex > 0 && vertex <= count_vertex;
}

int Graph::VertexLegal(int vertex_1, int vertex_2)
{
	return VertexLegal(vertex_1) && VertexLegal(vertex_2);
}
