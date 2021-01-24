#include <bits/stdc++.h>

using namespace std;

struct edge {
  int u, v;
  int64_t cost;
  int num;

  edge(edge const &) = default;
  edge(int u, int v, int64_t cost, int num) : u(u), v(v), cost(cost), num(num) {}
};

int n, m;
int64_t s;
vector<edge> edges, free_edges;
vector<int> parent, siz;

void input() {
  cin >> n >> m >> s;

  parent.resize(n);
  siz.resize(n);

  for (int i = 0; i < n; i++) {
    parent[i] = i;
    siz[i] = 1;
  }

  for (int i = 1; i <= m; i++) {
    int u, v;
    int64_t cost;

    cin >> u >> v >> cost;
    u--; v--;

    edges.emplace_back(u, v, cost, i);
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

void mst() {
  sort(edges.begin(), edges.end(), [](edge const &a, edge const &b) {
    return a.cost > b.cost;
  });

  for (edge &cur_edge : edges) {
    if (find_set(cur_edge.v) != find_set(cur_edge.u)) {
      union_set(cur_edge.v, cur_edge.u);
    } else {
      free_edges.push_back(cur_edge);
    }
  }

  reverse(free_edges.begin(), free_edges.end());
}

void solution() {
  vector<int> ans;

  for (edge &cur_edge : free_edges) {
    if (cur_edge.cost > s) {
      break;
    }

    ans.push_back(cur_edge.num);
    s -= cur_edge.cost;
  }

  cout << ans.size() << '\n';

  sort(ans.begin(), ans.end());
  for (int &i : ans) {
    cout << i << ' ';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("destroy.in", "r", stdin);
  freopen("destroy.out", "w", stdout);

  input();
  mst();
  solution();

  return 0;
}
