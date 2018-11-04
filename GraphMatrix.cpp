#include "GraphMatrix.h"
#include <iostream>
#include <fstream>

int GraphMatrix::CreateFromFile(char * file_path)
{
	const int TYPE_NORMAL_MATRIX = 1;
	using namespace std;

	ifstream *input_file = new ifstream;//ifstream 在std命名空间中，必须要using一下
	char buffer[4 * MAX_VERTEX];
	char *buffer_pointer;
	int column, row;
	int loading_type;
	int edge_weigh;

	input_file->open(file_path,ios::in);
	if (!input_file->is_open())
	{
		cout << "初始化图错误：文件无法打开" << endl;
		return 1;
	}
	input_file->getline(buffer, 20);
	//load graph type
	input_file->getline(buffer, 20);
	sscanf_s(buffer, "%d", &graph_type);//这个函数的格式类似于scanf
	//load vertex_count
	input_file->getline(buffer, 20);
	sscanf_s(buffer, "%d", &count_vertex);
	//load loading type
	input_file->getline(buffer, 20);
	sscanf_s(buffer, "%d", &loading_type);
	//load vertex info
	input_file->getline(buffer, sizeof(buffer));
	column = 0;
	buffer_pointer = buffer;
	while (*buffer_pointer != '\0')
	{
		sscanf_s(buffer_pointer, "%d", &vertex_info[column++]);
		while (*buffer_pointer == ' ')
			buffer_pointer++;
		while (*buffer_pointer != ' '&& *buffer_pointer != '\0')
			buffer_pointer++;
	}
	//load whole matrix
	if (loading_type == TYPE_NORMAL_MATRIX)
	{
		for (row = 0; row < count_vertex; row++)
		{
			input_file->getline(buffer, sizeof(buffer));
			column = 0;
			buffer_pointer = buffer;
			while (*buffer_pointer != '\0')
			{
				sscanf_s(buffer_pointer, "%d", &edge[row][column]);
				if (edge[row][column++] != 0)
					count_edge++;
				while (*buffer_pointer == ' ')
					buffer_pointer++;
				while (*buffer_pointer != ' '&& *buffer_pointer != '\0')
					buffer_pointer++;
			}
		}
		if (graph_type == TYPE_UNDIRECTED)
		{
			count_edge /= 2;
			//检查一下矩阵是否真的对称
			for (row = 0; row<count_vertex; row++)
				for (column = row; column<count_vertex; column++)
					if (edge[row][column] != edge[column][row])
					{
						cout << "警告：此无向图的邻接矩阵并不对称" << endl;
						row = count_vertex;
						column = count_vertex;
					}
		}
	}
	else
	{
		for (row = 0; row < count_vertex; row++)
			for (column = 0; column < count_vertex; column++)
				edge[row][column] = 0;//初始化
		for (;;)
		{
			input_file->getline(buffer, sizeof(buffer));
			buffer_pointer = buffer;
			if (strcmp(buffer_pointer, "*/")==0)
				break;

			sscanf_s(buffer_pointer, "%d", &row);
			while (*buffer_pointer == ' ')
				buffer_pointer++;
			while (*buffer_pointer != ' '&& *buffer_pointer != '\0')
				buffer_pointer++;

		    sscanf_s(buffer_pointer, "%d", &column);
			while (*buffer_pointer == ' ')
				buffer_pointer++;
			while (*buffer_pointer != ' '&& *buffer_pointer != '\0')
				buffer_pointer++;

			sscanf_s(buffer_pointer, "%d", &edge_weigh);

			edge[row - 1][column - 1] = edge_weigh;
			count_edge++;
			if (graph_type == TYPE_UNDIRECTED)
			{
				edge[column - 1][row - 1] = edge_weigh;
			}
		}
	}
	input_file->close();
	return 0;
}

GraphMatrix::GraphMatrix()
{
}


GraphMatrix::~GraphMatrix()
{
}

int GraphMatrix::DFTraverseRecursion(int vertex_visiting, int(*visit)(GraphMatrix *, int))
{
	int visiting_neighbor;
	visit(this, vertex_visiting);
	SetVisited(vertex_visiting);
	for (visiting_neighbor = FirstNeighbor(vertex_visiting); visiting_neighbor != 0; \
	visiting_neighbor = NextNeighbor(vertex_visiting, visiting_neighbor))
	{
		if(!VertexVisited(visiting_neighbor))//务必注意要先确认没有访问过再去访问
		    DFTraverseRecursion(visiting_neighbor, visit);
	}
	return 0;
}

