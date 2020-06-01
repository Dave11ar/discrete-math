#include <bits/stdc++.h>

using namespace std;

int n, m, k;
set<int> allowed[2];
vector<vector<int>> edges[2];
vector<int> iso;

vector<bool> used;

void input() {
  cin >> n >> m >> k;
  used.resize(n, false);
  iso.resize(n, -1);
  iso[0] = 0;

  for (int cur_auto = 0; cur_auto < 2; cur_auto++) {
    for (int i = 0; i < k; i++) {
      int t;
      cin >> t;
      allowed[cur_auto].insert(t - 1);
    }

    edges[cur_auto].resize(n, vector<int>(26, -1));
    for (int i = 0; i < m; i++) {
      int a, b;
      char c;
      cin >> a >> b >> c;

      edges[cur_auto][a - 1][c - 'a'] = b - 1;
    }
    if (cur_auto == 1) break;

    cin >> n >> m >> k;
  }
}

void ans_no() {
  cout << "NO";
  exit(0);
}

void dfs(int v) {
  for (int i = 0; i < 26; i++) {
    if (edges[0][v][i] == -1) {
      if (edges[1][iso[v]][i] != -1) ans_no();
    } else {
      if (edges[1][iso[v]][i] == -1) ans_no();

      used[edges[1][iso[v]][i]] = true;
      if (iso[edges[0][v][i]] == -1) {
        if (allowed[0].count(edges[0][v][i]) ^ allowed[1].count(edges[1][iso[v]][i])) ans_no();
        iso[edges[0][v][i]] = edges[1][iso[v]][i];
        dfs(edges[0][v][i]);
      } else {
        if (iso[edges[0][v][i]] != edges[1][iso[v]][i]) ans_no();
      }
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("isomorphism.in", "r", stdin);
  freopen("isomorphism.out", "w", stdout);

  input();

  dfs(0);

  cout << "YES";
  return 0;
}
