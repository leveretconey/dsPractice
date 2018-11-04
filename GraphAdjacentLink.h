#pragma once
#include "Graph.h"
class GraphAdjacentLink :
	public Graph
{

public:
	int CreateFromFile(char *file_path);

	/*
	void ShowVertexNeighbors(int vertex) ;
	void InsertVertex() ;
	void DeleteVertex(int vertex_to_delete) ;
	int AddEdge(int vertex_1, int vertex_2, int weight = 1);
	int RemoveEdge(int vertex_1, int vertex_2) ;
	int FirstNeighbor(int vertex) ;
	int NextNeighbor(int vertex, int last_neighbor) ;
	void Visited_Initialization() ;
	int VertexVisited(int vertex) ;
	int SetVisited(int vertex) ;*/

	int ExistEdge(int vertex_1, int vertex_2);

	GraphAdjacentLink();
	~GraphAdjacentLink();
protected:
	typedef struct EdgeNode
	{
		int target_vertex;
		int weight;
		EdgeNode *next_neighbor;
	}EdgeNode, *EdgeNodePointer;

	typedef struct VertexNode
	{
		int vertex_info;
		int visited;
		EdgeNode *first_neighbor;
	}VertexNode, *VertexNodePointer;
private:
	VertexNode vertex[MAX_VERTEX];
};

