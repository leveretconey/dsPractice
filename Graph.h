#pragma once
class Graph
{
public:
	static const int MAX_VERTEX = 100;
	static const int TYPE_DIRECTED=1;
	static const int TYPE_UNDIRECTED = 2;
	static const int BROAD_FIRST = 1;
	static const int DEPTH_FIRST = 2;
	static const int NULL_EDGE1 = 0;
	static const int NULL_EDGE2 = 0x3f3f3f3f;

	int VertexLegal(int vertex);
	int VertexLegal(int vertex_1,int vertex_2);

	virtual int ExistEdge(int vertex_1,int vertex_2) = 0;
	virtual void ShowVertexNeighbors(int vertex)=0;
	virtual void InsertVertex() = 0;
	virtual void DeleteVertex(int vertex_to_delete) = 0;
	virtual int AddEdge(int vertex_1, int vertex_2, int weight = 1) = 0;
	virtual int RemoveEdge(int vertex_1, int vertex_2) = 0;
	virtual int FirstNeighbor(int vertex) = 0;
	virtual int NextNeighbor(int vertex,int last_neighbor) = 0;
	virtual int Degree(int vertex)=0;
	static const int IN_DEGREE = 1;
	static const int OUT_DEGREE = 2;
	virtual int Degree(int vertex,int type) = 0;

	virtual void Visited_Initialization()=0;
	virtual int VertexVisited(int vertex) = 0;
	virtual int SetVisited(int vertex) = 0;

	Graph();
	~Graph();
protected:
	int graph_type;
	int count_vertex;
	int count_edge;
};

