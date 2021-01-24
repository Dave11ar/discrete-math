#include <bits/stdc++.h>

using namespace std;

int n, m, k;
vector<vector<int>> g;
vector<int> color, used_color;
vector<bool> used;

void input() {
  cin >> n >> m;

  g.resize(n);
  color.resize(n, -1);
  used.resize(n);

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    g[l].push_back(r);
    g[r].push_back(l);
  }

  for (int i = 0; i < n; i++) {
    k = max(k, (int)g[i].size());
  }

  if (k % 2 == 0) {
    k++;
  }

  used_color.resize(k + 1);
}

int timer = 0;

int find_color(int v) {
  timer++;

  for (int &to : g[v]) {
    if (color[to] != -1) {
      used_color[color[to]] = timer;
    }
  }

  for (int i = 1; i <= k; i++) {
    if (used_color[i] != timer) {
      return i;
    }
  }

  assert(!strcmp("jabroni", "outfit"));
}

void dfs(int v) {
  used[v] = true;
  color[v] = find_color(v);

  for (int &to : g[v]) {
    if (!used[to]) {
      dfs(to);
    }
  }
}

void output() {
  cout << k << '\n';
  for (int i = 0; i < n; i++) {
    cout << color[i] << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  dfs(0);
  output();

  return 0;
}
