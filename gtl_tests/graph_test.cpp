#include <graph.hpp>
#include <graph_algorithm.hpp>

struct GraphNode
{
	GraphNode() {}

	GraphNode(int idx) : idx_(idx) {}

	int idx_;
};

struct GraphEdge
{
	GraphEdge() {}

	GraphEdge(int from, int to) : from_(from), to_(to)
	{

	}

	int from() const { return from_; }
	int to() const { return to_; }

	int from_{ 0 }, to_{ 0 };
};

int main(void)
{
	typedef gtl::sparse_graph<GraphNode, GraphEdge> graph_type;
	graph_type g;
	
	g.add_node(GraphNode(0));
	g.add_node(GraphNode(1));
	g.add_node(GraphNode(2));
	g.add_node(GraphNode(3));
	g.add_node(GraphNode(4));
	g.add_node(GraphNode(5));
	g.add_edge(GraphEdge(0, 1));

	std::cout << g;

	gtl::graphsearch_dfs<graph_type> pathFinder(g, 0 , 1);

	if (pathFinder.found()) {
		std::cout << "found!" << std::endl;
	}
	else {
		std::cout << "not found!" << std::endl;
	}
	
	system("pause");

	return 0;
}