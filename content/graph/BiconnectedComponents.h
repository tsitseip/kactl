/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected
 *  multigraph, plus bridges and articulation points. In a biconnected
 *  component there are at least two internally disjoint paths between
 *  any two nodes (a cycle exists through them). A node can be in
 *  several components. comps[i] = edge ids of component i. An edge in
 *  no component is a bridge (not on any cycle). A node is an
 *  articulation point (isCut) iff removing it disconnects its component.
 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps(eid); // then read comps, isBridge[e], isCut[v]
 * Time: O(E + V)
 * Status: stress-tested
 */
#pragma once

vector<int> num, st, isBridge, isCut;
vector<vector<pair<int, int>>> ed;
vector<vector<int>> comps;
int Time;
int dfs(int at, int par) {
	int me = num[at] = ++Time, top = me, kids = 0;
	for (auto [y, e] : ed[at]) if (e != par) {
		if (num[y]) {
			top = min(top, num[y]);
			if (num[y] < me)
				st.push_back(e);
		} else {
			int si = st.size();
			int up = dfs(y, e);
			top = min(top, up); kids++;
			if (up >= me && (par != -1 || kids > 1)) isCut[at] = 1;
			if (up == me) {
				st.push_back(e);
				comps.emplace_back(st.begin() + si, st.end());
				st.resize(si);
			}
			else if (up < me) st.push_back(e);
			else isBridge[e] = 1;
		}
	}
	return top;
}

void bicomps(int nedges) {
	num.assign((int)ed.size(), 0);
	isCut.assign((int)ed.size(), 0);
	isBridge.assign(nedges, 0); comps.clear(); Time = 0;
	for (int i = 0; i < ed.size(); i++) if (!num[i]) dfs(i, -1);
}
