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

template <class NodeType, class EdgeType, class EdgeContainerType = gtl::list<EdgeType>, class CantainerType = gtl::vector<gtl::pair<NodeType, EdgeContainerType>>>
class sparse_graph
{
	typedef NodeType node_type;
	typedef EdgeType edge_type;
	typedef CantainerType container_type;
	typedef EdgeContainerType edge_container_type;
	typedef container_type::size_type index_type;

	const container_type& container() const { return _container; }
	const edge_container_type& edges(index_type idx) const { return _container[idx].second; }

	void add_node(const node_type& node) {

	}

protected:
	container_type _container;
};

NS_END(gtl);

#endif