#include <graph.hpp>

struct GraphNode
{

};

struct GraphEdge
{
	GraphEdge() {}

	GraphEdge(int from, int to) : from_(from), to_(to)
	{

	}

	int from() const { return from_; }
	int to() const { return to_; }

	int from_, to_;
};

int main(void)
{
	gtl::sparse_graph<GraphNode, GraphEdge> g;
	
	g.add_node(GraphNode());
	g.add_node(GraphNode());
	g.add_edge(GraphEdge(0, 1));

	std::cout << g;

	return 0;
}