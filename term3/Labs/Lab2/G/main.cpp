#include <bits/stdc++.h>

// uber cringe lol ))))))
#define _FORTIFY_SOURCE 0
#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,tune=native")
#pragma GCC optimize("fast-math")

using namespace std;

struct edge {
  int u, v;
  int num_spanning_tree;

  edge(int u, int v) : u(u), v(v), num_spanning_tree(INT_MAX) {}
};

int n, m;
vector<pair<int ,int>> path;
vector<edge> edges;
vector<vector<int>> g_rep;
vector<set<int>> spanning_tree;
set<int> S, T;

vector<int> parent, siz;

void clear_oracle() {
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    siz[i] = 1;
  }
}

void input() {
  cin >> n >> m;

  spanning_tree.emplace_back();
  parent.resize(n);
  siz.resize(n);
  clear_oracle();
  path.resize(m, {INT_MAX, INT_MAX});
  g_rep.resize(m);

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;

    edges.emplace_back(u, v);
  }
}

int find_set(int v) {
  if (v == parent[v]) {
    return v;
  }
  return parent[v] = find_set(parent[v]);
}

void union_set(int a, int b) {
  a = find_set(a);
  b = find_set(b);

  if (siz[a] < siz[b]) {
    swap(a, b);
  }

  parent[b] = a;
  siz[a] += siz[b];
}

bool oracle_acyclic(int num_edge) {
  return find_set(edges[num_edge].u) != find_set(edges[num_edge].v);
}

set<int> modif;

void clear_g_rep() {
  S.clear();
  T.clear();
  for (int const &cur : modif) {
    for (int const &node_num : spanning_tree[cur]) {
      g_rep[node_num].clear();
    }
  }
}

void build_set(set<int> const &st) {
  clear_oracle();
  for (int const &num_edge : st) {
    union_set(edges[num_edge].u, edges[num_edge].v);
  }
}

int build_graph_replacement() {
  clear_g_rep();
  build_set(spanning_tree.back());

  int bruh = -1;
  for (int i = 0; i < m; i++) {
    if (oracle_acyclic(i)) {
      S.insert(i);
      bruh = i;
    }
    if (edges[i].num_spanning_tree == INT_MAX) {
      T.insert(i);
      if (bruh == i) {
        return i;
      }
    }
  }

  for (int const &cur : modif) {
    set<int> cur_tree_tmp(spanning_tree[cur]);

    for (int num_edge : spanning_tree[cur]) {
      cur_tree_tmp.erase(num_edge);
      build_set(cur_tree_tmp);

      for (int i = 0; i < m; i++) {
        if (spanning_tree[cur].count(i) != 0) {
          continue;
        }

        if (oracle_acyclic(i)) {
          g_rep[num_edge].push_back(i);
        }
      }
      cur_tree_tmp.insert(num_edge);
    }
  }
  modif.clear();

  return INT_MAX;
}

int bfs() {
  path.assign(m, {INT_MAX, INT_MAX});
  queue<int> q;
  for (int const &num_edge : S) {
    path[num_edge] = {0, -1};
    q.push(num_edge);
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int const &to : g_rep[u]) {
      if (path[to].first == INT_MAX) {
        path[to] = {path[u].first + 1, u};
        q.push(to);
      }
    }
  }

  pair<int, int> mx = {INT_MAX, INT_MAX};
  for (int const &num_edge : T) {
    if (path[num_edge].first < mx.first) {
      mx = {path[num_edge].first, num_edge};
    }
  }

  return mx.second;
}

void solution() {
  while (true) {
    modif.insert((int)spanning_tree.size() - 1);
    int mx;
    if ((mx = build_graph_replacement()) == INT_MAX) {
      mx = bfs();

      if (mx == INT_MAX) {
        break;
      }
    } else {
      path[mx].second = -1;
    }

    while (path[mx].second != -1) {
      int prev_edge = path[mx].second;

      modif.insert(edges[mx].num_spanning_tree);
      spanning_tree[edges[prev_edge].num_spanning_tree].insert(mx);
      spanning_tree[edges[prev_edge].num_spanning_tree].erase(prev_edge);
      edges[mx].num_spanning_tree = edges[prev_edge].num_spanning_tree;

      mx = prev_edge;
    }

    spanning_tree.back().insert(mx);
    modif.insert(edges[mx].num_spanning_tree);
    edges[mx].num_spanning_tree = (int)spanning_tree.size() - 1;
    modif.insert(edges[mx].num_spanning_tree);
    modif.erase(INT_MAX);

    if (spanning_tree.back().size() == n - 1) {
      spanning_tree.emplace_back();
    }
  }

  int last = spanning_tree.size();
  if (spanning_tree.back().size() != n - 1) {
    last--;
  }

  cout << last << '\n';
  for (int i = 0; i < last; i++) {
    for (int num_edge : spanning_tree[i]) {
      cout << num_edge + 1 << ' ';
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("multispan.in", "r", stdin);
  freopen("multispan.out", "w", stdout);

  input();
  solution();

  return 0;
}