int GraphMatrix::ExistEdge(int vertex_1, int vertex_2)
{
	if (!VertexLegal(vertex_1, vertex_2))
		return false;
    return edge[vertex_1 - 1][vertex_2 - 1] != NULL_EDGE1 &&
		   edge[vertex_1 - 1][vertex_2 - 1] != NULL_EDGE2;
}

void GraphMatrix::ShowVertexNeighbors(int vertex)
{
	using namespace std;
	int row;

	if (vertex<1 || vertex>count_vertex)
    	std::cout << "错误：此顶点不存在" << std::endl;
	else
	{
		if (graph_type == TYPE_DIRECTED)
		{
			std::cout << "从顶点" << vertex  << "出发能到达的顶点包括："<<'\t';
			for (row =1; row <= count_vertex; row++)
			{
				if (ExistEdge(vertex,row))
					cout << row <<"  ";
			}
			std::cout << std::endl;

			std::cout << "能到达顶点" << vertex  << "的顶点包括："<<"\t\t";
			for (row = 1; row <= count_vertex; row++)
			{
				if (ExistEdge(row, vertex))
					cout << row  << "  ";
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "与顶点" << vertex << "相邻的顶点包括：" << '\t';
			for (row = 1; row <= count_vertex; row++)
			{
				if (ExistEdge(row, vertex))
					cout << row  << "  ";
			}
			std::cout << std::endl;
		}
	}
}

void GraphMatrix::InsertVertex()
{
	if (count_vertex == MAX_VERTEX)
	{
		std::cout << "错误：顶点数已达到最大" << std::endl;
	}
	int i;
	for (i = 0; i <= count_vertex; i++)
		edge[i][count_vertex] = 0;
	for (i = 0; i <= count_vertex; i++)
		edge[count_vertex][i] = 0;
	count_vertex++;
}

void GraphMatrix::DeleteVertex(int vertex_to_delete)
{
	int row, column;
	//下面的向上移动
	for (row = vertex_to_delete; row < count_vertex; row++)
		for (column = 0; column < vertex_to_delete-1; column++)
			edge[row - 1][column] = edge[row][column];
	//右边的向左移动
	for (row = 0; row < vertex_to_delete - 1; row++)
		for (column = vertex_to_delete; column < count_vertex; column++)
			edge[row][column-1] = edge[row][column];
	//右下的向左上移动
	for (row = vertex_to_delete; row < count_vertex; row++)
		for (column = vertex_to_delete; column < count_vertex; column++)
			edge[row-1][column - 1] = edge[row][column];
	count_vertex--;
}

int GraphMatrix::AddEdge(int vertex_1, int vertex_2, int weight)
{
	if (ExistEdge(vertex_1, vertex_2))
		return 1;
	edge[vertex_1 - 1][vertex_2 - 1] = weight;
	if(graph_type==TYPE_UNDIRECTED)
		edge[vertex_2 - 1][vertex_1 - 1] = weight;
	return 0;
}

int GraphMatrix::RemoveEdge(int vertex_1, int vertex_2)
{
	if (ExistEdge(vertex_1, vertex_2))
	{
		vertex_1--; vertex_2--;
		edge[vertex_1][vertex_2] = 0;
		if(graph_type == TYPE_UNDIRECTED)
			edge[vertex_2][vertex_1] = 0;
		return 0;
	}
	else
		return 1;

}

int GraphMatrix::FirstNeighbor(int vertex)
{
	if (!VertexLegal(vertex))
		return 0;
	int column;
	for (column = 1; column <= count_vertex; column++)
		if (ExistEdge(vertex, column))
			return column;
	return 0;


}

int GraphMatrix::NextNeighbor(int vertex, int last_neighbor)
{
	if (!VertexLegal(vertex, last_neighbor))
		return 0;
	int column;
	for (column = last_neighbor+1; column <= count_vertex; column++)
		if (ExistEdge(vertex, column))
			return column;
	return 0;

}

int GraphMatrix::ShowVertex(GraphMatrix *graph, int vertex)
{
	if (graph->VertexLegal(vertex))
	{
		std::cout << graph->GetVertexInfo(vertex)<< " ";
		return 0;
	}
	else
		return 1;
}

int GraphMatrix::Degree(int vertex)
{
	if (VertexLegal(vertex))
		return Degree(vertex, IN_DEGREE) + Degree(vertex, OUT_DEGREE);
	else
		return 0;
}

int GraphMatrix::ShowAllVertex(int order)
{
	int (*visit)(GraphMatrix *,int) = &(GraphMatrix::ShowVertex);
	Traverse(order, visit);
	return 0;
}

int GraphMatrix::Traverse(int order, int(*visit)(GraphMatrix *, int))
{
	switch (order)
	{
	case DEPTH_FIRST:DFTraverse(visit); break;
	case BROAD_FIRST:BFTraverse(visit); break;
	case DEPTH_FIRST_NO_RECURSION:DFNoRecursionTraverse(visit); break;
	case DEPTH_FIRST_NO_RECURSION_V2:DFNoRecursionTraverseV2(visit); break;
	default:
		std::cout << "错误：参数错误" <<std::endl;
		return 1;
	}
	std::cout << std::endl;
	return 0;
}

int GraphMatrix::BFTraverse(int(*visit)(GraphMatrix *, int))
{
	int i;
	int q[MAX_VERTEX], rear,front;
	int visiting_vertex, visiting_neighbor;
	Visited_Initialization();
	for (i = 1; i <= count_vertex; i++)//对每一个连通分量都执行一次BFS
	{
		if (!VertexVisited(i))
		{
			visit(this,i);//进队列之前访问
			SetVisited(i);
			rear = 0; front = 0;
			q[rear++] = i;
			while (rear != front)
			{
				visiting_vertex = q[front++];
				for (visiting_neighbor = FirstNeighbor(visiting_vertex); visiting_neighbor != 0;   \
					 visiting_neighbor = NextNeighbor(visiting_vertex, visiting_neighbor))
				{
					if (!VertexVisited(visiting_neighbor))
					{
						visit(this,visiting_neighbor);
						SetVisited(visiting_neighbor);
						q[rear++] = visiting_neighbor;
					}//if
				}//for
			}//while
		}//if
	}//for
	return 0;
}

int GraphMatrix::DFTraverse(int(*visit)(GraphMatrix *, int))
{
	Visited_Initialization();
	for (int i = 1; i <= count_vertex; i++)
		if (!VertexVisited(i))
			DFTraverseRecursion(i, visit);
	return 0;
}

int GraphMatrix::BFSingleOriginShortestDistance(int origin)
{
	if (!VertexLegal(origin))
		return 1;

	const int INACCESSIBLE=999999;
	int i;
	int distance[MAX_VERTEX+1];
	for (i = 1; i <= count_vertex; i++)
		distance[i] = INACCESSIBLE;
	Visited_Initialization();
	int rear = 0, front = 0;
	int q[MAX_VERTEX];
	distance[origin] = 0;
	SetVisited(origin);
	q[rear++] = origin;
	int visiting_vertex, visiting_neighbor;
	while (front != rear)
	{
		visiting_vertex = q[front++];
		for (visiting_neighbor = FirstNeighbor(visiting_vertex); visiting_neighbor != 0;   \
			visiting_neighbor = NextNeighbor(visiting_vertex, visiting_neighbor))
		{
			if (!VertexVisited(visiting_neighbor))
			{
				distance[visiting_neighbor] = distance[visiting_vertex]+1;
				SetVisited(visiting_neighbor);
				q[rear++] = visiting_neighbor;
			}
		}
	}
	for (i = 1; i <= count_vertex; i++)
	{
		if (distance[i] == INACCESSIBLE)
			std::cout << "顶点" << i << "不可到达"<<std::endl;
		else
			std::cout << "到顶点" << i << "的最短距离为"<<distance[i] << std::endl;
	}
	return 0;
}

void GraphMatrix::Visited_Initialization()
{
	for (int i = 0; i < count_vertex; i++)
		vertex_visted[i] = false;;
}
int GraphMatrix::VertexVisited(int vertex)
{
	if (VertexLegal(vertex))
		return 0!=vertex_visted[vertex - 1];
	else
		return true;
}

int GraphMatrix::SetVisited(int vertex)
{
	if (VertexLegal(vertex))
	{
		vertex_visted[vertex - 1] = true;
		return 0;
	}
	else
		return 1;
}

int GraphMatrix::GetVertexInfo(int vertex)
{
	return vertex_info[vertex-1];
}

int GraphMatrix::DFNoRecursionTraverse(int(*visit)(GraphMatrix *, int))
{
	const int NULL_VERTEX=0;
	Visited_Initialization();
	int stack[MAX_VERTEX], top;//visiting stack
	int visiting_neighbor[MAX_VERTEX];//temporarily record last neighbor visited by the vertex on each level of stack
	int visiting_vertex;


	for (int i = 1; i <= count_vertex; i++)
	{
		top = 0;
		if (!VertexVisited(i))
		{
			//对每个联通分量调用一次dfs,这里每次在进栈之前进行访问
			visiting_vertex = i;
			while (!(visiting_vertex == NULL_VERTEX && top == 0))
			{
				if (visiting_vertex != NULL_VERTEX && !VertexVisited(visiting_vertex))
				{
					visit(this, visiting_vertex);
					SetVisited(visiting_vertex);
					stack[top] = visiting_vertex;
					visiting_vertex = FirstNeighbor(visiting_vertex);
					visiting_neighbor[top] = visiting_vertex;
					top++;
				}
				else
				{
					visiting_vertex = stack[top - 1];
					visiting_vertex = NextNeighbor(visiting_vertex, visiting_neighbor[top - 1]);
					visiting_neighbor[top - 1] = visiting_vertex;
					if (visiting_vertex == NULL_VERTEX)
						top--;
				}
			}
		}
	}
	return 0;
}

int GraphMatrix::DFNoRecursionTraverseV2(int(*visit)(GraphMatrix *, int))
{
	int s[MAX_VERTEX], top;
	int k, w;
	Visited_Initialization();
	for (int i = 1; i < count_vertex; i++)
	{
		if (!VertexVisited(i))
		{
			top = 0;
			s[top++] = i;
			SetVisited(i);
			while (top != 0)
			{
				k = s[--top];
				visit(this,k);
				for(w=FirstNeighbor(k);w!=0;w=NextNeighbor(k,w))
					if (!VertexVisited(w))
					{
						s[top++] = w;
						SetVisited(w);
					}
			}
		}
	}
	return 0;
}

int GraphMatrix::DijkstraShortestPath(int vertex)
{
	
	if (!VertexLegal(vertex))
		return 1;
	Visited_Initialization();
	int i,j;
	int distance[MAX_VERTEX];
	//由于我用0表示不可到达，所以这里额外调一下
	for(i=0;i<count_vertex;i++)
		for (j = 0; j < count_vertex; j++)
		{
			if (i != j &&edge[i][j] == 0)
				edge[i][j] = NULL_EDGE2;
		}

	for (i = 0; i < count_vertex; i++)
	{
		distance[i] = edge[vertex - 1][i];//初始化值为源点到各个点的直线距离
	}
	int close_vertex,close_distance;
	int path_order[MAX_VERTEX],path_order_position=1;
	vertex_visted[vertex - 1] = true;
	path_order[0] = vertex - 1;

	while (path_order_position != count_vertex)
	{
		//找出剩下的顶点中距离最短的
		close_distance = 0x7fffffff;
		for (i = 0; i < count_vertex; i++)
		{
			if (!vertex_visted[i] && distance[i] < close_distance)
			{
				close_distance = distance[i];
				close_vertex = i;
			}
		}
		//选中这个顶点
		path_order[path_order_position++] = close_vertex;
		vertex_visted[close_vertex] = true;
		//更新距离
		for (i = 0; i < count_vertex; i++)
		{
			//如果绕过这个新的节点更近，就走新的节点
			if (distance[close_vertex] + edge[close_vertex][i] < distance[i])
				distance[i] = distance[close_vertex] + edge[close_vertex][i];
		}
	}
	//output 
	for (i = 0; i < count_vertex; i++)
	{
		std::cout << "从顶点" << vertex << "到顶点" << i + 1  \
			<< "的最短距离为" << distance[i] << std::endl;
	}
	std::cout << "节点选中的顺序为:";
	for (i = 0; i < count_vertex; i++)
	{
		std::cout << path_order[i] + 1 << "->";
	}
	std::cout << std::endl;
	return 0;
}

int GraphMatrix::FloydShortestPath()
{
	int i, j, k;
	int distance[MAX_VERTEX][MAX_VERTEX];
	//由于我用0表示不可到达，所以这里额外调一下
	for (i = 0; i<count_vertex; i++)
		for (j = 0; j < count_vertex; j++)
		{
			if (i != j &&edge[i][j] == 0)
				edge[i][j] = NULL_EDGE2;
			distance[i][j] = edge[i][j];
		}
	for (k = 0; k < count_vertex; k++)//i到j从节点k绕行
	    for (i = 0; i<count_vertex; i++)
	    	for (j = 0; j < count_vertex; j++)
			{
				if (distance[i][j] > distance[i][k] + edge[k][j])
					distance[i][j] = distance[i][k] + edge[k][j];
			}
	//output
	for (i = 0; i < count_vertex; i++)
	{
		for (j = 0; j < count_vertex; j++)
			std::cout << distance[i][j]<<'\t';
		std::cout << std::endl;
	}
	return 0;
}

GraphMatrix *GraphMatrix::Copy()
{
	GraphMatrix *gm = new GraphMatrix();
	gm->count_edge = count_edge;
	gm->count_vertex = count_vertex;
	gm->graph_type = graph_type;
	int i, j;
	for (i = 0; i < count_vertex; i++)
	{
		gm->vertex_info[i]=vertex_info[i];
		for (j = 0; j < count_vertex; j++)
			gm->edge[i][j] = edge[i][j];
	}
	return gm;
}

int GraphMatrix::TopologicalSorting()
{/*
	GraphMatrix *gm = Copy();
	int sorted_array[MAX_VERTEX];
	int i, j, k;
	Visited_Initialization();
	for (i = 0; i < gm->count_vertex; i++)
	{
		//首先寻找一个入度为0的节点
		for (j = 0; j <  gm->count_vertex; j++)
			if (Degree(j + 1, IN_DEGREE) == 0 && !VertexVisited(j + 1))
				break;
		//record it
		if (j == gm->count_vertex)
		{
			std::cout << "拓扑序列不存在" << std::endl;
			return 1;
		}
		sorted_array[i] = j;
		SetVisited(j + 1);
		//由于不好直接删顶点，把它出发的边都删掉，留一条到达它的边
		for (k = 0; k <  gm->count_vertex; k++)
			gm->edge[j][k] = 0;
		gm->edge[sorted_array[0]][j] = 1;
	}
	//output
	for (i = 0; i <  gm->count_vertex; i++)
		std::cout << sorted_array[i]+1;
	std::cout << std::endl;
	return 0;
	*/
	int s[MAX_VERTEX], top = 0;
	int degeree[MAX_VERTEX],visiting_vertex,vertex_neighbor;
	int i;
	int sorted[MAX_VERTEX], sorted_count = 0;
	for (i = 1; i <= count_vertex; i++)
	{
		degeree[i-1] = Degree(i, IN_DEGREE);
		if (degeree[i-1] == 0)
			s[top++] = i;
	}
	while (top != 0)
	{
		visiting_vertex = s[--top];
		sorted[sorted_count++] = visiting_vertex;
		for (vertex_neighbor = FirstNeighbor(visiting_vertex); vertex_neighbor != 0; \
			 vertex_neighbor = NextNeighbor(visiting_vertex, vertex_neighbor))
		{
			degeree[vertex_neighbor - 1]--;
			if (degeree[vertex_neighbor - 1] == 0)
				s[top++] = vertex_neighbor;
		}
	}
	if (sorted_count == count_vertex)
	{
		std::cout << "拓扑序列为" ;
		for (i = 0; i < count_vertex;i++)
			std::cout << sorted[i] << "  ";
		std::cout  << std::endl;
		return 0;
	}
	else
	{
		std::cout << "拓扑序列不存在" << std::endl;
		return 1;
	}
}

int GraphMatrix::Degree(int vertex,int type)
{
	int i,degree=0;
	if (VertexLegal(vertex))
		switch (type)
		{
		case IN_DEGREE:
			for (i = 1; i < count_vertex; i++)
				if (ExistEdge(i,vertex))
					degree++;
			return degree;
			break;
		case OUT_DEGREE:
			for (i = 1; i < count_vertex; i++)
				if (ExistEdge(vertex,i))
					degree++;
			return degree;
			break;
		default:return 0;
		}
	else
		return 0;
}

void DFSTopologicalSortingRecusion(GraphMatrix *gm,int vertex, int &time,int *finish_time)
{
	int vertex_neighbor;
	gm->SetVisited(vertex);
	
	for (vertex_neighbor = gm->FirstNeighbor(vertex); vertex_neighbor != 0; \
		vertex_neighbor = gm->NextNeighbor(vertex, vertex_neighbor))
	{
		if(!gm->VertexVisited(vertex_neighbor))
	    	DFSTopologicalSortingRecusion(gm, vertex_neighbor, time, finish_time);
	}
	time++;
	finish_time[vertex - 1] = time;
}

int GraphMatrix::DFSTopologicalSorting()
{
	Visited_Initialization();
	int i= 0;
	int time = 0, finish_time[MAX_VERTEX];
	for (i = 1; i <= count_vertex; i++)
		if (!VertexVisited(i))
			DFSTopologicalSortingRecusion(this, i, time, finish_time);
	
	int sorted[MAX_VERTEX];
	for (i = 0; i < count_vertex; i++)
	{
		sorted[count_vertex - finish_time[i]] = i + 1;
	}
	for (i = 0; i < count_vertex; i++)
		std::cout << sorted[i] << "  ";
	std::cout << std::endl;
	return 0;
}