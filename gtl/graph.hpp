#ifdef _MSC_VER
#pragma once
#endif

#ifndef _GRAPH_HPP_
#define	_GRAPH_HPP_

#include <macros.hpp>
#include <avltree.hpp>
#include <utility.hpp>

NS_BEGIN(gtl);

template <class Vertex, class Edge, class VertexContainer = gtl::vector<Vertex>, class EdgeContainer = gtl::list<Edge>>
class sparse_graph
{

};

NS_END(gtl);

#endif