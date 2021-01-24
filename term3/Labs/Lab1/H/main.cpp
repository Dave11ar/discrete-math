#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> g_s;
vector<int> ans;

void input() {
  cin >> n >> m;

  g_s.resize(n);
  ans.resize(n + 1);

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    g_s[l].push_back(r);
    g_s[r].push_back(l);
  }
}

int find_free(vector<vector<int>> &g) {
  for (int i = 0; i < g.size(); i++) {
    if (!g[i].empty()) {
      return i;
    }
  }

  return -1;
}

void recursive(vector<vector<int>> &g, bool plus) {
  int free = find_free(g);

  if (free == -1) {
    if (plus) {
      ans[g.size()]++;
    } else {
      ans[g.size()]--;
    }
  } else {
    int u = free;
    int v = g[u][0];

    vector<vector<int>> g_1(g.size()), g_2(g.size() - 1);

    for (int i = 0; i < g.size(); i++) {
      for (int j = 0; j < g[i].size(); j++) {
        if ((i == u && g[i][j] == v) || (i == v && g[i][j] == u)) {
          continue;
        }

        g_1[i].push_back(g[i][j]);
      }
    }

    set<int> bruh;
    bruh.insert(u);


    for (int i = 0; i < g.size(); i++) {
      if (i == v) {
        continue;
      }

      for (int j = 0; j < g[i].size(); j++) {
        if (i == u) {
          bruh.insert(g[i][j]);
          if (g[i][j] == v) {
            continue;
          }
        }

        int l = i;
        int r = g[i][j];

        if (l > v) {
          l--;
        }
        if (r > v) {
          r--;
        }

        if (g[i][j] == v) {
          g_2[l].push_back(u);
        } else {
          g_2[l].push_back(r);
        }
      }
    }

    for (int j = 0; j < g[v].size(); j++) {
      int to = g[v][j];
      if (bruh.count(to) == 0) {
        if (to > v) {
          to--;
        }
        if (u == 2) {
          int a =2;
        }
        g_2[u].push_back(to);
      }
    }

    recursive(g_1, plus);
    recursive(g_2, !plus);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  recursive(g_s, true);

  cout << n << '\n';
  for (int i = n; i >= 0; i--) {
    cout << ans[i] << ' ';
  }

  return 0;
}
