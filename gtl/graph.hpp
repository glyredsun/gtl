#ifdef _MSC_VER
#pragma once
#endif

#ifndef _GRAPH_HPP_
#define	_GRAPH_HPP_

#include <macros.hpp>
#include <avltree.hpp>
#include <utility.hpp>
#include <vector.hpp>
#include <list.hpp>

NS_BEGIN(gtl);

template <class NodeType, class EdgeType, class EdgeContainerType = list<EdgeType>, class CantainerType = vector<pair<NodeType, EdgeContainerType>>>
class sparse_graph
{
public:
	typedef NodeType node_type;
	typedef EdgeType edge_type;
	typedef CantainerType container_type;
	typedef EdgeContainerType edge_container_type;
	typedef typename container_type::size_type index_type;
	typedef pair<NodeType, EdgeContainerType> value_type;

	const container_type& container() const { return container_; }
	const edge_container_type& edges(index_type idx) const { return container_[idx].second; }

	void add_node(const node_type& node) { container_.push_back(value_type(node, edge_container_type())); }
	void add_edge(const edge_type& edge) { container_[edge.from()].second.push_back(edge); }

protected:
	container_type container_;
};

template <class NodeType, class EdgeType, class EdgeContainerType = list<EdgeType>, class CantainerType = vector<pair<NodeType, EdgeContainerType>>>
std::ostream& operator<< (std::ostream& o, const sparse_graph<NodeType, EdgeType, EdgeContainerType, CantainerType>& g)
{
	auto c = g.container();
	for (size_t i = 0, len = c.size(); i < len; ++i)
	{
		auto value = c[i];
		o << i << ", [";
		for (auto edge : value.second)
		{
			o << edge.to() << " ";
		}
		o << "]" << std::endl;
	}
	return o;
}

NS_END(gtl);

#endif