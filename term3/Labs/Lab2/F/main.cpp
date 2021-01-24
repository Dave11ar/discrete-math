#include <bits/stdc++.h>

using namespace std;

struct edge {
  int u, v;
  int color;

  edge(int u, int v, int color) : u(u), v(v), color(color) {}
};

vector<pair<int ,int>> path;
int n, m;
vector<edge> edges;
vector<vector<int>> g_rep;
set<int> A, S, T;

int timer = 1;
vector<bool> colors;
vector<int> parent, siz, used;

void clear_oracle() {
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    siz[i] = 1;
  }
  colors.assign(110, false);
}

void input() {
  cin >> n >> m;

  colors.resize(110);

  parent.resize(n);
  siz.resize(n);
  clear_oracle();
  path.resize(m, {INT_MAX, INT_MAX});

  g_rep.resize(m);
  used.resize(m);

  for (int i = 0; i < m; i++) {
    int u, v, color;
    cin >> u >> v >> color;
    u--; v--;

    edges.emplace_back(u, v, color);
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

bool oracle_color(int num_edge) {
  return !colors[edges[num_edge].color];
}

bool oracle_acyclic(int num_edge) {
  return find_set(edges[num_edge].u) != find_set(edges[num_edge].v);
}

void clear_g_rep() {
  S.clear();
  T.clear();
  for (int i = 0; i < m; i++) {
    g_rep[i].clear();
  }
}

void build_set(set<int> const &st) {
  clear_oracle();
  for (int const &num_edge : st) {
    union_set(edges[num_edge].u, edges[num_edge].v);
    colors[edges[num_edge].color] = true;
  }
}

void build_graph_replacement() {
  clear_g_rep();
  set<int> A_tmp(A);

  build_set(A);
  for (int i = 0; i < m; i++) {
    if (A.count(i) != 0) {
      continue;
    }

    if (oracle_color(i)) {
      S.insert(i);
    }
    if (oracle_acyclic(i)) {
      T.insert(i);
    }
  }

  for (int const &num_edge : A) {
    A_tmp.erase(num_edge);
    build_set(A_tmp);
    for (int i = 0; i < m; i++) {
      if (A.count(i) != 0) {
        continue;
      }
      if (oracle_color(i)) {
        g_rep[num_edge].push_back(i);
      }
      if (oracle_acyclic(i)) {
        g_rep[i].push_back(num_edge);
      }
    }
    A_tmp.insert(num_edge);
  }
}


int bfs() {
  path.assign(m, {INT_MAX, INT_MAX});
  queue<int> q;
  for (int const &num_edge : S) {
    path[num_edge] = {0, -1};
    q.push(num_edge);
    used[num_edge] = timer;
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int const &to : g_rep[u]) {
      if (used[to] != timer) {
        path[to] = {path[u].first + 1, u};
        used[to] = timer;
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
    build_graph_replacement();
    timer++;
    int mx = bfs();

    if (mx == INT_MAX) {
      break;
    }

    if (path[mx].second == -1) {
      A.insert(mx);
    } else {
      A.insert(mx);

      mx = path[mx].second;
      while (mx != -1) {
        A.erase(mx);
        A.insert(path[mx].second);
        mx = path[path[mx].second].second;
      }
    }
  }

  cout << A.size() << '\n';
  for (int const &num_edge : A) {
    cout << num_edge + 1 << ' ';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("rainbow.in", "r", stdin);
  freopen("rainbow.out", "w", stdout);

  input();
  solution();

  return 0;
}