#pragma once
#include "Graph.h"
class GraphMatrix :
	public Graph
{
public:
	static const int DEPTH_FIRST_NO_RECURSION = 3;
	static const int DEPTH_FIRST_NO_RECURSION_V2 = 4;

	int CreateFromFile(char *file_path);
	GraphMatrix *Copy();
	int ExistEdge(int vertex_1, int vertex_2);
	void ShowVertexNeighbors(int vertex);
	void InsertVertex();
	void DeleteVertex(int vertex_to_delete);
	int AddEdge(int vertex_1, int vertex_2, int weight = 1);
	int RemoveEdge(int vertex_1, int vertex_2);
	int FirstNeighbor(int vertex);
	int NextNeighbor(int vertex, int last_neighbor);
	static int ShowVertex(GraphMatrix *graph,int vertex);
	int Degree(int vertex);
	int Degree(int vertex,int type);


	int ShowAllVertex(int order);
	int Traverse(int order, int(*visit)(GraphMatrix *,int));
	int BFTraverse(int(*visit)(GraphMatrix *, int));
	int DFTraverse(int(*visit)(GraphMatrix *, int));
	int DFNoRecursionTraverse(int(*visit)(GraphMatrix *, int));
	int DFNoRecursionTraverseV2(int(*visit)(GraphMatrix *, int));
	int BFSingleOriginShortestDistance(int origin);
	int DijkstraShortestPath(int vertex);
	int FloydShortestPath();
	int TopologicalSorting();
	int DFSTopologicalSorting();

	void Visited_Initialization();
	int VertexVisited(int vertex);
	int SetVisited(int vertex);
	int GetVertexInfo(int vertex);
	GraphMatrix();
	~GraphMatrix();
protected:
	int edge[MAX_VERTEX][MAX_VERTEX];
	int vertex_info[MAX_VERTEX];
	int vertex_visted[MAX_VERTEX];

	int DFTraverseRecursion(int vertex_visiting, int(*visit)(GraphMatrix *, int));
};

