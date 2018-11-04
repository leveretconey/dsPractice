#include "GraphAdjacentLink.h"
#include <iostream>
#include "GraphMatrix.h"

GraphAdjacentLink::GraphAdjacentLink()
{
	count_vertex = 0;
}


GraphAdjacentLink::~GraphAdjacentLink()
{
	int i;
	EdgeNodePointer pre, p;
	for (i = 0; i < count_vertex; i++)
	{
		p = vertex[i].first_neighbor;
		while (p != NULL)
		{
			pre = p;
			p = p->next_neighbor;
			delete pre;
		}
	}
}

int GraphAdjacentLink::CreateFromFile(char * file_path)
{
	GraphMatrix *gm = new  GraphMatrix;
	gm->CreateFromFile(file_path);

	return 0;
}

int GraphAdjacentLink::ExistEdge(int vertex_1, int vertex_2)
{
	if (VertexLegal(vertex_1) && VertexLegal(vertex_2))
	{
		EdgeNodePointer p = vertex[vertex_1 - 1].first_neighbor;
		while (p)
		{
			if (p->target_vertex == vertex_2 - 1)
				return true;
			else
				p = p->next_neighbor;
		}	
		return false;
	}
	return false;
}
