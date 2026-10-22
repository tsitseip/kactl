/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Topological sorting. Given is an oriented graph.
 * Output is an ordering of vertices, such that there are edges only from left to right.
 * If there are cycles, the returned list will have size smaller than $n$ -- nodes reachable
 * from cycles will not be returned.
 * Usage: vector<int> ord = topoSort(adj); // (int)ord.size() < n iff there is a cycle
 * Time: $O(|V|+|E|)$
 * Status: stress-tested
 */
#pragma once

vector<int> topoSort(const vector<vector<int>>& gr) {
	vector<int> indeg(gr.size()), q;
	for (auto& li : gr) for (int x : li) indeg[x]++;
	for (int i = 0; i < gr.size(); i++)
		if (indeg[i] == 0) q.push_back(i);
	for (int j = 0; j < q.size(); j++) for (int x : gr[q[j]])
		if (--indeg[x] == 0) q.push_back(x);
	return q;
}
