#ifdef _MSC_VER
#pragma once
#endif

#ifndef _GRAPH_ALGORITHM_HPP_
#define	_GRAPH_ALGORITHM_HPP_

#include <macros.hpp>
#include <vector.hpp>
#include <stack.hpp>
#include <list.hpp>

NS_BEGIN(gtl);

template <class GraphType, class PathContainerType = list<int>>
class graphsearch_dfs
{
public:

	enum {unvisited, visited, no_parent_assigned};

	typedef GraphType graph_type;
	typedef typename graph_type::node_type node_type;
	typedef typename graph_type::edge_type edge_type;

	graphsearch_dfs(const graph_type& g, int source, int target) : 
		g_(g),
		source_(source),
		target_(target),
		visited_(g.size(), unvisited),
		route_(g.size(), no_parent_assigned)
	{
		found_ = search();
	}

	bool found() const { return found_; }

	const PathContainerType& path() const
	{
		if (found_ && path_container_.empty())
		{
			int idx = target_;
			path_container_.push_front(idx);
			while (idx != source_)
			{
				idx = route_[idx];
				path_container_.push_front(idx);
			}
		}

		return path_container_;
	}

protected:

	bool search()
	{
		stack<const edge_type*> s;

		edge_type dummy(source_, source_);

		s.push(&dummy);

		std::cout << g_;

		while (!s.empty())
		{
			const edge_type* next = s.top();
			s.pop();
			auto to = next->to();
			auto from = next->from();
			visited_[to] = visited;
			route_[to] = from;

			if (next->to() == target_)
			{
				return true;
			}


			auto edge = g_.edges(from);

			if (!edge.empty()) {
				for (auto &edge : g_.edges(from))
				{
					if (visited_[edge.to()] == unvisited)
					{
						s.push(&edge);
					}
				}
			}
			else {
				std::cout << "it 's empty" << std::endl;
			}
		}

		return false;
	}

private:
	const graph_type& g_;
	int source_;
	int target_;
	bool found_{false};
	vector<int> visited_;
	vector<int> route_;
	PathContainerType path_container_;
};

NS_END(gtl);

#endif